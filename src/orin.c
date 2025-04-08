#include "orin.h"
#include "orinmath.h"

#include "internal/display.h"
#include "internal/graphics.h"
#include "internal/texture.h"
#include "internal/shader.h"
#include "internal/model.h"
#include "internal/input.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <time.h>
#include <stdlib.h>

Shader *currentShader = NULL;
Camera2D *currentCamera = NULL;
Display *currentDisplay = NULL;

Display* CreateDisplay(int width, int height, const char *title, int args) {
    Display *display = Internal_CreateDisplay(width, height, title, args);
    currentDisplay = display;

    srand((unsigned int)time(NULL));

    return display;
}

void SetDisplayIcon(Display *display, const char *fileName) {
    Internal_SetDisplayIcon(display, fileName);
}

int DisplayShouldClose(Display* display) {
    Internal_UpdateDisplay(display);
    return Internal_DisplayShouldClose(display);
}

void DestroyDisplay(Display* display) {
    return Internal_DestroyDisplay(display);
}

void SetDisplaySize(Display* display, int width, int height) {
    Internal_SetDisplaySize(display, width, height);
}

void SetDisplayTitle(Display* display, const char *title) {
    Internal_SetDisplayTitle(display, title);
}

void UseVSync(bool sync) {
    Internal_UseVSync(sync);
}

void ClearBackground(Color color) {
    Internal_ClearBackground(color);
}

void BeginDrawing(Shader *shader, Camera2D camera) {
    glViewport(0, 0, currentDisplay->displayMode.width, currentDisplay->displayMode.height);

    currentShader = shader;
    currentCamera = &camera;

    Internal_BeginDrawing(camera, shader, currentDisplay);
}

void BeginDrawing2D(Camera2D camera) {
    if (currentShader == NULL) {
        currentShader = CreateDefaultShader();
    }

    BeginDrawing(currentShader, camera);
}

void EndDrawing() {

}

void DrawRectangle(float x, float y, float width, float height, Color tint) {
    Internal_DrawRectangle(currentShader, x, y, width, height, tint);
}

void DrawRectangleV(Vector2f position, Vector2f size, Color tint) {
    DrawRectangle(position.x, position.y, size.x, size.y, tint);
}

void DrawTexture(Texture *texture, float x, float y, float width, float height, Color tint) {
    Internal_DrawTexture(currentShader, texture, x, y, width, height, tint);
}

void DrawTextureV(Texture *texture, Vector2f position, Vector2f size, Color tint) {
    DrawTexture(texture, position.x, position.y, size.x, size.y, tint);
}

Texture *LoadTexture(const char *filename, int filter) {
    return Internal_LoadTexture(filename, filter);
}

void DestroyTexture(Texture *texture) {
    return Internal_DestroyTexture(texture);
}

Shader *CreateShader(const char *vertexFile, const char *fragmentFile) {
    return Internal_CreateShader(vertexFile, fragmentFile);
}

Shader *CreateDefaultShader() {
    const char *vertexSource =
        "#version 330 core\n"
        "layout(location = 0) in vec2 a_position;\n"
        "layout(location = 1) in vec2 a_uvs;\n"
        "layout(location = 2) in vec2 a_normals;\n"
        "layout(location = 3) in vec4 a_colors;\n"
        "\n"
        "uniform mat4 u_combmatrix = mat4(1.0);\n"
        "uniform mat4 u_transmatrix = mat4(1.0);\n"
        "\n"
        "out vec2 uvs;\n"
        "out vec2 normals;\n"
        "out vec4 colors;\n"
        "\n"
        "void main() {\n"
        "    gl_Position = u_combmatrix * u_transmatrix * vec4(a_position, 0.0, 1.0);\n"
        "\n"
        "    uvs = a_uvs;\n"
        "    normals = a_normals;\n"
        "    colors = a_colors;\n"
        "}\n";

    const char *fragmentSource =
        "#version 330 core\n"
        "\n"
        "out vec4 FragColor;\n"
        "\n"
        "in vec2 uvs;\n"
        "in vec2 normals;\n"
        "in vec4 colors;\n"
        "\n"
        "uniform sampler2D u_sampler;\n"
        "uniform bool u_texture;\n"
        "uniform vec4 u_color;\n"
        "\n"
        "void main() {\n"
        "    vec4 final_color = u_color;\n"
        "    if (u_texture) {\n"
        "        final_color = texture(u_sampler, uvs) * u_color;\n"
        "    }\n"
        "    FragColor = final_color * colors;\n"
        "}\n";

    return Internal_CreateShaderBySource(vertexSource, fragmentSource);
}

