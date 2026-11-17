
#include "error_codes.h"
struct tree_node_t;
struct tree_t;

tree_error_t get_tree(const char* file_name, tree_t* tree);
tree_error_t save_tree(const char* file_name, tree_t* tree);
char* create_file_buffer(const char* file_name, FILE* file);
tree_error_t fprintf_tree(FILE* file, tree_node_t* current_node);
size_t define_file_size(const char* file_name);
tree_error_t fill_tree_structure(tree_node_t* current_node, tree_t* tree, const char* tree_buffer, size_t* buffer_position);
tree_error_t create_tree_root(tree_t* tree);
int no_or_empty_file_created(const char* file_name);
tree_error_t create_one_node(tree_node_t** node_to_create);
void link_nodes(tree_t* tree, tree_node_t* node_pointer, tree_node_t* current_node);


#define MAX_NODE_LEN 100
