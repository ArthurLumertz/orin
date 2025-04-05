#ifndef TEXTURE_H
#define TEXTURE_H

#include "../orin.h"

#ifdef __cplusplus
extern "C" {
#endif

Texture *Internal_LoadTexture(const char *filename, int filter);
void Internal_DestroyTexture(Texture *texture);

#ifdef __cplusplus
}
#endif

#endif
