#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "get_tree.h"
#include "akinator.h"
#include "guess_mode.h"
#include "my_txSpeak.h"

tree_error_t guess_elem(tree_t* tree)
{
    tree_error_t error_status = OK;

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

tree_error_t move_along_tree(tree_node_t** current_node)
{
    tree_error_t error_status = OK;

    if (current_node == NULL)
        return NULL_NODE_GIVEN;

    while (((*current_node) -> right_node != NULL) && ((*current_node) -> left_node != NULL))
    {
        int answer = tx_get_answer(*current_node);

        if (answer == 1)
            *current_node = (*current_node) -> right_node;
        else if (answer == 2)
            *current_node = (*current_node) -> left_node;
    }

    return error_status;
}

tree_error_t check_if_guessed(tree_node_t* current_node, tree_t* tree)
{
    tree_error_t error_status = OK;

    int answer = tx_get_answer(current_node);
    if (answer == 1)
        txSpeak_shure_answer();

    else if (answer == 2)
    {
        tree -> tree_node_num += 2;

        error_status = create_one_node(&(current_node -> left_node));
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }

        error_status = create_one_node(&(current_node -> right_node));
        if (error_status)
        {
            FILL_DBG(error_status);
            return error_status;
        }

        link_children(current_node);

        memcpy((current_node -> left_node) -> data, current_node -> data, MAX_NODE_LEN * sizeof(char));
        get_new_data(current_node);
    }

    return error_status;
}

void link_children(tree_node_t* current_node)
{
    (current_node -> left_node) -> parent_node = current_node;
    (current_node -> right_node) -> parent_node = current_node;
}

void get_new_data(tree_node_t* current_node)
{
    _txConsole = -1;

    txSpeak_apologize();
    strcpy((current_node -> right_node) -> data, txInputBox());

    txSpeak_ask_differences((current_node -> right_node) -> data, (current_node -> left_node) -> data);
    strcpy(current_node -> data, txInputBox());
}
