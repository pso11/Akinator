
#include "error_codes.h"

tree_error_t guess_elem(tree_t* tree);
tree_error_t move_along_tree(tree_node_t** current_node);
tree_error_t check_answer(char* answer, tree_node_t* current_node, tree_t* tree);
tree_error_t check_if_guessed(tree_node_t* current_node, tree_t* tree);
char* get_answer(tree_node_t* current_node);
void link_children(tree_node_t* current_node);
void get_new_data(tree_node_t* current_node);
