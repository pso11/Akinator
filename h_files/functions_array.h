struct tree_t;

tree_error_t (*mode_array[])(tree_t* tree) =
{
    &guess_elem,
    &show_tree,
    &define_elem,
    &compare_elements
};
