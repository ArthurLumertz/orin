#include "texture.h"
#include <stb_image.h>
#include <stdio.h>
#include <stdlib.h>

Texture *Internal_LoadTexture(const char *filename, int filter) {
    if (filename == NULL) {
        fprintf(stderr, "Filename is NULL\n");
        return NULL;
    }

    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    if (data == NULL) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
        return NULL;
    }

    Texture *texture = (Texture*)malloc(sizeof(Texture));
    if (texture == NULL) {
        fprintf(stderr, "Failed to allocate memory for texture\n");
        stbi_image_free(data);
        return NULL;
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    texture->width = width;
    texture->height = height;
    texture->channels = STBI_rgb_alpha;

    stbi_image_free(data);
    return texture;
}

void Internal_DestroyTexture(Texture *texture) {
    if (texture == NULL) {
        return;
    }
    glDeleteTextures(1, &texture->id);
    free(texture);
}