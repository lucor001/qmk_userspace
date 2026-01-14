/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

//#define QUICK_TAP_TERM 0
// Core tap-hold tuning
#define TAPPING_TERM 210 //Reduced from 240 due to missed capitals
//#define PERMISSIVE_HOLD
#define PERMISSIVE_HOLD_PER_KEY
//#define HOLD_ON_OTHER_KEY_PRESS
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define SPECULATIVE_HOLD

// New in 2025
#define CHORDAL_HOLD // settle same-hand chords as taps
#define FLOW_TAP_TERM 150 // optional: "flow of taps" during fast typing

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define SPLIT_LAYER_STATE_ENABLE

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
   #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
   #define RGB_MATRIX_SLEEP // turn off effects when suspended
   #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
//   #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
   #define RGB_MATRIX_HUE_STEP 8
   #define RGB_MATRIX_SAT_STEP 8
   #define RGB_MATRIX_VAL_STEP 8
   #define RGB_MATRIX_SPD_STEP 10
   #define SPLIT_MODS_ENABLE //allows mods to address leds on the second side.

    /* Enable the animations you want/need.  You may need to enable only a small number of these because       *
 * they take up a lot of space.  Enable and confirm that you can still successfully compile your firmware. */
// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_BREATHING
#    define ENABLE_RGB_MATRIX_BAND_SAT
#    define ENABLE_RGB_MATRIX_BAND_VAL
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#    define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#    define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    define ENABLE_RGB_MATRIX_CYCLE_ALL
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#    define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#    define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#    define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    define ENABLE_RGB_MATRIX_DUAL_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#    define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    define ENABLE_RGB_MATRIX_RAINDROPS
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_HUE_BREATHING
#    define ENABLE_RGB_MATRIX_HUE_PENDULUM
#    define ENABLE_RGB_MATRIX_HUE_WAVE
#    define ENABLE_RGB_MATRIX_PIXEL_RAIN
#    define ENABLE_RGB_MATRIX_PIXEL_FLOW
#    define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_RGB_MATRIX_SPLASH
#    define ENABLE_RGB_MATRIX_MULTISPLASH
#    define ENABLE_RGB_MATRIX_SOLID_SPLASH
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

