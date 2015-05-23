#include "citrus/hid.hpp"
#include "internal.hpp"

#include <unordered_map>

#include <3ds.h>

namespace ctr {
    namespace hid {
        static std::unordered_map<u32, const std::string> buttonNames = {
                {BUTTON_NONE, "None"},
                {BUTTON_A, "A"},
                {BUTTON_B, "B"},
                {BUTTON_SELECT, "Select"},
                {BUTTON_START, "Start"},
                {BUTTON_DRIGHT, "D-Pad Right"},
                {BUTTON_DLEFT, "D-Pad Left"},
                {BUTTON_DUP, "D-Pad Up"},
                {BUTTON_DDOWN, "D-Pad Down"},
                {BUTTON_R, "R"},
                {BUTTON_L, "L"},
                {BUTTON_X, "X"},
                {BUTTON_Y, "Y"},
                {BUTTON_ZL, "ZL"},
                {BUTTON_ZR, "ZR"},
                {BUTTON_TOUCH, "Touch"},
                {BUTTON_CSTICK_RIGHT, "C-Stick Right"},
                {BUTTON_CSTICK_LEFT, "C-Stick Left"},
                {BUTTON_CSTICK_UP, "C-Stick Up"},
                {BUTTON_CSTICK_DOWN, "C-Stick Down"},
                {BUTTON_CPAD_RIGHT, "Circle-Pad Right"},
                {BUTTON_CPAD_LEFT, "Circle-Pad Left"},
                {BUTTON_CPAD_UP, "Circle-Pad Up"},
                {BUTTON_CPAD_DOWN, "Circle-Pad Down"},
                {BUTTON_UP, "Up"},
                {BUTTON_DOWN, "Down"},
                {BUTTON_LEFT, "Left"},
                {BUTTON_RIGHT, "Right"}
        };
    }
}

bool ctr::hid::init() {
    return true;
}

void ctr::hid::exit() {
}

void ctr::hid::poll() {
    hidScanInput();
}

ctr::hid::Button ctr::hid::anyPressed() {
    for(u32 i = 0; i < 32; i++) {
        Button button = (Button) (1 << i);
        if(pressed(button)) {
            return button;
        }
    }

    return BUTTON_NONE;
}

bool ctr::hid::released(ctr::hid::Button button) {
    return (hidKeysUp() & button) != 0;
}

bool ctr::hid::pressed(ctr::hid::Button button) {
    return (hidKeysDown() & button) != 0;
}

bool ctr::hid::held(ctr::hid::Button button) {
    return (hidKeysHeld() & button) != 0;
}

ctr::hid::Touch ctr::hid::touch() {
    touchPosition pos;
    hidTouchRead(&pos);
    return {pos.px, pos.py};
}

const std::string ctr::hid::buttonName(ctr::hid::Button button) {
    std::unordered_map<u32, const std::string>::iterator result = buttonNames.find(button);
    return result != buttonNames.end() ? result->second : "<unknown>";
}