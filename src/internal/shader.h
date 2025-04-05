#ifndef SHADER_H
#define SHADER_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Shader *Internal_CreateShaderBySource(const char *vertexSource, const char *fragmentSource);
Shader *Internal_CreateShader(const char *vertexFile, const char *fragmentFile);
void Internal_DestroyShader(Shader *shader);

void Internal_SetUniform1f(Shader *shader, const char *name, float value);
void Internal_SetUniform2f(Shader *shader, const char *name, Vector2f value);
void Internal_SetUniform3f(Shader *shader, const char *name, Vector3f value);
void Internal_SetUniform4f(Shader *shader, const char *name, Vector4f value);

void Internal_SetUniform1i(Shader *shader, const char *name, int value);
void Internal_SetUniform2i(Shader *shader, const char *name, Vector2i value);
void Internal_SetUniform3i(Shader *shader, const char *name, Vector3i value);
void Internal_SetUniform4i(Shader *shader, const char *name, Vector4i value);

void Internal_SetUniformMatrix4f(Shader *shader, const char *name, Matrix4f *value);

#ifdef __cplusplus
}
#endif

#endif
