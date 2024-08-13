#ifdef OLED_ENABLE
#include QMK_KEYBOARD_H
#include "wpm.h"

// Configuration
#define ANIM_INVERT true
#define ANIM_RENDER_WPM true
#define FAST_TYPE_WPM 45 // Switch to fast animation when over words per minute

// Include only one animation at a time
#include "crab.c"

// Declare external variables with correct type
extern const char PROGMEM layer_zero[];
extern const char PROGMEM layer_one[];
extern const char PROGMEM layer_two[];
extern const char PROGMEM layer_three[];

// OLED initialization
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

// OLED task
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Display layer status on master side
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_raw_P(layer_zero, OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8);
                break;
            case 1:
                oled_write_raw_P(layer_one, OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8);
                break;
            case 2:
                oled_write_raw_P(layer_two, OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8);
                break;
            case 3:
                oled_write_raw_P(layer_three, OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / 8);
                break;
        }
    } else {
        // Display animation on slave side
        oled_render_anim();
    }
    return false;
}
#endif
