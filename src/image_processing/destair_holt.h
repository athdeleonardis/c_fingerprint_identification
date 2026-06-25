#ifndef HEADER_DESTAIR_HOLT
#define HEADER_DESTAIR_HOLT

#include "../image/bit_image.h"

uint8_t destair_holt_pass_1_cell_condition(uint8_t n[]);
uint8_t destair_holt_pass_2_cell_condition(uint8_t n[]);
uint8_t destair_holt_pass_1_cell(bit_image_t *bit_image, bit_image_t *to_remove, uint32_t x, uint32_t y);
uint8_t destair_holt_pass_2_cell(bit_image_t *bit_image, bit_image_t *to_remove, uint32_t x, uint32_t y);
void destair_holt_pass_1(bit_image_t *bit_image, bit_image_t *to_remove);
void destair_holt_pass_2(bit_image_t *bit_image, bit_image_t *to_remove);
void destair_holt(bit_image_t *bit_image, bit_image_t *to_remove);

#endif