#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

void Internal_SetKeyCallback(int key, int scancode, int action, int mods);
void Internal_SetMouseButtonCallback(int button, int action, int mods);
void Internal_SetCursorPosCallback(double xpos, double ypos);

int Internal_IsKeyDown(int key);
int Internal_IsKeyReleased(int key);
int Internal_IsButtonDown(int button);
int Internal_IsButtonReleased(int button);

#ifdef __cplusplus
}
#endif

#endif
