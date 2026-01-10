#pragma once

#include "layer_list.h"

enum keyboard_layers {
    #define KEYBOARD_X(LAYER, STRING) U_##LAYER,
    KEYBOARD_LAYER_LIST
    #undef KEYBOARD_X
};
