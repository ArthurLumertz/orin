#include "shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ReadFile(const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory for file %s\n", filepath);
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    fclose(file);
    return buffer;
}

unsigned int CompileShader(int type, const char *source) {
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Shader compilation failed (%d): %s\n", shader, infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

Shader *Internal_CreateShaderBySource(const char *vertexSource, const char *fragmentSource) {
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0) {
        fprintf(stderr, "Failed to compile vertex shader\n");
        return NULL;
    }

    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0) {
        fprintf(stderr, "Failed to compile fragment shader\n");
        glDeleteShader(vertexShader);
        return NULL;
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Shader program linking failed: %s\n", infoLog);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(shaderProgram);
        return NULL;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    Shader *shader = (Shader *)malloc(sizeof(Shader));
    if (shader == NULL) {
        fprintf(stderr, "Failed to allocate memory for Shader object\n");
        glDeleteProgram(shaderProgram);
        return NULL;
    }

    shader->id = shaderProgram;
    return shader;
}

Shader *Internal_CreateShader(const char *vertexFile, const char *fragmentFile) {
    char *vertexSource = ReadFile(vertexFile);
    if (vertexSource == NULL) {
        return 0;
    }
    free(vertexSource);

    char *fragmentSource = ReadFile(fragmentFile);
    if (fragmentSource == NULL) {
        return 0;
    }
    free(fragmentSource);

    Shader *shader = Internal_CreateShaderBySource(vertexSource, fragmentSource);
    return shader;
}

void Internal_DestroyShader(Shader *shader) {
    if (shader) {
        glDeleteProgram(shader->id);
        free(shader);
    }
}

int Internal_GetShaderLocation(Shader *shader, const char *uniformName) {
    int location = glGetUniformLocation(shader->id, uniformName);
    if (location == -1) {
        fprintf(stderr, "Warning: Uniform '%s' not found or not used in the shader program\n", uniformName);
    }
    return location;
}

void Internal_SetShaderValue(Shader *shader, int location, const void *value, UniformType type) {
    switch (type) {
    case UNIFORM_FLOAT: {
        glUniform1f(location, *(float *)value);
    }
    case UNIFORM_INT: {
        glUniform1f(location, *(int *)value);
    }
    case UNIFORM_VEC2: {
        Vector2f v = *(Vector2f *)value;
        glUniform2f(location, v.x, v.y);
    }
    case UNIFORM_VEC2I: {
        Vector2i v = *(Vector2i *)value;
        glUniform2i(location, v.x, v.y);
    }
    case UNIFORM_VEC3: {
        Vector3f v = *(Vector3f *)value;
        glUniform3f(location, v.x, v.y, v.z);
    }
    case UNIFORM_VEC3I: {
        Vector3i v = *(Vector3i *)value;
        glUniform3i(location, v.x, v.y, v.z);
    }
    case UNIFORM_VEC4: {
        Vector4f v = *(Vector4f *)value;
        glUniform4f(location, v.x, v.y, v.z, v.w);
    }
    case UNIFORM_VEC4I: {
        Vector4i v = *(Vector4i *)value;
        glUniform4i(location, v.x, v.y, v.z, v.w);
    }
    case UNIFORM_MAT4: {
        static float values[16];
        static Matrix4f *mat;
        mat = (Matrix4f *)value;
        values[0] = mat->m00; values[1] = mat->m10; values[2] = mat->m20; values[3] = mat->m30;
        values[4] = mat->m01; values[5] = mat->m11; values[6] = mat->m21; values[7] = mat->m31;
        values[8] = mat->m02; values[9] = mat->m12; values[10] = mat->m22; values[11] = mat->m32;
        values[12] = mat->m03; values[13] = mat->m13; values[14] = mat->m23; values[15] = mat->m33;

        glUniformMatrix4fv(location, 1, GL_FALSE, values);
    }
    }
}