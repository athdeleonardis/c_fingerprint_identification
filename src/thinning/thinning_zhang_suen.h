#ifndef HEADER_ZHANG_SUEN
#define HEADER_ZHANG_SUEN

#include <stdint.h>
#include "../image/bit_image.h"

uint8_t thinning_zhang_suen_pass_1_cell(bit_image_t *bit_image, uint32_t x, uint32_t y);
uint8_t thinning_zhang_suen_pass_2_cell(bit_image_t *bit_image, uint32_t x, uint32_t y);
uint8_t thinning_zhang_suen_pass_1(bit_image_t *bit_image, bit_image_t *to_remove);
uint8_t thinning_zhang_suen_pass_2(bit_image_t *bit_image, bit_image_t *to_remove);
void thinning_zhang_suen_update(bit_image_t *bit_image, bit_image_t *to_remove);
uint8_t thinning_zhang_suen_pass(bit_image_t *bit_image, bit_image_t *to_remove);
void thinning_zhang_suen(bit_image_t *bit_image, bit_image_t *to_remove);

#endif