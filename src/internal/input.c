#include "input.h"
#include "../orin.h"

static int keysDown[KEY_LAST];
static int keysReleased[KEY_LAST];

static int buttonsDown[GLFW_MOUSE_BUTTON_3];

void Internal_SetKeyCallback(int key, int scancode, int action, int mods) {
    if (key < 0 || key >= KEY_LAST) {
        return;
    }
    keysDown[key] = action != GLFW_RELEASE;
    keysReleased[key] = action == GLFW_PRESS;
}

void Internal_SetMouseButtonCallback(int button, int action, int mods) {

}

void Internal_SetCursorPosCallback(double xpos, double ypos) {

}

int Internal_IsKeyDown(int key) {

}

int Internal_IsKeyReleased(int key) {

}

int Internal_IsButtonDown(int button) {

}

int Internal_IsButtonReleased(int button) {

}