void DestroyShader(Shader *shader) {
    return Internal_DestroyShader(shader);
}

int GetShaderLocation(Shader *shader, const char *uniformName) {
    return Internal_GetShaderLocation(shader, uniformName);
}

void SetShaderValue(Shader *shader, int location, const void *value, UniformType type) {
    Internal_SetShaderValue(shader, location, value, type);
}

Model *CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount) {
    return Internal_CreateModel(vertices, vertexCount, indices, indexCount);
}

void DestroyModel(Model *model) {
    Internal_DestroyModel(model);
}

void DrawModel(Model *model, Vector3f position, Vector3f scale, Color tint) {
    Internal_DrawModel(model, position, scale, tint, currentShader);
}

bool IsKeyDown(Key key) {
    return Internal_IsKeyDown(key);
}

bool IsKeyReleased(Key key) {
    return Internal_IsKeyReleased(key);
}

bool IsButtonDown(Button button) {
    return Internal_IsButtonDown(button);
}

bool IsButtonReleased(Button button) {
    return Internal_IsButtonReleased(button);
}

Vector2f GetMousePosition() {
    return Internal_GetMousePosition();
}

Vector2f GetMouseDelta() {
    return Internal_GetMouseDelta();
}

bool RectIntersects(Rectangle a, Rectangle b) {
    return a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y;
}

bool RectIIntersects(RectangleI a, RectangleI b) {
    return a.x < b.x + b.width &&
        a.x + a.width > b.x &&
        a.y < b.y + b.height &&
        a.y + a.height > b.y;
}

bool RectContains(Rectangle a, Rectangle b) {
    return b.x >= a.x &&
        b.y >= a.y &&
        b.x + b.width <= a.x + a.width &&
        b.y + b.height <= a.y + a.height;
}

bool RectIContains(RectangleI a, RectangleI b) {
    return b.x >= a.x &&
        b.y >= a.y &&
        b.x + b.width <= a.x + a.width &&
        b.y + b.height <= a.y + a.height;
}

bool BBoxIntersects(BoundingBox a, BoundingBox b) {
    return a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z;
}

bool BBoxIIntersects(BoundingBoxI a, BoundingBoxI b) {
    return a.min.x <= b.max.x && a.max.x >= b.min.x &&
        a.min.y <= b.max.y && a.max.y >= b.min.y &&
        a.min.z <= b.max.z && a.max.z >= b.min.z;
}

bool BBoxContains(BoundingBox a, BoundingBox b) {
    return b.min.x >= a.min.x && b.max.x <= a.max.x &&
        b.min.y >= a.min.y && b.max.y <= a.max.y &&
        b.min.z >= a.min.z && b.max.z <= a.max.z;
}

bool BBoxIContains(BoundingBoxI a, BoundingBoxI b) {
    return b.min.x >= a.min.x && b.max.x <= a.max.x &&
        b.min.y >= a.min.y && b.max.y <= a.max.y &&
        b.min.z >= a.min.z && b.max.z <= a.max.z;
}

bool PointInRect(Rectangle rect, Vector2f point) {
    return point.x >= rect.x &&
        point.x <= rect.x + rect.width &&
        point.y >= rect.y &&
        point.y <= rect.y + rect.height;
}

bool PointInRectI(RectangleI rect, Vector2i point) {
    return point.x >= rect.x &&
        point.x <= rect.x + rect.width &&
        point.y >= rect.y &&
        point.y <= rect.y + rect.height;
}

Rectangle GetCameraViewport(Camera2D camera) {
    float halfWidth  = (float)currentDisplay->displayMode.width  / (2.0f * camera.zoom);
    float halfHeight = (float)currentDisplay->displayMode.height / (2.0f * camera.zoom);

    float width  = halfWidth * 2.0f;
    float height = halfHeight * 2.0f;

    return (Rectangle){ camera.position.x, camera.position.y, width, height };
}

int GetRandomValue(int min, int max) {
    return (rand() % (abs(max - min) + 1) + min);
}

void HideMouse(Display *display, bool hidden) {
    Internal_SetMouseHidden(display, hidden);
}

bool IsMouseHidden(Display *display) {
    return Internal_IsMouseHidden(display);
}

void DisableMouse(Display *display, bool disabled) {
    return Internal_DisableMouse(display, disabled);
}

bool IsMouseDisabled(Display *display) {
    return Internal_IsMouseDisabled(display);
}