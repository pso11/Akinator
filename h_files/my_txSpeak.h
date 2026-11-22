struct buttom_t
{
    double x_0;
    double y_0;
    double x_1;
    double y_1;
    const char* message;
    COLORREF fill_color;
    COLORREF touch_fill_color;
    COLORREF stroke_color;
    COLORREF touch_stroke_color;
};

struct mouse_t
{
    double m_x;
    double m_y;
};

int tx_introduction(void);
int txSpeak_empty_database(void);
int txSpeak_main_charact(void);
int txSpeak_pros_answer(void);
int txSpeak_negativ_answer(void);
int txSpeak_apologize(void);
int txSpeak_ask_differences(tree_elem_t val1, tree_elem_t val2);
int tx_get_answer(tree_node_t* current_node);
int txSpeak_yes_or_no(tree_node_t* current_node);
int txSpeak_shure_answer(void);
int txSpeak_dump_message(void);
int txSpeak_no_tree_elem(void);
int txSpeak_same_intro(tree_elem_t val1, tree_elem_t val2);
int txSpeak_no(void);
int txSpeak_poped_val(tree_elem_t val);
int txSpeak_no_same_elem(void);
int txSpeak_enter_word(void);
void tx_clear_window(void);
void my_tx_destroy(void);

int akinator_mode(buttom_t* struct_array, size_t array_size, mouse_t* mouse_coordinats);
void draw_buttom(buttom_t* structure, bool pushed);
void get_mouse_coordinats(mouse_t* mouse_coordinats);

#define  TX_BLACK RGB ( 0, 0, 0)
#define  TX_BLUE RGB ( 10, 18, 65)
#define  TX_GREEN RGB ( 0, 128, 0)
#define  TX_CYAN RGB ( 0, 128, 128)
#define  TX_RED RGB (128, 0, 0)
#define  TX_MAGENTA RGB (128, 0, 128)
#define  TX_BROWN RGB (128, 128, 0)
#define  TX_ORANGE RGB (255, 128, 0)
#define  TX_GRAY RGB (103, 112, 106)
#define  TX_DARKGRAY RGB (128, 128, 128)
#define  TX_LIGHTGRAY RGB (192, 192, 192)
#define  TX_LIGHTBLUE RGB (210, 252, 252)
#define  TX_LIGHTGREEN RGB ( 0, 255, 128)
#define  TX_LIGHTCYAN RGB ( 0, 255, 255)
#define  TX_LIGHTRED RGB (255, 0, 128)
#define  TX_LIGHTMAGENTA RGB (255, 0, 25)
#define  TX_PINK RGB (255, 128, 255)
#define  TX_YELLOW RGB (255, 215, 0)
#define  TX_GOLD RGB(212, 175, 55)
#define  TX_WHITE RGB (255, 255, 255)
#define  TX_TURQUOISE RGB(64, 224, 208)
#define  TX_NULL 0xFFFFFFF
#define  TX_HUE 0x04000000
#define  TX_SATURATION 0x05000000
#define  TX_LIGHTNESS 0x06000000
#define  TX_LAB_L 0x07000000
#define  TX_LAB_A 0x08000000
#define  TX_LAB_B 0x09000000

