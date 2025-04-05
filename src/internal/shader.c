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
    buffer[fileSize] = '\0'; // Null-terminate the string

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

static int GetUniformLocation(Shader *shader, const char *name) {
    int location = glGetUniformLocation(shader->id, name);
    if (location == -1) {
        fprintf(stderr, "Warning: Uniform '%s' not found or not used in the shader program\n", name);
    }
    return location;
}

void Internal_SetUniform1f(Shader *shader, const char *name, float value) {
    int location = GetUniformLocation(shader, name);
    glUniform1f(location, value);
}

void Internal_SetUniform2f(Shader *shader, const char *name, Vector2f value) {
    int location = GetUniformLocation(shader, name);
    glUniform2f(location, value.x, value.y);
}

void Internal_SetUniform3f(Shader *shader, const char *name, Vector3f value) {
    int location = GetUniformLocation(shader, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void Internal_SetUniform4f(Shader *shader, const char *name, Vector4f value) {
    int location = GetUniformLocation(shader, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Internal_SetUniform1i(Shader *shader, const char *name, int value) {
    int location = GetUniformLocation(shader, name);
    glUniform1i(location, value);
}

void Internal_SetUniform2i(Shader *shader, const char *name, Vector2i value) {
    int location = GetUniformLocation(shader, name);
    glUniform2i(location, value.x, value.y);
}

void Internal_SetUniform3i(Shader *shader, const char *name, Vector3i value) {
    int location = GetUniformLocation(shader, name);
    glUniform3i(location, value.x, value.y, value.z);
}

void Internal_SetUniform4i(Shader *shader, const char *name, Vector4i value) {
    int location = GetUniformLocation(shader, name);
    glUniform4i(location, value.x, value.y, value.z, value.w);
}

void Internal_SetUniformMatrix4f(Shader *shader, const char *name, Matrix4f *value) {
    int location = GetUniformLocation(shader, name);

    static float values[16];

    values[0] = value->m00; values[1] = value->m10; values[2] = value->m20; values[3] = value->m30;
    values[4] = value->m01; values[5] = value->m11; values[6] = value->m21; values[7] = value->m31;
    values[8] = value->m02; values[9] = value->m12; values[10] = value->m22; values[11] = value->m32;
    values[12] = value->m03; values[13] = value->m13; values[14] = value->m23; values[15] = value->m33;

    glUniformMatrix4fv(location, 1, GL_FALSE, values);
}