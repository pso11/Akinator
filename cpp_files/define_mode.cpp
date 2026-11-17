#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "define_mode.h"
#include "get_tree.h"
#include "my_txSpeak.h"

tree_error_t define_elem(tree_t* tree)
{
    tree_error_t  tree_error_status  = OK;
    stack_error_t stack_error_status = STACK_OK;

    tree_node_t* def_elem = NULL;
    tree_error_status = get_tree_elem(&def_elem, tree);
    if (tree_error_status)
    {
        FILL_DBG(tree_error_status);
        return tree_error_status;
    }
    if (def_elem == NULL)
    {
        txSpeak_no_tree_elem();
        return tree_error_status;
    }

    stack_t stk = {};
    stack_error_status = stack_init_and_fill(def_elem, &stk);
    if (stack_error_status)
    {
        FILL_DBG(stack_error_status);
        return DAMAGED_STACK_TREE;
    }

    stack_error_status = write_stack(&stk, def_elem);
    if (stack_error_status)
    {
        FILL_DBG(stack_error_status);
        return DAMAGED_STACK_TREE;
    }

    return tree_error_status;
}

tree_error_t find_tree_elem(tree_elem_t data, tree_node_t** def_elem, tree_node_t* current_node)
{
    tree_error_t error_status = OK;

    if (def_elem == NULL)
        return NULL_NODE_GIVEN;

    if (strcmp(data, current_node -> data) == 0)
    {
        *def_elem = current_node;
        return error_status;
    }

    if (current_node -> left_node != NULL)
        error_status = find_tree_elem(data, def_elem, current_node -> left_node);

    if ((current_node -> right_node != NULL) && (*def_elem == NULL))
        error_status = find_tree_elem(data, def_elem, current_node -> right_node);

    return error_status;
}

stack_error_t fill_stack(stack_t* stk, tree_node_t* def_elem)
{
    stack_error_t error_status = STACK_OK;

    while (def_elem -> parent_node != NULL)
    {
        error_status = stack_push(stk, def_elem -> parent_node);
        if (error_status)
            return error_status;

        if ((def_elem -> parent_node) -> left_node == def_elem)
            error_status = stack_push(stk, NULL);

        if (error_status)
            return error_status;

        def_elem = def_elem -> parent_node;
    }

    return error_status;
}

stack_error_t write_stack(stack_t* stk, tree_node_t* def_elem)
{
    stack_error_t error_status = STACK_OK;

    tree_node_t* poped_value = 0;
    txSpeak_poped_val(def_elem -> data);
    while (stk -> size != 0)
    {
        error_status = stack_pop(stk, &poped_value);

        if (poped_value == NULL)
            txSpeak_no();
        else
            txSpeak_poped_val(poped_value -> data);
    }
    putchar('\n');

    return error_status;
}

tree_error_t get_tree_elem(tree_node_t** def_elem, tree_t* tree)
{
    tree_error_t tree_error_status = OK;

    txSpeak_enter_word();
    char data[MAX_NODE_LEN] = {};
    scanf("\n%[^\n]" TREE_SPECIFICATOR, data);

    tree_error_status = find_tree_elem(data, def_elem, tree -> tree_root);

    return tree_error_status;
}

stack_error_t stack_init_and_fill(tree_node_t* def_elem, stack_t* stk)
{
    stack_error_t stack_error_status = STACK_OK;

    stack_error_status = stack_init(stk, 10);
    if (stack_error_status)
        return stack_error_status;

    stack_error_status = fill_stack(stk, def_elem);
    if (stack_error_status)
        return stack_error_status;

    return stack_error_status;
}
