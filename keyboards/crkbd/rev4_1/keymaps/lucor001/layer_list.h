#pragma once

#if !defined (KEYBOARD_LAYER_LIST)

//The order of these layers isn't important, this is just an enumeration.  However, the top layer is layer 0 which is the default layer on bootup.
#define KEYBOARD_LAYER_LIST \
KEYBOARD_X(COLMAKDH, "Colmakdh") \
KEYBOARD_X(QWERTY,   "Qwerty") \
KEYBOARD_X(DVORAK,   "Dvorak") \
KEYBOARD_X(SYM,      "Sym") \
KEYBOARD_X(NAV,      "Nav") \
KEYBOARD_X(NUM,      "Num") \
KEYBOARD_X(MOUSE,    "Mouse") \
KEYBOARD_X(MEDIA,    "Media") \
KEYBOARD_X(FUN,      "Fun") \
KEYBOARD_X(BUTTON,   "Button") \
KEYBOARD_X(TAP,      "Tap")
#endif
