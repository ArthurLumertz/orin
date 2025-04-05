#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

void Internal_ClearBackground(Color color);

void Internal_BeginDrawing(Camera2D camera, Shader *shader, Display *display);
void Internal_EndDrawing();

void Internal_SetColor(Color color, Shader *shader);

void Internal_DrawRectangle(Shader *shader, Vector2f position, Vector2f size, Color color);
void Internal_DrawTexture(Shader *shader, Texture *texture, Vector2f position, Vector2f size, Color color);

void Internal_DrawModel(Model *model, Matrix4f *transform, Shader *shader);

Shader *Internal_CreateDefaultShader();

#ifdef __cplusplus
}
#endif

#endif
