#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <direct.h>
#include <io.h>

#include "akinator.h"
#include "show_tree.h"

#ifdef TREE_DEBUG
tree_error_t tree_veryficator(struct tree_t* tree)
{
    tree_error_t error_status = OK;

    if (tree == NULL)
        return NULL_POINT_ON_TREE_STRUCT;

    if ((tree -> tree_node_num) < 0)
    {
        FILL_DBG(WRONG_SIZE);
        return WRONG_SIZE;
    }

    if ((tree -> tree_root == NULL) && (tree -> tree_node_num != 0))
    {
        FILL_DBG(WRONG_SIZE);
        return WRONG_SIZE;
    }

    int visited_nodes = 0;
    error_status = node_veryficator(tree -> tree_root, &visited_nodes, tree);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    return OK;
}

tree_error_t tree_dump(struct tree_t* tree)
{
    txSpeak("\vHiiii!!!! LOOK AT MAIN.LOG!!!\n");

    FILE* file = fopen("main.log", "a+");
    fwrite_txt_dump(tree, file);
    fclose(file);

    file = fopen("html_log.html", "a+");
    fwrite_html_dump(tree, file);
    fclose(file);

    return OK;
}

void fwrite_stars(size_t number, FILE* file)
{
    for (size_t i = 0; i < number; i++)
        fputc('*', file);
}

void fwrite_txt_dump(const struct tree_t* tree, FILE* file)
{
    fprintf_beautiful(file, "\nMEET ERROR IN YOUR PROGRAMM READ ALL INFORMATION DOWN\n");

    fprintf_error_inf(tree, file);
    fprintf_tree_data(tree, file);

    fprintf_beautiful(file, "\nEND OF OUR MESSAGE\n");
    fputc('\n', file);
}

void fwrite_html_dump(const struct tree_t* tree, FILE* file)
{
    fprintf(file, "<!DOCTYPE html>\n<html>\n<pre style = \"font-size: 20px;\">\n");

    fprintf_error_inf(tree, file);
    fprintf_tree_data(tree, file);
    fwrite_graph_dump(tree);

    fputc('\n', file);
    fprintf(file, "Image:\n");
    fprintf(file, "<img src =\"grapic_dump.png\">");
    fprintf_beautiful(file, "\nEND OF OUR MESSAGE\n");
    fputc('\n', file);

    system("code grapic_dump.png");

    fprintf(file, "</pre>\n</html>");
}

void fprintf_beautiful(FILE* file, const char* string)
{
    fputc('\n', file);
    fwrite_stars(25, file);
    fprintf(file,"%s", string);
    fwrite_stars(25, file);
    fputc('\n', file);
}

void fprintf_error_inf(const struct tree_t* tree, FILE* file)
{
    const char* error_description_array[] =
    {
        "Everything is OK",
        "Calloc didn't work",
        "You gave NULL pointer on tree structure",
        "You gave not existing node to the function",
        "You gave NULL pointer on file to function",
        "Couldn't open file",
        "Root pointer equals NULL, but number of nodes in tree does not",
        "Right node has wrong parent",
        "Left node has wrong parent",
        "Node has only one NULL baby",
        "Tree has cycle",
        "Root has not NULL parent",
        "Stack error -> check error code"
    };

    fprintf(file, "Error code: [%d] : %s called in: %s:%zu in function: %s : %s:%zu\n\n",
                   tree -> error_code, error_description_array[tree -> error_code], tree -> call_file,
                   tree -> call_line, tree -> function, tree -> file, tree -> line);

    fflush(file);
}

void fprintf_tree_data(const struct tree_t* tree, FILE* file)
{
    fprintf(file, "YOUR tree: tree_t %s = [%p] created by %s():\n"
                  "root_pointer = %p\n"
                  "number of nodes = %d",
                   tree -> val_name, tree, tree -> birth_function,
                   tree -> tree_root, tree -> tree_node_num);

    fflush(file);
}

tree_error_t node_veryficator(tree_node_t* current_node, int* visited_nodes, struct tree_t* tree)
{
    tree_error_t error_status = OK;

    ++(*visited_nodes);
    if ((*visited_nodes) > (tree -> tree_node_num))
        return TREE_WITH_CYCLE;

    if ((current_node -> right_node == NULL) != (current_node -> left_node == NULL))
        return DAMAGED_LEAF_NODE;

    if (current_node -> right_node != NULL)
    {
        if ((current_node -> right_node) -> parent_node != current_node)
            return WRONG_RIGHT_PARENTNESS;
        else
        {
            error_status = node_veryficator(current_node -> right_node, visited_nodes, tree);
            if (error_status)
                return error_status;
        }
    }

    if (current_node -> left_node != NULL)
    {
        if ((current_node -> left_node) -> parent_node != current_node)
            return WRONG_LEFT_PARENTNESS;
        else
        {
            error_status = node_veryficator(current_node -> left_node, visited_nodes, tree);
            if (error_status)
                return error_status;
        }
    }

    return error_status;
}

#endif
