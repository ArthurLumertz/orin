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

    static Matrix4f viewMatrix;
    static Matrix4f translatedView;
    static Matrix4f combinedMatrix;
    static Matrix4f projMatrix;
    
    Vector3f cameraTranslation = { -camera.position.x, -camera.position.y, 0.0f };

    OrthoMatrix4f(&projMatrix, 0.0f, vw, vh, 0.0f, -1.0f, 1.0f);
    IdentityMatrix4f(&viewMatrix);
    TranslateMatrix4f(&translatedView, &viewMatrix, cameraTranslation);
    MultiplyMatrix4f(&combinedMatrix, &projMatrix, &translatedView);

    static int combMatrixLocation = 0;
    static bool hasFetchedMatrix = false;
    if (!hasFetchedMatrix) {
        combMatrixLocation = GetShaderLocation(shader, "u_combmatrix");
        hasFetchedMatrix = true;
    }
    SetShaderValue(shader, combMatrixLocation, &combinedMatrix, UNIFORM_MAT4);
}

void Internal_EndDrawing() {

}

void Internal_DrawModel(Model *model, Vector3f position, Vector3f scale, Color tint, Shader *shader) {
    static unsigned int lastVao = 999;

    if (lastVao != model->vao) {
        glBindVertexArray(model->vao);
    }

    static Matrix4f transform;
    static Matrix4f scaled;
    static Matrix4f translated;

    IdentityMatrix4f(&transform);
    ScaleMatrix4f(&scaled, &transform, scale);
    TranslateMatrix4f(&translated, &scaled, position);

    static int locationTransMatrix;
    static bool hasFetchedTransMatrix = false;
    if (!hasFetchedTransMatrix) {
        locationTransMatrix = GetShaderLocation(shader, "u_transmatrix");
        hasFetchedTransMatrix = true;
    }
    SetShaderValue(shader, locationTransMatrix, &translated, UNIFORM_MAT4);
    glDrawElements(GL_TRIANGLES, model->indexCount, GL_UNSIGNED_INT, 0);

    lastVao = model->vao;
}

void Internal_DrawRectangle(Shader *shader, float x, float y, float width, float height, Color tint) {
    Vector4f color = {
        tint.r / 255.0f,
        tint.g / 255.0f,
        tint.b / 255.0f,
        tint.a / 255.0f
    };

    static int location = 0;
    static bool hasFetched = false;
    if (!hasFetched) {
        location = GetShaderLocation(shader, "u_color");
        hasFetched = true;
    }
    SetShaderValue(shader, location, &color, UNIFORM_VEC4);
    Internal_DrawModel(GetCubeModel(), (Vector3f){ x, y, 0.0f }, (Vector3f){ width, height, 0.0f }, tint, shader);
}

void Internal_DrawTexture(Shader *shader, Texture *texture, float x, float y, float width, float height, Color tint) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    static int locationTexture = 0;
    static bool hasFetchedTexture = false;
    if (!hasFetchedTexture) {
        locationTexture = GetShaderLocation(shader, "u_texture");
        hasFetchedTexture = true;
    }
    
    int value = 1;
    SetShaderValue(shader, locationTexture, &value, UNIFORM_INT);

    static int locationSampler = 0;
    static bool hasFetchedSampler = false;
    if (!hasFetchedSampler) {
        locationSampler = GetShaderLocation(shader, "u_sampler");
        hasFetchedSampler = true;
    }
    value = 0;
    SetShaderValue(shader, locationSampler, &value, UNIFORM_INT);

    Vector4f color = {
        tint.r / 255.0f,
        tint.g / 255.0f,
        tint.b / 255.0f,
        tint.a / 255.0f
    };

    static int locationColor = 0;
    static bool hasFetchedColor = false;
    if (!hasFetchedColor) {
        locationColor = GetShaderLocation(shader, "u_color");
        hasFetchedColor = true;
    }
    SetShaderValue(shader, locationColor, &color, UNIFORM_VEC4);
    Internal_DrawModel(GetCubeModel(), (Vector3f) { x, y, 0.0f }, (Vector3f) { width, height, 0.0f }, tint, shader);

    value = 0;
    SetShaderValue(shader, locationTexture, &value, UNIFORM_INT);
}