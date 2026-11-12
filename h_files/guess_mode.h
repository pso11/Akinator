
#include "error_codes.h"

error_t guess_elem(struct tree_t* tree);
error_t move_along_tree(struct tree_node_t** current_node);

error_t check_if_guessed(struct tree_node_t* current_node, struct tree_t* tree);
