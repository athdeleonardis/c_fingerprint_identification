#ifndef HEADER_IMAGE
#define HEADER_IMAGE

#include "../../lib/stb/stb_image.h"
#include "../../lib/stb/stb_image_write.h"
#include <stdint.h>

typedef struct image {
    uint32_t width;
    uint32_t height;
    uint8_t channels;
    uint8_t *pixels;
} image_t;

uint8_t image_load(image_t *image, const char *file);
uint8_t image_write(image_t *image, const char *file);
void image_free(image_t *image);

#endif