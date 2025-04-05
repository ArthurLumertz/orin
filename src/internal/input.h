#ifndef INPUT_H
#define INPUT_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

void Internal_KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void Internal_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void Internal_CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

int Internal_IsKeyDown(int key);
int Internal_IsKeyReleased(int key);
int Internal_IsButtonDown(int button);
int Internal_IsButtonReleased(int button);

Vector2f Internal_GetMousePosition();
Vector2f Internal_GetMouseDelta();

#ifdef __cplusplus
}
#endif

#endif
