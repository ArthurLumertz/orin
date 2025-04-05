#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

Model *Internal_CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount) {
    Model *model = (Model*)malloc(sizeof(Model));
    if (model == NULL) {
        fprintf(stderr, "Failed to allocate memory for the model\n");
        return NULL;
    }

    model->vertexCount = vertexCount;
    model->indexCount = indexCount;

    model->vertices = (Vertex*)malloc(sizeof(Vertex) * vertexCount);
    model->indices = (unsigned int*)malloc(sizeof(unsigned int) * indexCount);

    if (model->vertices == NULL || model->indices == NULL) {
        fprintf(stderr, "Failed to allocate memory for the model data\n");
        free(model);
        return NULL;
    }

    memcpy(model->vertices, vertices, sizeof(Vertex) * vertexCount);
    memcpy(model->indices, indices, sizeof(unsigned int) * indexCount);

    glGenVertexArrays(1, &model->vao);
    glGenBuffers(1, &model->vbo);
    glGenBuffers(1, &model->ebo);

    glBindVertexArray(model->vao);

    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, model->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, model->indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    return model;
}

void Internal_DestroyModel(Model *model) {
    if (model == NULL) {
        return;
    }

    glDeleteBuffers(1, &model->vbo);
    glDeleteBuffers(1, &model->ebo);
    glDeleteVertexArrays(1, &model->vao);

    free(model->vertices);
    free(model->indices);
    free(model);
}
