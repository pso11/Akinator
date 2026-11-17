#include "error_codes.h"

#pragma once
#include "stack.h"

stack_error_t write_compare_stack_inf(tree_node_t* def_elem_1, tree_node_t* def_elem_2,
                                      stack_t* stk2, stack_t* stk1);
tree_error_t compare_elements(tree_t* tree);
stack_error_t write_same_inf(tree_node_t** poped_value_1, tree_node_t** poped_value_2,
                             tree_node_t* def_elem_1, tree_node_t* def_elem_2,
                             stack_t* stk2, stack_t* stk1);
stack_error_t write_dif_inf(tree_node_t* poped_value, tree_node_t* def_elem, stack_t* stk);
