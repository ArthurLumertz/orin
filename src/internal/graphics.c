#include "graphics.h"
#include "../orinmath.h"
#include <glad/glad.h>
#include "shader.h"
#include <stdio.h>

Model *GetCubeModel() {
    static Model *model = NULL;

    if (model == NULL) {
        Vertex vertices[] = {
            {(Vector2f){0.0f, 0.0f}, (Vector2f){0.0f, 0.0f}, (Vector2f){0.0f, 1.0f}, WHITE},
            {(Vector2f){1.0f, 0.0f}, (Vector2f){1.0f, 0.0f}, (Vector2f){0.0f, 1.0f}, WHITE},
            {(Vector2f){1.0f, 1.0f}, (Vector2f){1.0f, 1.0f}, (Vector2f){0.0f, 1.0f}, WHITE},
            {(Vector2f){0.0f, 1.0f}, (Vector2f){0.0f, 1.0f}, (Vector2f){0.0f, 1.0f}, WHITE},
        };
        unsigned int indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        model = CreateModel(vertices, ARRAY_SIZE(vertices), indices, ARRAY_SIZE(indices));
    }
    return model;
}

void Internal_ClearBackground(Color color) {
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Internal_BeginDrawing(Camera2D camera, Shader *shader, Display *display) {
    float vw = display->displayMode.width;
    float vh = display->displayMode.height;

    static unsigned int lastProgram = 999;

    if (lastProgram != shader->id) {
        glUseProgram(shader->id);
        lastProgram = shader->id;
    }

    Matrix4f projMatrix = OrthoMatrix4f(0.0f, vw, vh, 0.0f, -1.0f, 1.0f);
    Matrix4f viewMatrix = IdentityMatrix4f();
    viewMatrix = TranslateMatrix4f(viewMatrix, (Vector3f){-camera.position.x, -camera.position.y, 0.0f});

    Matrix4f combinedMatrix = MultiplyMatrix4f(projMatrix, viewMatrix);
    SetUniformMatrix4f(shader, "u_combmatrix", &combinedMatrix);
}

void Internal_EndDrawing() {

}

void Internal_SetColor(Color color, Shader *shader) {
    Vector4f c = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
    SetUniform4f(shader, "u_color", c);
}

void Internal_DrawModel(Model *model, Matrix4f transform, Shader *shader) {
    static unsigned int lastVao = 999;

    if (lastVao != model->vao) {
        glBindVertexArray(model->vao);
    }

    SetUniformMatrix4f(shader, "u_transmatrix", &transform);

    glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);

    lastVao = model->vao;
}

void Internal_DrawRectangle(Shader *shader, Vector2f position, Vector2f size, Color color) {
    Matrix4f transform = IdentityMatrix4f();
    transform = ScaleMatrix4f(transform, (Vector3f){size.x,size.y,0.0f});
    transform = TranslateMatrix4f(transform, (Vector3f){position.x,position.y,0.0f});
    Vector4f c = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
    SetUniform4f(shader, "u_color", c);
    Internal_DrawModel(GetCubeModel(), transform, shader);
}

void Internal_DrawTexture(Shader *shader, Texture *texture, Vector2f position, Vector2f size, Color color) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    SetUniform1i(shader, "u_texture", 1);
    SetUniform1i(shader, "u_sampler", 0);
    Vector4f c = { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
    SetUniform4f(shader, "u_color", c);

    Matrix4f transform = IdentityMatrix4f();
    transform = ScaleMatrix4f(transform, (Vector3f){size.x,size.y,0.0f});
    transform = TranslateMatrix4f(transform, (Vector3f){position.x,position.y,0.0f});
    Internal_DrawModel(GetCubeModel(), transform, shader);

    SetUniform1i(shader, "u_texture", 0);
}