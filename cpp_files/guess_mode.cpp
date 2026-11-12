#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "get_tree.h"
#include "akinator.h"
#include "guess_mode.h"

#define MAX_NODE_LEN 50

error_t guess_elem(struct tree_t* tree)
{
    error_t error_status = OK;

    tree_node_t* current_node = tree -> tree_root;

    error_status = move_along_tree(&current_node);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    error_status = check_if_guessed(current_node, tree);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    return error_status;
}

error_t move_along_tree(struct tree_node_t** current_node)
{
    error_t error_status = OK;

    if (current_node == NULL)
        return NULL_NODE_GIVEN;

    while (((*current_node) -> right_node != NULL) && ((*current_node) -> left_node != NULL))
    {
        char answer[5] = {};
        printf("Is it %" SPECIFICATOR "?\n" , (*current_node) -> data);
        scanf("%s", answer);
        if (strcmp(answer, "yes") == 0)
            *current_node = (*current_node) -> right_node;
        else if (strcmp(answer, "no") == 0)
            *current_node = (*current_node) -> left_node;
        else
            printf("No such option to answer");
    }

    return error_status;
}

error_t check_if_guessed(struct tree_node_t* current_node, struct tree_t* tree)
{
    error_t error_status = OK;

    char answer[5] = {};
    printf("Is it %" SPECIFICATOR "?\n", current_node -> data);
    scanf("%s", answer);
    if (strcmp(answer, "yes") == 0)
    {
        printf("Heheheh, I told you that I'll guess\n");
        return error_status;
    }
    else if (strcmp(answer, "no") == 0)
    {
        tree -> tree_node_num += 2;
        current_node -> left_node = (tree_node_t*)calloc(1, sizeof(tree_node_t));
        if (current_node -> left_node == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }

        (current_node -> left_node) -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
        if ((current_node -> left_node) -> data == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }
        (current_node -> left_node) -> parent_node = current_node;

        current_node -> right_node = (tree_node_t*)calloc(1, sizeof(tree_node_t));
        if (current_node -> right_node == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }
        (current_node -> right_node) -> data = (char*)calloc(MAX_NODE_LEN, sizeof(char));
        if ((current_node -> right_node) -> data == NULL)
        {
            FILL_DBG(error_status);
            return NULL_POINT_FROM_CALLOC;
        }
        (current_node -> right_node) -> parent_node = current_node;

        memcpy((current_node -> left_node) -> data, current_node -> data, MAX_NODE_LEN * sizeof(char));

        printf("So what was it?: ");
        scanf("%s", (current_node -> right_node) -> data);

        printf("How does %s differ from %s?: ", (current_node -> right_node) -> data, (current_node -> left_node) -> data);
        scanf("%s", current_node -> data);
    }

    return error_status;
}
