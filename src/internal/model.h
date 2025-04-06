#ifndef ORIN_MODEL_H
#define ORIN_MODEL_H

#include "./orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Model *Internal_CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount);
void Internal_DestroyModel(Model *model);

#ifdef __cplusplus
}
#endif

#endif
