#include "error_codes.h"

void fwrite_graph_dump(const tree_t* tree);
void fprintf_nodes(FILE* file, size_t* visited_nodes, tree_node_t* current_node, const char* fill_color);
void fprintf_edge(FILE* file, tree_node_t* current_node, tree_node_t* linked_node,
                      const char* line_status, const char* edge_color, double penwidth, const char* label);
void fprintf_node(FILE* file, tree_node_t* current_node, const char* label_color,
                  const char* stroke_color, const char* fill_color);
void fprintf_invis_edges(FILE* file, const tree_t* tree, tree_node_t* current_node, size_t* depth);
tree_error_t show_tree(tree_t* tree);
const char* get_translit_letter(const char letter);
char* turn_to_translit(tree_elem_t data);