//    RGB_MATRIX_NONE = 0,
//    RGB_MATRIX_SOLID_COLOR = 1,     // Static single hue, no speed support
//    RGB_MATRIX_ALPHAS_MODS,         // Static dual hue, speed is hue for secondary hue
//    RGB_MATRIX_GRADIENT_UP_DOWN,    // Static gradient top to bottom, speed controls how much gradient changes
//    RGB_MATRIX_GRADIENT_LEFT_RIGHT,    // Static gradient left to right, speed controls how much gradient changes
//    RGB_MATRIX_BREATHING,           // Single hue brightness cycling animation
//    RGB_MATRIX_BAND_SAT,        // Single hue band fading saturation scrolling left to right
//    RGB_MATRIX_BAND_VAL,        // Single hue band fading brightness scrolling left to right
//    RGB_MATRIX_BAND_PINWHEEL_SAT,   // Single hue 3 blade spinning pinwheel fades saturation
//    RGB_MATRIX_BAND_PINWHEEL_VAL,   // Single hue 3 blade spinning pinwheel fades brightness
//    RGB_MATRIX_BAND_SPIRAL_SAT,     // Single hue spinning spiral fades saturation
//    RGB_MATRIX_BAND_SPIRAL_VAL,     // Single hue spinning spiral fades brightness
//    RGB_MATRIX_CYCLE_ALL,           // Full keyboard solid hue cycling through full gradient
//    RGB_MATRIX_CYCLE_LEFT_RIGHT,    // Full gradient scrolling left to right
//    RGB_MATRIX_CYCLE_UP_DOWN,       // Full gradient scrolling top to bottom
//    RGB_MATRIX_CYCLE_OUT_IN,        // Full gradient scrolling out to in
//    RGB_MATRIX_CYCLE_OUT_IN_DUAL,   // Full dual gradients scrolling out to in
//    RGB_MATRIX_RAINBOW_MOVING_CHEVRON,  // Full gradient Chevron shapped scrolling left to right
//    RGB_MATRIX_CYCLE_PINWHEEL,      // Full gradient spinning pinwheel around center of keyboard
//    RGB_MATRIX_CYCLE_SPIRAL,        // Full gradient spinning spiral around center of keyboard
//    RGB_MATRIX_DUAL_BEACON,         // Full gradient spinning around center of keyboard
//    RGB_MATRIX_RAINBOW_BEACON,      // Full tighter gradient spinning around center of keyboard
//    RGB_MATRIX_RAINBOW_PINWHEELS,   // Full dual gradients spinning two halfs of keyboard
//    RGB_MATRIX_FLOWER_BLOOMING,     // Full tighter gradient of first half scrolling left to right and second half scrolling right to left
//    RGB_MATRIX_RAINDROPS,           // Randomly changes a single key's hue
//    RGB_MATRIX_JELLYBEAN_RAINDROPS, // Randomly changes a single key's hue and saturation
//    RGB_MATRIX_HUE_BREATHING,       // Hue shifts up a slight ammount at the same time, then shifts back
//    RGB_MATRIX_HUE_PENDULUM,        // Hue shifts up a slight ammount in a wave to the right, then back to the left
//    RGB_MATRIX_HUE_WAVE,            // Hue shifts up a slight ammount and then back down in a wave to the right
//    RGB_MATRIX_PIXEL_FRACTAL,       // Single hue fractal filled keys pulsing horizontally out to edges
//    RGB_MATRIX_PIXEL_FLOW,          // Pulsing RGB flow along LED wiring with random hues
//    RGB_MATRIX_PIXEL_RAIN,          // Randomly light keys with random hues
//    RGB_MATRIX_TYPING_HEATMAP,      // How hot is your WPM!
//    RGB_MATRIX_DIGITAL_RAIN,        // That famous computer simulation
//    RGB_MATRIX_SOLID_REACTIVE_SIMPLE,   // Pulses keys hit to hue & value then fades value out
//    RGB_MATRIX_SOLID_REACTIVE,      // Static single hue, pulses keys hit to shifted hue then fades to current hue
//    RGB_MATRIX_SOLID_REACTIVE_WIDE,       // Hue & value pulse near a single key hit then fades value out
//    RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE,  // Hue & value pulse near multiple key hits then fades value out
//    RGB_MATRIX_SOLID_REACTIVE_CROSS,      // Hue & value pulse the same column and row of a single key hit then fades value out
//    RGB_MATRIX_SOLID_REACTIVE_MULTICROSS, // Hue & value pulse the same column and row of multiple key hits then fades value out
//    RGB_MATRIX_SOLID_REACTIVE_NEXUS,      // Hue & value pulse away on the same column and row of a single key hit then fades value out
//    RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS, // Hue & value pulse away on the same column and row of multiple key hits then fades value out
//    RGB_MATRIX_SPLASH,              // Full gradient & value pulse away from a single key hit then fades value out
//    RGB_MATRIX_MULTISPLASH,         // Full gradient & value pulse away from multiple key hits then fades value out
//    RGB_MATRIX_SOLID_SPLASH,        // Hue & value pulse away from a single key hit then fades value out
//    RGB_MATRIX_SOLID_MULTISPLASH,   // Hue & value pulse away from multiple key hits then fades value out
//    RGB_MATRIX_STARLIGHT,           // LEDs turn on and off at random at varying brightness, maintaining user set color
//    RGB_MATRIX_STARLIGHT_DUAL_HUE,  // LEDs turn on and off at random at varying brightness, modifies user set hue by +- 30
//    RGB_MATRIX_STARLIGHT_DUAL_SAT,  // LEDs turn on and off at random at varying brightness, modifies user set saturation by +- 30
//    RGB_MATRIX_RIVERFLOW,           // Modification to breathing animation, offset's animation depending on key location to simulate a river flowing
//    RGB_MATRIX_EFFECT_MAX
