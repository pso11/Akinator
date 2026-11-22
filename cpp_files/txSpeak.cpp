#define TX_USE_SPEAK
#include <TXLib.h>

#include <stdio.h>
#include <stdlib.h>

#include "akinator.h"
#include "my_txSpeak.h"

int tx_introduction(void)
{
    txClearConsole();
    if (!txWindow())
        txCreateWindow(800, 800);

    tx_clear_window();

    txDrawText(50, 60, 750, 220, "Привет, я Сири.\nВыберите режим работы программы:", DT_CENTER | DT_WORDBREAK);
    txRedrawWindow();
    txSpeak("Привет, я Сири. Выберите режим работы программы");

    txSelectFont("Gabriola", 40, 0, 1000);

    buttom_t struct_array[] =
    {
        {100, 200, 300, 300, "Угадывание", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
        {400, 200, 600, 300, "Показать дерево", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
        {100, 400, 300, 500, "Определение", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
        {400, 400, 600, 500, "Сравнение", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
        {250, 600, 450, 700, "Выход", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK}
    };

    mouse_t mouse_coordinats = {};

    return akinator_mode(struct_array, sizeof(struct_array) / sizeof(struct_array[0]), &mouse_coordinats);
}

void draw_buttom(buttom_t* structure, bool pushed)
{
    if (pushed)
    {
        txSetFillColor(structure -> touch_fill_color);
        txSetColor(structure -> touch_stroke_color);
    }
    else
    {
        txSetFillColor(structure -> fill_color);
        txSetColor(structure -> stroke_color);
    }

    txRectangle(structure -> x_0, structure -> y_0, structure -> x_1, structure -> y_1);
    txDrawText(structure -> x_0, structure -> y_0, structure -> x_1, structure -> y_1, structure -> message, DT_CENTER | DT_WORDBREAK | DT_VCENTER );
}

int akinator_mode(buttom_t* struct_array, size_t array_size, mouse_t* mouse_coordinats)
{
    txBegin();

    while (1)
    {
        get_mouse_coordinats(mouse_coordinats);
        double m_x = mouse_coordinats -> m_x;
        double m_y = mouse_coordinats -> m_y;

        for (size_t i = 0; i < array_size; i++)
        {
            double x_0 = struct_array[i].x_0;
            double y_0 = struct_array[i].y_0;
            double x_1 = struct_array[i].x_1;
            double y_1 = struct_array[i].y_1;

            if (m_x >= x_0 && m_x <= x_1 && m_y >= y_0 && m_y <= y_1)
            {
                draw_buttom(&struct_array[i], 1);
                txRedrawWindow();

                unsigned push_state = txMouseButtons();
                if ((push_state & 1) || (push_state & 2))
                    return i + 1;
            }
            else
            {
                draw_buttom(&struct_array[i], 0);
                txRedrawWindow();
            }
        }
    }
}

void get_mouse_coordinats(mouse_t* mouse_coordinats)
{
    mouse_coordinats -> m_x = txMouseX();
    mouse_coordinats -> m_y = txMouseY();
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
    tx_clear_window();

    txDrawText(50, 400, 750, 450, "Блиннн. Тогда что это было?\n", DT_CENTER | DT_WORDBREAK);
    txRedrawWindow();
    txSpeak("Блиннн. Тогда что это было?\n");

    return 0;
}

int txSpeak_ask_differences(tree_elem_t val1, tree_elem_t val2)
{
    tx_clear_window();

    char buffer[100] = {};
    snprintf(buffer, 100, "Чем %" TREE_SPECIFICATOR " оличается от %" TREE_SPECIFICATOR "?\n", val1, val2);

    txDrawText(50, 400, 750, 450, buffer, DT_CENTER | DT_WORDBREAK);
    txRedrawWindow();
    txSpeak("%s", buffer);

    return 0;
}

int tx_get_answer(tree_node_t* current_node)
{
    tx_clear_window();

    char buffer[100] = {};
    snprintf(buffer, 100, "Это %" TREE_SPECIFICATOR "?\n", current_node -> data);

    txDrawText(50, 60, 750, 220, buffer, DT_CENTER | DT_WORDBREAK);
    txRedrawWindow();
    txSpeak("%s", buffer);

    buttom_t struct_array[] =
    {
        {300, 350, 500, 450, "Да", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
        {300, 500, 500, 600, "Нет", RGB(245, 222, 179), TX_GOLD, TX_BLACK, TX_BLACK},
    };
    mouse_t mouse_coordinats = {};

    return akinator_mode(struct_array, sizeof(struct_array) / sizeof(struct_array[0]), &mouse_coordinats);
}

int txSpeak_shure_answer(void)
{
    tx_clear_window();

    txDrawText(50, 400, 750, 450, "Уафхфхфххф, я же говорил, что угадаю\n", DT_CENTER | DT_WORDBREAK);
    txRedrawWindow();
    txSpeak("Уафхфхфххф, я же говорил, что угадаю\n");

    return 0;
}

void tx_clear_window(void)
{
    txSetFillColor(TX_BLUE);
    txClear();
    txRedrawWindow();

    txSetColor(TX_GOLD);
    txSelectFont("Monotype Corsiva", 36, 0, 800);
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

void my_tx_destroy(void)
{
    txDestroyWindow();
}

