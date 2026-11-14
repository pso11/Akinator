#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <direct.h>
#include <io.h>

#include "akinator.h"

#ifdef TREE_DEBUG
error_t tree_veryficator(struct tree_t* tree)
{
    error_t error_status = OK;

    if (tree == NULL)
        return NULL_POINT_ON_TREE_STRUCT;

    if ((tree -> tree_node_num) < 0)
    {
        FILL_DBG(WRONG_SIZE);
        return WRONG_SIZE;
    }

    if ((tree -> tree_root == NULL) && (tree -> tree_node_num != 0))
    {
        FILL_DBG(WRONG_SIZE);
        return WRONG_SIZE;
    }

    size_t visited_nodes = 0;
    error_status = node_veryficator(tree -> tree_root, &visited_nodes, tree);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    return OK;
}

error_t tree_dump(struct tree_t* tree)
{
    printf("Hiiii!!!! LOOK AT MAIN.LOG!!!\n");

    FILE* file = fopen("main.log", "a+");
    fwrite_txt_dump(tree, file);
    fclose(file);

    file = fopen("html_log.html", "a+");
    fwrite_html_dump(tree, file);
    fclose(file);

    return OK;
}

void fwrite_stars(size_t number, FILE* file)
{
    for (size_t i = 0; i < number; i++)
        fputc('*', file);
}

void fwrite_txt_dump(const struct tree_t* tree, FILE* file)
{
    fprintf_beautiful(file, "\nMEET ERROR IN YOUR PROGRAMM READ ALL INFORMATION DOWN\n");

    fprintf_error_inf(tree, file);
    fprintf_tree_data(tree, file);

    fprintf_beautiful(file, "\nEND OF OUR MESSAGE\n");
    fputc('\n', file);
}

void fwrite_graph_dump(const struct tree_t* tree)
{
    FILE* graph_file = fopen("graphic_dump.txt", "w");

    fprintf(graph_file, "digraph tree\n{\n");

    size_t depth = 0;
    fprintf_invis_edges(graph_file, tree, tree -> tree_root, &depth);
    fprintf(graph_file, "node [shape = doubleoctagon, fontsize = 28, fontname = \"Helvetica-Bold\", style = \"bold\", style = filled, fontcolor = \"#FFFF00\", fillcolor = \"#ff0000\"]\n");
    size_t visited_nodes = 0;
    fprintf_nodes(graph_file, &visited_nodes, tree -> tree_root);

    fprintf(graph_file, "}\n");
    fclose(graph_file);

    char dot_cmd[MAX_PATH_LEN] = {};
    snprintf(dot_cmd, sizeof(dot_cmd), "dot \"graphic_dump.txt\" -Tpng -o grapic_dump.png");

    system(dot_cmd);
}

void fwrite_html_dump(const struct tree_t* tree, FILE* file)
{
    fprintf(file, "<!DOCTYPE html>\n<html>\n<pre style = \"font-size: 20px;\">\n");

    fprintf_error_inf(tree, file);
    fprintf_tree_data(tree, file);
    fwrite_graph_dump(tree);

    fputc('\n', file);
    fprintf(file, "Image:\n");
    fprintf(file, "<img src =\"grapic_dump.png\">");
    fprintf_beautiful(file, "\nEND OF OUR MESSAGE\n");
    fputc('\n', file);

    system("code grapic_dump.png");

    fprintf(file, "</pre>\n</html>");
}

void fprintf_beautiful(FILE* file, const char* string)
{
    fputc('\n', file);
    fwrite_stars(25, file);
    fprintf(file,"%s", string);
    fwrite_stars(25, file);
    fputc('\n', file);
}

void fprintf_error_inf(const struct tree_t* tree, FILE* file)
{
    const char* error_description_array[] =
    {
        "Everything is OK",
        "Calloc didn't work",
        "You gave NULL pointer on tree structure",
        "You gave not existing node to the function",
        "You gave NULL pointer on file to function",
        "Couldn't open file",
        "Root pointer equals NULL, but number of nodes in tree does not",
        "Right node has wrong parent",
        "Left node has wrong parent",
        "Node has only one NULL baby",
        "Tree has cycle",
        "Root has not NULL parent"
    };

    fprintf(file, "Error code: [%d] : %s called in: %s:%d in function: %s : %s:%d\n\n",
                   tree -> error_code, error_description_array[tree -> error_code], tree -> call_file,
                   tree -> call_line, tree -> function, tree -> file, tree -> line);

    fflush(file);
}

