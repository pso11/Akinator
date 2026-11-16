#include "error_codes.h"

#pragma once
#include "stack.h"

stack_error_t write_compare_stack_inf(struct tree_node_t* def_elem_1, struct tree_node_t* def_elem_2,
                                      struct stack_t* stk2, struct stack_t* stk1);
tree_error_t compare_elements(struct tree_t* tree);
stack_error_t write_same_inf(struct tree_node_t* poped_value_1, struct tree_node_t* poped_value_2,
                             struct tree_node_t* def_elem_1, struct tree_node_t* def_elem_2,
                             struct stack_t* stk2, struct stack_t* stk1);
stack_error_t write_dif_inf(struct tree_node_t* poped_value, struct tree_node_t* def_elem, struct stack_t* stk);
