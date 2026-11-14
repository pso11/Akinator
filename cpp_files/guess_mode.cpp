#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_codes.h"
#include "get_tree.h"
#include "akinator.h"
#include "dump.h"
#include "guess_mode.h"

error_t guess_elem(struct tree_t* tree)
{
    error_t error_status = OK;

    tree_node_t* current_node = tree -> tree_root;

    error_status = move_along_tree(&current_node);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    error_status = check_if_guessed(current_node, tree);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    return error_status;
}

error_t move_along_tree(struct tree_node_t** current_node)
{
    error_t error_status = OK;

    if (current_node == NULL)
        return NULL_NODE_GIVEN;

    while (((*current_node) -> right_node != NULL) && ((*current_node) -> left_node != NULL))
    {
        char* answer = get_answer(*current_node);

        if (strcmp(answer, "да") == 0)
            *current_node = (*current_node) -> right_node;
        else if (strcmp(answer, "нет") == 0)
            *current_node = (*current_node) -> left_node;
        else
            printf("Такого варианта ответа нет\n");

        free(answer);
    }

    return error_status;
}

error_t check_if_guessed(struct tree_node_t* current_node, struct tree_t* tree)
{
    error_t error_status = OK;

    char* answer = get_answer(current_node);

    error_status = check_answer(answer, current_node, tree);
    if (error_status)
    {
        FILL_DBG(error_status);
        return error_status;
    }

    free(answer);

    return error_status;
}

char* get_answer(struct tree_node_t* current_node)
{
    char* answer = (char*)calloc(MAX_ANSWER_NAME, sizeof(char));
    printf("Это %" SPECIFICATOR "?\n", current_node -> data);
    scanf("%s", answer);

    return answer;
}
 error_t check_answer(char* answer, struct tree_node_t* current_node, struct tree_t* tree)
 {
    error_t error_status = OK;

    if (strcmp(answer, "да") == 0)
        printf("Уафхфхфххф, я же говорил, что угадаю\n");

    else if (strcmp(answer, "нет") == 0)
    {
        tree -> tree_node_num += 2;

        error_status = create_one_node(&(current_node -> left_node));
        if (error_status)
            return error_status;

        error_status = create_one_node(&(current_node -> right_node));
        if (error_status)
            return error_status;

        link_children(current_node);

        memcpy((current_node -> left_node) -> data, current_node -> data, MAX_NODE_LEN * sizeof(char));

        get_new_data(current_node);
    }
    else
        printf("Такого варианта ответа нет\n");

    return error_status;
}

void link_children(struct tree_node_t* current_node)
{
    (current_node -> left_node) -> parent_node = current_node;
    (current_node -> right_node) -> parent_node = current_node;
}

void get_new_data(struct tree_node_t* current_node)
{
    printf("<Блиннн. Тогда что это было?: \n");
    scanf("\n%[^\n]", (current_node -> right_node) -> data);

    printf("Как %s отличается от %s?: \n", (current_node -> right_node) -> data, (current_node -> left_node) -> data);
    scanf("\n%[^\n]", current_node -> data);
}
