#ifndef HEADER_FLOAT_IMAGE
#define HEADER_FLOAT_IMAGE

#include <stdint.h>
#include "image.h"

typedef struct float_image {
    uint32_t width;
    uint32_t height;
    float *values;
} float_image_t;

void float_image_to_image(float_image_t *image_in, image_t *image_out, float min, float max);

#endif