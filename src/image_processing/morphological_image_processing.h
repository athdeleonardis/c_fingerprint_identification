#ifndef HEADER_MORPHOLOGICAL_IMAGE_PROCESSING
#define HEADER_MORPHOLOGICAL_IMAGE_PROCESSING

#include "../image/bit_image.h"

uint8_t morphology_dilation_pass_condition(bit_image_t *image, uint32_t x, uint32_t y);
uint8_t morphology_dilation_pass(bit_image_t *bit_image, bit_image_t *to_add);
uint8_t morphology_dilation(bit_image_t *bit_image, bit_image_t *to_add);
uint8_t morphology_erosion_pass_condition(bit_image_t *image, uint32_t x, uint32_t y);
uint8_t morphology_erosion_pass(bit_image_t *bit_image, bit_image_t *to_remove);
uint8_t morphology_erosion(bit_image_t *bit_image, bit_image_t *to_remove);
uint8_t morphology_opening(bit_image_t *bit_image, bit_image_t *to_change);
uint8_t morphology_closing(bit_image_t *bit_image, bit_image_t *to_change);

#endif