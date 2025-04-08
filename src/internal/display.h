#ifndef ORIN_DISPLAY_H
#define ORIN_DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Display* Internal_CreateDisplay(int width, int height, const char *title, int args);
int Internal_DisplayShouldClose(Display* display);
void Internal_UpdateDisplay(Display* display);
void Internal_DestroyDisplay(Display* display);

void Internal_SetDisplaySize(Display* display, int width, int height);
void Internal_SetDisplayTitle(Display* display, const char *title);

void Internal_UseVSync(bool sync);
void Internal_SetDisplayIcon(Display *display, const char *fileName);

void Internal_HideMouse(Display *display, bool hidden);
bool Internal_IsMouseHidden(Display *display);

void Internal_DisableMouse(Display *display, bool disabled);
bool Internal_IsMouseDisabled(Display *display);

#ifdef __cplusplus
}
#endif

#endif
