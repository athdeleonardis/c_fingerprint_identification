#include "float_image.h"

void float_image_to_image(float_image_t *image_in, image_t *image_out, float min, float max) {
    float range = max - min;
    uint32_t index_max = image_in->width * image_in->height;
    for (uint32_t index = 0; index < index_max; index++) {
        float value_in = image_in->values[index];
        float value_out = (value_in - min) / range;
        if (value_out < 0) {
            value_out = 0;
        }
        if (value_out > 1) {
            value_out = 1;
        }
        image_out->pixels[index] = (uint8_t)(value_out * 255);
    }
}