void fprintf_tree_data(const struct tree_t* tree, FILE* file)
{
    fprintf(file, "YOUR tree: tree_t %s = [%p] created by %s():\n"
                  "root_pointer = %p\n"
                  "number of nodes = %d",
                   tree -> val_name, tree, tree -> birth_function,
                   tree -> tree_root, tree -> tree_node_num);

    fflush(file);
}

error_t node_veryficator(tree_node_t* current_node, size_t* visited_nodes, struct tree_t* tree)
{
    error_t error_status = OK;

    ++(*visited_nodes);
    if ((*visited_nodes) > (tree -> tree_node_num))
        return TREE_WITH_CYCLE;

    if ((current_node -> right_node == NULL) != (current_node -> left_node == NULL))
        return DAMAGED_LEAF_NODE;

    if (current_node -> right_node != NULL)
    {
        if ((current_node -> right_node) -> parent_node != current_node)
            return WRONG_RIGHT_PARENTNESS;
        else
        {
            error_status = node_veryficator(current_node -> right_node, visited_nodes, tree);
            if (error_status)
                return error_status;
        }
    }

    if (current_node -> left_node != NULL)
    {
        if ((current_node -> left_node) -> parent_node != current_node)
            return WRONG_LEFT_PARENTNESS;
        else
        {
            error_status = node_veryficator(current_node -> left_node, visited_nodes, tree);
            if (error_status)
                return error_status;
        }
    }

    return error_status;
}

void fprintf_node(FILE* file, struct tree_node_t* current_node, const char* label_color,
                  const char* stroke_color, const char* fill_color)
{
    fprintf(file,  "   \"%p\" [style = filled, fontcolor = \"%s\", fillcolor = \"%s\", color = \"%s\", shape = Mrecord, label = \" "
                        "{data = %" SPECIFICATOR " | {left_node = %p | right_node = %p} | {node = %p | parent_node =  %p}} \"];\n",
                        current_node, label_color, fill_color, stroke_color, current_node -> data, current_node -> left_node,
                        current_node -> right_node, current_node, current_node -> parent_node);
}

void fprintf_edge(FILE* file, struct tree_node_t* current_node, struct tree_node_t* linked_node,
                  const char* line_status, const char* edge_color, double penwidth, const char* label)
{
    fprintf(file,  "   \"%p\" -> \"%p\" [%s, color = \"%s\", penwidth = %lg, label = \"%s\"];\n",
                    current_node, linked_node, line_status, edge_color, penwidth, label);
}

void fprintf_invis_edges(FILE* file, const struct tree_t* tree, tree_node_t* current_node, size_t* depth)
{
    (*depth)++;

    if (current_node -> left_node)
    {
        fprintf(file, "\"%p\" -> \"%p\"  [style = invis, weight = 1000, rank = %d];\n", current_node, current_node -> left_node, *depth);
        fprintf_invis_edges(file, tree, current_node -> left_node, depth);
    }

    if (current_node -> right_node)
    {
        fprintf(file, "\"%p\" -> \"%p\"  [style = invis, weight = 1000, rank = %d];\n", current_node, current_node -> right_node, *depth);
        fprintf_invis_edges(file, tree, current_node -> right_node, depth);
    }

}

void fprintf_nodes(FILE* file, size_t* visited_nodes, tree_node_t* current_node)
{
    error_t error_status = OK;

    fprintf_node(file, current_node, "#000000", "#000000", "#bce1ed");
    (*visited_nodes)++;

    if (current_node -> right_node)
    {
        fprintf_edge(file, current_node, current_node -> right_node, "dir = both", "#55c3dc", 1.0, "yes");
        fprintf_nodes(file, visited_nodes, current_node -> right_node);
    }

    if (current_node -> left_node)
    {
        fprintf_edge(file, current_node, current_node -> left_node, "dir = both", "#93c63a", 1.0, "no");
        fprintf_nodes(file, visited_nodes, current_node -> left_node);
    }

    fflush(file);
}

#endif
