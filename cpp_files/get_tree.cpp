#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>

#include "error_codes.h"
#include "get_tree.h"
#include "akinator.h"

error_t get_tree(const char* file_name, struct tree_t* tree)
{
    error_t error_status = OK;

    if (tree == NULL)
    {
        FILL_DBG(NULL_POINT_ON_TREE_STRUCT);
        return NULL_POINT_ON_TREE_STRUCT;
    }

    if (no_or_empty_file_created(file_name))
    {
        FILE* file = fopen(file_name, "w+");
        fclose(file);
        printf("Your database doesn't exist.\n");
        error_status = create_tree_root(tree);
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }
    }

    FILE* file = fopen(file_name, "r");
    char* tree_buffer = create_file_buffer(file_name, file);
    if (tree_buffer == NULL)
    {
        FILL_DBG(NULL_POINT_FROM_CALLOC);
        return NULL_POINT_FROM_CALLOC;
    }
    fclose(file);

    size_t buffer_position = 0;
    error_status = fill_tree_structure(tree -> tree_root, tree, tree_buffer, &buffer_position);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    free(tree_buffer);

    return error_status;
}

char* create_file_buffer(const char* file_name, FILE* file)
{
    size_t file_size = define_file_size(file_name);
    char* text_buffer = (char*)calloc(file_size + 1, sizeof(char));
    if (text_buffer == NULL)
        return text_buffer;

    size_t file_elem_number = fread(text_buffer, sizeof(char), file_size, file);
    text_buffer[file_elem_number] = '\0';

    return text_buffer;
}

size_t define_file_size(const char* file_name)
{
    struct stat buff = {};
    stat(file_name, &buff);
    return buff.st_size;
}

error_t fill_tree_structure(struct tree_node_t* current_node, struct tree_t* tree, const char* tree_buffer, size_t* buffer_position)
{
    error_t error_status = OK;

    while (tree_buffer[*buffer_position] == ' ')
        (*buffer_position)++;

    size_t temp_increment = 0;
    if (tree_buffer[*buffer_position] == '(')
    {
        tree_node_t* node_pointer = (tree_node_t*)calloc(1, sizeof(tree_node_t));
        if (node_pointer == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }

        node_pointer -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
        if (node_pointer -> data == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }
        tree -> tree_node_num++;

        sscanf(tree_buffer + *buffer_position + 2, "%[^\"]%n", node_pointer -> data, &temp_increment);
        *buffer_position += 4 + temp_increment;

        if (tree -> tree_root == NULL)
        {
            tree -> tree_root = node_pointer;
            (tree -> tree_root) -> parent_node = NULL;
        }

        else
        {
            if (current_node -> left_node == NULL)
            {
                current_node -> left_node = node_pointer;
                (current_node -> left_node) -> parent_node = current_node;
            }
            else
            {
                current_node -> right_node = node_pointer;
                (current_node -> right_node) -> parent_node = current_node;
            }
        }

        error_status = fill_tree_structure(node_pointer, tree, tree_buffer, buffer_position);
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }

        error_status = fill_tree_structure(node_pointer, tree, tree_buffer, buffer_position);
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }

        if (tree_buffer[*buffer_position] == ')')
            *buffer_position += 1;
    }
    else if (tree_buffer[*buffer_position] == 'n')
        *buffer_position += 3;

    return error_status;
}

error_t save_tree(const char* file_name, struct tree_t* tree)
{
    error_t error_status = OK;

    FILE* file = fopen(file_name, "w");
    if (file == NULL)
    {
        FILL_DBG(CANNOT_OPEN_FILE);
        return CANNOT_OPEN_FILE;
    }

    error_status = fprintf_tree(file, tree -> tree_root);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    fclose(file);

    return error_status;
}

error_t fprintf_tree(FILE* file, struct tree_node_t* current_node)
{
    error_t error_status = OK;

    if (file == NULL)
        return NULL_FILE_POINT;

    if (current_node == NULL)
        return NULL_NODE_GIVEN;

    fprintf(file, " (");
    fprintf(file, "\"%" SPECIFICATOR "\" ", current_node -> data);
    if (current_node -> left_node)  fprintf_tree(file, current_node -> left_node);
    else fprintf(file, " nil");
    if (current_node -> right_node) fprintf_tree(file, current_node -> right_node);
    else fprintf(file, " nil");
    fprintf(file, ")");

    return error_status;
}

error_t create_tree_root(struct tree_t* tree)
{
    error_t error_status = OK;

    if (tree == NULL)
    {
        FILL_DBG(NULL_POINT_ON_TREE_STRUCT);
        return NULL_POINT_ON_TREE_STRUCT;
    }

    tree -> tree_root = (tree_node_t*)calloc(1, sizeof(tree_node_t));
    if (tree -> tree_root == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    (tree -> tree_root) -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
    if ((tree -> tree_root) -> data == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    (tree -> tree_root) -> left_node = (tree_node_t*)calloc(1, sizeof(tree_node_t));
    if ((tree -> tree_root) -> left_node == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    ((tree -> tree_root) -> left_node) -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
    if (((tree -> tree_root) -> left_node) -> data == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    (tree -> tree_root) -> right_node = (tree_node_t*)calloc(1, sizeof(tree_node_t));
    if ((tree -> tree_root) -> right_node == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    ((tree -> tree_root) -> right_node) -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
    if (((tree -> tree_root) -> right_node) -> data == NULL)
    {
        FILL_DBG(error_status);
        return NULL_POINT_FROM_CALLOC;
    }

    printf("Enter the main characteristic: ");
    scanf("%s", ((tree -> tree_root) -> data));

    printf("Now enter the answer if yes: ");
    scanf("%" SPECIFICATOR, (((tree -> tree_root) -> right_node)-> data));

    printf("And the answer if no: ");
    scanf("%" SPECIFICATOR, (((tree -> tree_root) -> left_node)-> data));

    return error_status;
}

int no_or_empty_file_created(const char* file_name)
{
    struct stat buff = {};
    if (stat(file_name, &buff) == -1)
        return 1;
    else if (buff.st_size == 0)
        return 1;
    else return 0;
}

