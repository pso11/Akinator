#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "akinator.h"
#include "show_tree.h"
#include "get_tree.h"

tree_error_t show_tree(tree_t* tree)
{
    tree_error_t error_status = OK;
    fwrite_graph_dump(tree);

    system("start \"\" \"grapic_dump.png\"");
    return error_status;
}

void fwrite_graph_dump(const tree_t* tree)
{
    FILE* graph_file = fopen("graphic_dump.txt", "w");

    fprintf(graph_file, "digraph tree\n{\n");

    size_t depth = 0;
    fprintf_invis_edges(graph_file, tree, tree -> tree_root, &depth);
    fprintf(graph_file, "node [shape = doubleoctagon, fontsize = 28, fontname = \"Helvetica-Bold\", style = \"bold\", style = filled, fontcolor = \"#FFFF00\", fillcolor = \"#ff0000\"]\n");
    size_t visited_nodes = 0;
    fprintf_nodes(graph_file, &visited_nodes, tree -> tree_root, "#c890f6");

    fprintf(graph_file, "}\n");
    fclose(graph_file);

    char dot_cmd[MAX_PATH_LEN] = {};
    snprintf(dot_cmd, sizeof(dot_cmd), "dot \"graphic_dump.txt\" -Tpng -o grapic_dump.png");

    system(dot_cmd);
}

void fprintf_node(FILE* file, tree_node_t* current_node, const char* label_color,
                  const char* stroke_color, const char* fill_color)
{
    char* translit_data = turn_to_translit(current_node -> data);

    fprintf(file,  "   \"%p\" [style = filled, fontcolor = \"%s\", fillcolor = \"%s\", color = \"%s\", shape = Mrecord, label = \" "
                        "{data = %" TREE_SPECIFICATOR " | {left_node = %p | right_node = %p} | {node = %p | parent_node =  %p}} \"];\n",
                        current_node, label_color, fill_color, stroke_color, translit_data, current_node -> left_node,
                        current_node -> right_node, current_node, current_node -> parent_node);

    free(translit_data);
}

void fprintf_edge(FILE* file, tree_node_t* current_node, tree_node_t* linked_node,
                  const char* line_status, const char* edge_color, double penwidth, const char* label)
{
    fprintf(file,  "   \"%p\" -> \"%p\" [%s, color = \"%s\", penwidth = %lg, label = \"%s\"];\n",
                    current_node, linked_node, line_status, edge_color, penwidth, label);
}

void fprintf_invis_edges(FILE* file, const tree_t* tree, tree_node_t* current_node, size_t* depth)
{
    (*depth)++;

    if (current_node -> left_node)
    {
        fprintf(file, "\"%p\" -> \"%p\"  [style = invis, weight = 1000, rank = %lld];\n", current_node, current_node -> left_node, *depth);
        fprintf_invis_edges(file, tree, current_node -> left_node, depth);
    }

    if (current_node -> right_node)
    {
        fprintf(file, "\"%p\" -> \"%p\"  [style = invis, weight = 1000, rank = %lld];\n", current_node, current_node -> right_node, *depth);
        fprintf_invis_edges(file, tree, current_node -> right_node, depth);
    }

}

void fprintf_nodes(FILE* file, size_t* visited_nodes, tree_node_t* current_node, const char* fill_color)
{
    fprintf_node(file, current_node, "#000000", "#000000", fill_color);
    (*visited_nodes)++;

    if (current_node -> right_node)
    {
        fprintf_edge(file, current_node, current_node -> right_node, "dir = both", "#55c3dc", 1.0, "yes");
        fprintf_nodes(file, visited_nodes, current_node -> right_node, "#93d7e6");
    }

    if (current_node -> left_node)
    {
        fprintf_edge(file, current_node, current_node -> left_node, "dir = both", "#93c63a", 1.0, "no");
        fprintf_nodes(file, visited_nodes, current_node -> left_node, "#ccee91");
    }

    fflush(file);
}

const char* get_translit_letter(const char letter)
{
    switch (letter)
    {
        case 'À': case 'à': return "a";
        case 'Á': case 'á': return "b";
        case 'Â': case 'â': return "v";
        case 'Ã': case 'ã': return "g";
        case 'Ä': case 'ä': return "d";
        case 'Å': case 'å': return "e";
        case '¨': case '¸': return "yo";
        case 'Æ': case 'æ': return "zh";
        case 'Ç': case 'ç': return "z";
        case 'È': case 'è': return "i";
        case 'É': case 'é': return "j";
        case 'Ê': case 'ê': return "k";
        case 'Ë': case 'ë': return "l";
        case 'Ì': case 'ì': return "m";
        case 'Í': case 'í': return "n";
        case 'Î': case 'î': return "o";
        case 'Ï': case 'ï': return "p";
        case 'Ğ': case 'ğ': return "r";
        case 'Ñ': case 'ñ': return "s";
        case 'Ò': case 'ò': return "t";
        case 'Ó': case 'ó': return "u";
        case 'Ô': case 'ô': return "f";
        case 'Õ': case 'õ': return "kh";
        case 'Ö': case 'ö': return "ts";
        case '×': case '÷': return "ch";
        case 'Ø': case 'ø': return "sh";
        case 'Ù': case 'ù': return "shch";
        case 'Ú': case 'ú': return "";
        case 'Û': case 'û': return "y";
        case 'Ü': case 'ü': return "";
        case 'İ': case 'ı': return "e";
        case 'Ş': case 'ş': return "yu";
        case 'ß': case 'ÿ': return "ya";
        case ' ': return " ";
        default: return NULL;
    }
}

char* turn_to_translit(tree_elem_t data)
{
    char* translit_data = (char*)calloc(MAX_NODE_LEN, sizeof(tree_elem_t));
    translit_data[0] = '\0';

    for(size_t letter = 0; data[letter] != '\0'; letter++)
        strcat(translit_data, get_translit_letter(data[letter]));

    return translit_data;
}
