#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "error_codes.h"

error_t tree_init(struct tree_t* tree)
{
    error_t error_status = OK;

    if (tree == NULL)
    {
        FILL_DBG(NULL_POINT_ON_TREE_STRUCT);
        return NULL_POINT_ON_TREE_STRUCT;
    }

    tree -> tree_root = NULL;
    tree -> tree_node_num = 0;

    return error_status;
}

error_t tree_destroy(struct tree_t* tree, struct tree_node_t* current_node)
{
    error_t error_status = OK;

    if (tree == NULL)
    {
        FILL_DBG(NULL_POINT_ON_TREE_STRUCT);
        return NULL_POINT_ON_TREE_STRUCT;
    }

    if (current_node -> left_node != NULL)
    {
        error_status = tree_destroy(tree, current_node -> left_node);
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }
    }
    if (current_node -> right_node != NULL)
    {
        error_status = tree_destroy(tree, current_node -> right_node);
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }
    }

    free(current_node -> data);
    current_node -> data = NULL;

    if (current_node == tree -> tree_root)
        tree -> tree_root = NULL;

    free(current_node);
    current_node = NULL;

    return error_status;
}

size_t ask_user_mode(void)
{
    printf("Hello, I'm Siri. Choose mode to start       \n"
           "(1). Guess              (2). Show tree      \n"
           "(3). Stop                                   \n");

    size_t chosen_mode = 0;
    scanf("%d", &chosen_mode);

    return chosen_mode;
}






