#include "orin.h"
#include "orinmath.h"

#include "internal/display.h"
#include "internal/graphics.h"
#include "internal/texture.h"
#include "internal/shader.h"
#include "internal/model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <complex.h>
#include <stb_image.h>

#include "internal/input.h"

Shader *currentShader = NULL;
Camera2D *currentCamera = NULL;
Display *currentDisplay = NULL;

Display* CreateDisplay(DisplayMode displayMode, const char *title, int args) {
    Display *display = Internal_CreateDisplay(displayMode, title, args);
    currentDisplay = display;
    return display;
}

int DisplayShouldClose(Display* display) {
    return Internal_DisplayShouldClose(display);
}

void UpdateDisplay(Display* display) {
    return Internal_UpdateDisplay(display);
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

void UseVSync(int sync) {
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

void EndDrawing() {

}

void DrawRectangle(Vector2f position, Vector2f size, Color color) {
    Internal_DrawRectangle(currentShader, position, size, color);
}

void DrawTexture(Texture *texture, Vector2f position, Vector2f size, Color color) {
    Internal_DrawTexture(currentShader, texture, position, size, color);
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

Model *CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount) {
    return Internal_CreateModel(vertices, vertexCount, indices, indexCount);
}

void DestroyModel(Model *model) {
    Internal_DestroyModel(model);
}

void SetColor(Color color) {
    Internal_SetColor(color, currentShader);
}

void DrawModel(Model *model, Matrix4f *transform) {
    Internal_DrawModel(model, transform, currentShader);
}

void SetUniform1f(Shader *shader, const char *name, float value) {
    Internal_SetUniform1f(shader, name, value);
}

void SetUniform2f(Shader *shader, const char *name, Vector2f value) {
    Internal_SetUniform2f(shader, name, value);
}

void SetUniform3f(Shader *shader, const char *name, Vector3f value) {
    Internal_SetUniform3f(shader, name, value);
}

void SetUniform4f(Shader *shader, const char *name, Vector4f value) {
    Internal_SetUniform4f(shader, name, value);
}

void SetUniform1i(Shader *shader, const char *name, int value) {
    Internal_SetUniform1i(shader, name, value);
}

void SetUniform2i(Shader *shader, const char *name, Vector2i value) {
    Internal_SetUniform2i(shader, name, value);
}

void SetUniform3i(Shader *shader, const char *name, Vector3i value) {
    Internal_SetUniform3i(shader, name, value);
}

void SetUniform4i(Shader *shader, const char *name, Vector4i value) {
    Internal_SetUniform4i(shader, name, value);
}

void SetUniformMatrix4f(Shader *shader, const char *name, Matrix4f *value) {
    Internal_SetUniformMatrix4f(shader, name, value);
}


int IsKeyDown(int key) {
    return Internal_IsKeyDown(key);
}

int IsKeyReleased(int key) {
    return Internal_IsKeyReleased(key);
}

int IsButtonDown(int button) {
    return Internal_IsButtonDown(button);
}

int IsButtonReleased(int button) {
    return Internal_IsButtonReleased(button);
}

Vector2f GetMousePosition() {
    return Internal_GetMousePosition();
}

Vector2f GetMouseDelta() {
    return Internal_GetMouseDelta();
}