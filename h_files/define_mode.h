#include "error_codes.h"

#pragma once
#include "stack.h"

tree_error_t define_elem(struct tree_t* tree);
tree_error_t find_tree_elem(tree_elem_t data, struct tree_node_t** def_elem, struct tree_node_t* current_node);
stack_error_t fill_stack(struct stack_t* stk, struct tree_node_t* def_elem);
stack_error_t write_stack(struct stack_t* stk, struct tree_node_t* def_elem);
stack_error_t stack_init_and_fill(struct tree_node_t* def_elem, struct stack_t* stk);
tree_error_t get_tree_elem(struct tree_node_t** def_elem, struct tree_t* tree);
