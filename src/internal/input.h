#ifndef ORIN_INPUT_H
#define ORIN_INPUT_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

void Internal_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void Internal_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void Internal_CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

bool Internal_IsKeyDown(Key key);
bool Internal_IsKeyReleased(Key key);
bool Internal_IsButtonDown(Button button);
bool Internal_IsButtonReleased(Button button);

Vector2f Internal_GetMousePosition();
Vector2f Internal_GetMouseDelta();

#ifdef __cplusplus
}
#endif

#endif
