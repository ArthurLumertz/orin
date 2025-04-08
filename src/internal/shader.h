#ifndef ORIN_SHADER_H
#define ORIN_SHADER_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Shader *Internal_CreateShaderBySource(const char *vertexSource, const char *fragmentSource);
Shader *Internal_CreateShader(const char *vertexFile, const char *fragmentFile);
void Internal_DestroyShader(Shader *shader);

int Internal_GetShaderLocation(Shader *shader, const char *uniformName);
void Internal_SetShaderValue(Shader *shader, int location, const void *value, UniformType type);

#ifdef __cplusplus
}
#endif

#endif
