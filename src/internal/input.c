#include "input.h"
#include "../orin.h"

static int keysDown[KEY_LAST] = { 0 };
static int keysReleased[KEY_LAST] = { 0 };

static int buttonsDown[MOUSE_BUTTON_LAST] = { 0 };
static int buttonsReleased[MOUSE_BUTTON_LAST] = { 0 };

static float prevMouseX;
static float prevMouseY;

static float mouseX;
static float mouseY;

static float mouseDeltaX;
static float mouseDeltaY;

void Internal_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key >= KEY_LAST) {
        return;
    }
    keysDown[key] = action != GLFW_RELEASE;
    keysReleased[key] = action == GLFW_PRESS;
}

void Internal_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button < 0 || button >= MOUSE_BUTTON_LAST) {
        return;
    }
    buttonsDown[button] = action != GLFW_RELEASE;
    buttonsReleased[button] = action == GLFW_PRESS;
}

void Internal_CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    prevMouseX = mouseX;
    prevMouseY = mouseY;

    mouseX = (float)xpos;
    mouseY = (float)ypos;

    mouseDeltaX = mouseX - prevMouseX;
    mouseDeltaY = mouseY - prevMouseY;
}

Vector2f Internal_GetMousePosition() {
    return (Vector2f){ mouseX, mouseY };
}

Vector2f Internal_GetMouseDelta() {
    return (Vector2f){ mouseDeltaX, mouseDeltaY };
}

int Internal_IsKeyDown(int key) {
    return keysDown[key];
}

int Internal_IsKeyReleased(int key) {
    int result = keysReleased[key];
    keysReleased[key] = 0;
    return result;
}

int Internal_IsButtonDown(int button) {
    return buttonsDown[button];
}

int Internal_IsButtonReleased(int button) {
    int result = buttonsReleased[button];
    buttonsReleased[button] = 0;
    return result;
}