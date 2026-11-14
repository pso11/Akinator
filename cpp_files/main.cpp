#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "akinator.h"
#include "error_codes.h"
#include "get_tree.h"
#include "guess_mode.h"
#include "functions_array.h"

int main(const int argc, const char* argv[])
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    error_t error_status = OK;
    struct tree_t tree = {};
    DUMP_INIT(tree);

    error_status = tree_init(&tree);
    ASSERT(tree, error_status);

    size_t chosen_mode = 0;
    while ((chosen_mode = ask_user_mode()) != 3)
    {
        error_status = get_tree(argv[1], &tree);
        ASSERT(tree, error_status);

        error_status = mode_array[chosen_mode - 1](&tree);
        ASSERT(tree, error_status);

        error_status = save_tree(argv[1], &tree);
        ASSERT(tree, error_status);

        error_status = tree_destroy(&tree, tree.tree_root);
        ASSERT(tree, error_status);

    }
    return 0;
}
