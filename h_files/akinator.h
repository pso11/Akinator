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

error_t tree_init(struct tree_t* tree);
error_t tree_destroy(struct tree_t* tree, struct tree_node_t* current_node);
size_t ask_user_mode(void);

