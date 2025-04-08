#ifndef ORIN_GRAPHICS_H
#define ORIN_GRAPHICS_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

void Internal_ClearBackground(Color color);

void Internal_BeginDrawing(Camera2D camera, Shader *shader, Display *display);
void Internal_EndDrawing();

void Internal_DrawRectangle(Shader *shader, float x, float y, float width, float height, Color tint);
void Internal_DrawTexture(Shader *shader, Texture *texture, float x, float y, float width, float height, Color tint);

void Internal_DrawModel(Model *model, Vector3f position, Vector3f scale, Color tint, Shader *shader);

#ifdef __cplusplus
}
#endif

#endif
