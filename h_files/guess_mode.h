
#include "error_codes.h"

error_t guess_elem(struct tree_t* tree);
error_t move_along_tree(struct tree_node_t** current_node);
error_t check_answer(char* answer, struct tree_node_t* current_node, struct tree_t* tree);
error_t check_if_guessed(struct tree_node_t* current_node, struct tree_t* tree);
char* get_answer(struct tree_node_t* current_node);
void link_children(struct tree_node_t* current_node);
void get_new_data(struct tree_node_t* current_node);
