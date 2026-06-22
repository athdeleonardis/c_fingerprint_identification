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
void image_set_pixel(image_t *image, uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4);
uint8_t image_write(image_t *image, const char *file);
void image_free(image_t *image);

#endif