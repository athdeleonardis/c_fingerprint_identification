#ifndef HEADER_BIT_IMAGE
#define HEADER_BIT_IMAGE

#include <stdint.h>
#include "image.h"

typedef struct bit_image {
    uint32_t width;
    uint32_t height;
    uint32_t num_bytes;
    uint8_t *bytes;
} bit_image_t;

uint8_t bit_image_pixel_from_coord(bit_image_t *image, uint32_t x, uint32_t y);
uint8_t bit_image_bit_from_index(bit_image_t *image, uint32_t index);
void bit_image_set_pixel_zero(bit_image_t *bit_image, uint32_t x, uint32_t y);
void bit_image_from_image(bit_image_t *bit_image, image_t *image, uint8_t threshold, uint8_t do_allocate);
void bit_image_invert(bit_image_t *bit_image);
void bit_image_clear(bit_image_t *bit_image);
void bit_image_write(bit_image_t *bit_image, const char *file);

#endif