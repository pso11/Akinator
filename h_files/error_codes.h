#pragma once

enum error_t
{
    OK                        = 0,
    NULL_POINT_FROM_CALLOC    = 1,
    NULL_POINT_ON_TREE_STRUCT = 2,
    NULL_NODE_GIVEN           = 3,
    NULL_FILE_POINT           = 4,
    CANNOT_OPEN_FILE          = 5,
    WRONG_SIZE                = 6,
    WRONG_RIGHT_PARENTNESS    = 7,
    WRONG_LEFT_PARENTNESS     = 8,
    DAMAGED_LEAF_NODE         = 9,
    TREE_WITH_CYCLE           = 10,
    WRONG_ROOT_PARENT         = 11
};
