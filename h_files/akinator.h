#ifdef TREE_USE_INT
    typedef int tree_elem_t;
    #define SPECIFICATOR "d"
#elif TREE_USE_DOUBLE
    typedef double tree_elem_t;
    #define SPECIFICATOR "lg"
#elif TREE_USE_CHAR
    typedef char* tree_elem_t;
    #define SPECIFICATOR "s"
#else
    #error "Error: Neither TREE_USE_INT nor TREE_USE_DOUBLE is defined!"
#endif

#include "error_codes.h"

struct tree_node_t
{
    tree_elem_t data;
    tree_node_t* left_node;
    tree_node_t* right_node;
    tree_node_t* parent_node;
};

struct tree_t
{
    #ifdef TREE_DEBUG
        size_t line;
        const char* file;
        const char* call_file;
        size_t call_line;
        const char* function;
        const char* birth_function;
        const char* val_name;
        error_t error_code;
        char* project_dir_path;
        size_t dump_num;
        int add_or_del_status;
        int add_or_del_elem;
    #endif
    tree_node_t* tree_root;
    int tree_node_num;
};

#ifdef TREE_DEBUG
    error_t tree_dump(struct tree_t* tree);
    void fwrite_txt_dump(const struct tree_t* tree, FILE* file);
    void fwrite_graph_dump(const struct tree_t* tree);
    void fwrite_html_dump(const struct tree_t* tree, FILE* file);
    void define_log_file(struct tree_t* tree);
    size_t define_run_number(const char* file_name);
    void fwrite_stars(size_t number, FILE* file);
    void fprintf_invis_edges(FILE* file, const struct tree_t* tree, tree_node_t* current_node, size_t* depth);
    void fprintf_nodes(FILE* file, size_t* visited_nodes, tree_node_t* current_node);
    void fprintf_beautiful(FILE* file_name, const char* string);
    void fprintf_error_inf(const struct tree_t* tree, FILE* file);
    void fprintf_tree_data(const struct tree_t* tree, FILE* file);
    error_t node_veryficator(tree_node_t* current_node, int* visited_nodes, struct tree_t* tree);
    error_t tree_veryficator(struct tree_t* tree);
    void fprintf_edge(FILE* file, struct tree_node_t* current_node, struct tree_node_t* linked_node,
                      const char* line_status, const char* edge_color, double penwidth, const char* label);
    void fprintf_node(FILE* file, struct tree_node_t* current_node, const char* label_color,
                      const char* stroke_color, const char* fill_color);


    struct error
    {
        const char* description;
        error_t error_name;
    };

    #define MAX_PATH_LEN 100
    #define MAX_FILE_NAME_LEN 15
    #define MAX_ANSWER_NAME 25

    #define FILL_DBG(error)                \
        tree -> line       = __LINE__ ;    \
        tree -> file       = __FILE__;     \
        tree -> function   = __FUNCTION__;

    #define TREE_VERYFICATION(tree)            \
        error_status = tree_veryficator(tree); \
        if (error_status)                      \
        {                                      \
            FILL_DBG(error_status);            \
            return error_status;               \
        }

    #define ASSERT(tree, error_status)               \
            if (error_status)                        \
            {                                        \
                tree.error_code = error_status;      \
                tree.call_file = __FILE__ ;          \
                tree.call_line = __LINE__;           \
                tree_dump(&tree);                    \
                tree_destroy(&tree,  tree.tree_root);\
                return 0;                            \
            }
    #define DUMP_INIT(tree)                     \
            tree.val_name = #tree;              \
            tree.birth_function = __FUNCTION__; \

    #define DEFINE_LOG_FILE(argument) define_log_file(argument)
#else
    #define FILL_DBG(error)             ;
    #define TREE_VERYFICATION(tree)     ;
    #define ASSERT(tree, error_status)  ;
    #define DEFINE_LOG_FILE()           ;
    #define DUMP_INIT(tree)             ;
#endif


error_t tree_init(struct tree_t* tree);
error_t tree_destroy(struct tree_t* tree, struct tree_node_t* current_node);
size_t ask_user_mode(void);

