#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "compare_mode.h"
#include "define_mode.h"
#include "get_tree.h"
#include "my_txSpeak.h"

tree_error_t compare_elements(struct tree_t* tree)
{
    tree_error_t  tree_error_status  = OK;
    stack_error_t stack_error_status = STACK_OK;

    tree_node_t* def_elem_1 = NULL;
    tree_node_t* def_elem_2 = NULL;

    tree_error_status = get_tree_elem(&def_elem_1, tree);
    if (tree_error_status)
    {
        FILL_DBG(tree_error_status);
        return tree_error_status;
    }
    if (def_elem_1 == NULL)
    {
        txSpeak_no_tree_elem();
        return tree_error_status;
    }

    tree_error_status = get_tree_elem(&def_elem_2, tree);
    if (tree_error_status)
    {
        FILL_DBG(tree_error_status);
        return tree_error_status;
    }
    if (def_elem_2 == NULL)
    {
        txSpeak_no_tree_elem();
        return tree_error_status;
    }

    struct stack_t stk1 = {};
    struct stack_t stk2 = {};
    stack_error_status = stack_init_and_fill(def_elem_1, &stk1);
    if (stack_error_status)
    {
        FILL_DBG(stack_error_status);
        return DAMAGED_STACK_TREE;
    }

    stack_error_status = stack_init_and_fill(def_elem_2, &stk2);
    if (stack_error_status)
    {
        FILL_DBG(stack_error_status);
        return DAMAGED_STACK_TREE;
    }

    stack_error_status = write_compare_stack_inf(def_elem_1, def_elem_2, &stk2, &stk1);
    if (stack_error_status)
    {
        FILL_DBG(stack_error_status);
        return DAMAGED_STACK_TREE;
    }

    return tree_error_status;
}

stack_error_t write_compare_stack_inf(struct tree_node_t* def_elem_1, struct tree_node_t* def_elem_2,
                                      struct stack_t* stk2, struct stack_t* stk1)
{
    stack_error_t error_status = STACK_OK;

    tree_node_t* poped_value_1 = 0;
    tree_node_t* poped_value_2 = 0;

    error_status = stack_pop(stk1, &poped_value_1);
    error_status = stack_pop(stk2, &poped_value_2);

    error_status = write_same_inf(&poped_value_1, &poped_value_2, def_elem_1, def_elem_2, stk2, stk1);
    if (error_status)
        return error_status;

    error_status = write_dif_inf(poped_value_1, def_elem_1, stk1);
    if (error_status)
        return error_status;

    error_status = write_dif_inf(poped_value_2, def_elem_2, stk2);
    if (error_status)
        return error_status;

    return error_status;
}

stack_error_t write_same_inf(struct tree_node_t** poped_value_1, struct tree_node_t** poped_value_2,
                             struct tree_node_t* def_elem_1, struct tree_node_t* def_elem_2,
                             struct stack_t* stk2, struct stack_t* stk1)
{
    stack_error_t error_status = STACK_OK;

    if (*poped_value_1 == *poped_value_2)
    {
        txSpeak_same_intro(def_elem_1 -> data, def_elem_2 -> data);
        while (*poped_value_1 == *poped_value_2)
        {
            if (*poped_value_1 == NULL)
                txSpeak_no();
            else
                txSpeak_poped_val((*poped_value_1) -> data);

            if  (stk1 -> size != 0)
                error_status = stack_pop(stk1, poped_value_1);
            if (stk2 -> size != 0)
                error_status = stack_pop(stk2, poped_value_2);

            if (error_status)
                return error_status;
        }
        putchar('\n');
    }
    else txSpeak_no_same_elem();

    return error_status;
}

stack_error_t write_dif_inf(struct tree_node_t* poped_value, struct tree_node_t* def_elem, struct stack_t* stk)
{
    stack_error_t error_status = STACK_OK;

    txSpeak_poped_val(def_elem -> data);
    while (stk -> size != 0)
    {
        if (poped_value == NULL)
           txSpeak_no();
        else
            txSpeak_poped_val(poped_value -> data);

        error_status = stack_pop(stk, &poped_value);
        if (error_status)
            return error_status;
    }
    txSpeak_poped_val(poped_value -> data);
    putchar('\n');

    return error_status;
}
