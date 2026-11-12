
#include "error_codes.h"

error_t get_tree(const char* file_name, struct tree_t* tree);
error_t save_tree(const char* file_name, struct tree_t* tree);
char* create_file_buffer(const char* file_name, FILE* file);
error_t fprintf_tree(FILE* file, struct tree_node_t* current_node);
size_t define_file_size(const char* file_name);
error_t fill_tree_structure(struct tree_node_t* current_node, struct tree_t* tree, const char* tree_buffer, size_t* buffer_position);
error_t create_tree_root(struct tree_t* tree);
int no_or_empty_file_created(const char* file_name);
error_t create_one_node(struct tree_node_t** node_to_create);
void link_nodes(struct tree_t* tree, struct tree_node_t* node_pointer, struct tree_node_t* current_node);

#define MAX_NODE_LEN 50
