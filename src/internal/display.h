#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Display* Internal_CreateDisplay(DisplayMode displayMode, const char *title, int args);
int Internal_DisplayShouldClose(Display* display);
void Internal_UpdateDisplay(Display* display);
void Internal_DestroyDisplay(Display* display);

void Internal_SetDisplaySize(Display* display, int width, int height);
void Internal_SetDisplayTitle(Display* display, const char *title);

void Internal_UseVSync(int sync);

#ifdef __cplusplus
}
#endif

#endif
