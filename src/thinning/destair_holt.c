#include "destair_holt.h"

// Finds cells where the neighbours follow these patterns, where atleast one cell marked x is zero.
// 0 1 x   -   x 1 0
// 1 1 x   -   x 1 1
// x x 0   -   0 x x
uint8_t destair_holt_pass_1_cell_condition(uint8_t n[]) {
    return n[0] * (
        (n[6] * !n[3] * !n[7] * !(n[1] * n[2] * n[4] * n[5])) ||
        (n[2] * !n[1] * !n[5] * !(n[3] * n[4] * n[6] * n[7]))
    );
}
// Finds cells where the neighbours follow these patterns, where atleast one cell marked x is zero.
// 0 x x   -   x x 0
// x 1 1   -   1 1 x
// x 1 0   -   0 1 x
uint8_t destair_holt_pass_2_cell_condition(uint8_t n[]) {
    return n[4] * (
        (n[2] * !n[3] * !n[7] * !(n[0] * n[1] * n[5] * n[6])) ||
        (n[6] * !n[1] * !n[5] * !(n[0] * n[2] * n[3] * n[7]))
    );
}

uint8_t destair_holt_pass_1_cell(bit_image_t *bit_image, bit_image_t *to_remove, uint32_t x, uint32_t y) {
    if (!bit_image_pixel_from_coord(bit_image, x, y)) {
        return 0;
    }
    uint8_t neighbours[8];
    bit_image_neighbours_from_coord(bit_image, x, y, neighbours);
    return destair_holt_pass_1_cell_condition(neighbours);
}

uint8_t destair_holt_pass_2_cell(bit_image_t *bit_image, bit_image_t *to_remove, uint32_t x, uint32_t y) {
    if (!bit_image_pixel_from_coord(bit_image, x, y)) {
        return 0;
    }
    uint8_t neighbours[8];
    bit_image_neighbours_from_coord(bit_image, x, y, neighbours);
    return destair_holt_pass_2_cell_condition(neighbours);
}

void destair_holt_pass_1(bit_image_t *bit_image, bit_image_t *to_remove) {
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            if (!destair_holt_pass_1_cell(bit_image, to_remove, x, y)) {
                continue;
            }
            uint32_t index = x + bit_image->width * y;
            uint32_t byte_index = index / 8;
            uint8_t bit_index = index % 8;
            to_remove->bytes[byte_index] |= 1 << bit_index;
        }
    }
}

void destair_holt_pass_2(bit_image_t *bit_image, bit_image_t *to_remove) {
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            if (!destair_holt_pass_2_cell(bit_image, to_remove, x, y)) {
                continue;
            }
            uint32_t index = x + bit_image->width * y;
            uint32_t byte_index = index / 8;
            uint8_t bit_index = index % 8;
            to_remove->bytes[byte_index] |= 1 << bit_index;
        }
    }
}

void destair_holt(bit_image_t *bit_image, bit_image_t *to_remove) {
    bit_image_clear(to_remove);
    destair_holt_pass_1(bit_image, to_remove);
    bit_image_remove_all(bit_image, to_remove);

    bit_image_clear(to_remove);
    destair_holt_pass_2(bit_image, to_remove);
    bit_image_remove_all(bit_image, to_remove);
}
