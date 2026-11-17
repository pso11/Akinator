#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "akinator.h"
#include "my_txSpeak.h"

tree_error_t tree_init(tree_t* tree)
{
    tree_error_t error_status = OK;

    if (tree == NULL)
    {
        FILL_DBG(NULL_POINT_ON_TREE_STRUCT);
        return NULL_POINT_ON_TREE_STRUCT;
    }

    tree -> tree_root = NULL;
    tree -> tree_node_num = 0;

    return error_status;
}

tree_error_t tree_destroy(tree_t* tree, tree_node_t* current_node)
{
    tree_error_t error_status = OK;

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
    txSpeak_introduction();
    printf("(1). Отгадывание              (2). Показать дерево\n"
           "(3). Определение              (4). Сравнение      \n"
           "(5). Выйти\n");

    size_t chosen_mode = 0;
    scanf("%zu", &chosen_mode);

    return chosen_mode;
}






