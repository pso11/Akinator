#include "error_codes.h"

#pragma once
#include "stack.h"

tree_error_t define_elem(tree_t* tree);
tree_error_t find_tree_elem(tree_elem_t data, tree_node_t** def_elem, tree_node_t* current_node);
stack_error_t fill_stack(stack_t* stk, tree_node_t* def_elem);
stack_error_t write_stack(stack_t* stk, tree_node_t* def_elem);
stack_error_t stack_init_and_fill(tree_node_t* def_elem, stack_t* stk);
tree_error_t get_tree_elem(tree_node_t** def_elem, tree_t* tree);
