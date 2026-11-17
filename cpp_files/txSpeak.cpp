#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>

#include "akinator.h"
#include "my_txSpeak.h"

int txSpeak_introduction(void)
{
    txSpeak("\vПривет, я Сири. Выберите режим работы программы  \n");

    return 0;
}

int txSpeak_empty_database(void)
{
    txSpeak("\vВаша база данных пуста.\n");

    return 0;
}

int txSpeak_main_charact(void)
{
    txSpeak("\vВведите главную характеристику: ");

    return 0;
}

int txSpeak_pros_answer(void)
{
    txSpeak("\vТеперь введите ответ, если да: ");

    return 0;
}

int txSpeak_negativ_answer(void)
{
    txSpeak("\vИ введите ответ, если нет: ");

    return 0;
}

int txSpeak_apologize(void)
{
    txSpeak("\vБлиннн. Тогда что это было?: \n");

    return 0;
}

int txSpeak_ask_differences(tree_elem_t val1, tree_elem_t val2)
{
    txSpeak("\vКак %s отличается от %s?: \n", val1, val2);

    return 0;
}

int txSpeak_no_answer_to_answer(void)
{
    txSpeak("\vТакого варианта ответа нет\n");

    return 0;
}

int txSpeak_yes_or_no(tree_node_t* current_node)
{
    txSpeak("\vЭто %" TREE_SPECIFICATOR "?\n", current_node -> data);

    return 0;
}

int txSpeak_shure_answer(void)
{
    txSpeak("\vУафхфхфххф, я же говорил, что угадаю\n");

    return 0;
}

int txSpeak_dump_message(void)
{
    txSpeak("\vHiiii!!!! LOOK AT MAIN.LOG!!!\n");

    return 0;
}

int txSpeak_no_tree_elem(void)
{
    txSpeak("\vТакого элемента не существует \n");

    return 0;
}

int txSpeak_same_intro(tree_elem_t val1, tree_elem_t val2)
{
    txSpeak("\v%" TREE_SPECIFICATOR " и %" TREE_SPECIFICATOR " похожи тем, что они: ", val1, val2);

    return 0;
}

int txSpeak_no(void)
{
    txSpeak("\vне ");

    return 0;
}

int txSpeak_poped_val(tree_elem_t val)
{
    txSpeak("\v%" TREE_SPECIFICATOR " ", val);

    return 0;
}

int txSpeak_no_same_elem(void)
{
    txSpeak("\vСхожеств нет\n");

    return 0;
}

int txSpeak_enter_word(void)
{
    txSpeak("\vВведите определяемое слово: ");

    return 0;
}
