#include "destair_holt.h"

// 0 1 x       x 1 0
// 1 1 x       x 1 1
// x x 0       0 x x
uint8_t _destair_holt_cell_1(uint8_t n[]) {
    return n[0] * (
        (n[6] * !n[3] * !n[7] * !(n[1] * n[2] * n[4] * n[5])) ||
        (n[2] * !n[1] * !n[5] * !(n[3] * n[4] * n[6] * n[7]))
    );
}

uint8_t _destair_holt_cell_2(uint8_t n[]) {
    return n[4] * (
        (n[2] * !n[3] * !n[7] * !(n[0] * n[1] * n[5] * n[6])) ||
        (n[6] * !n[1] * !n[5] * !(n[0] * n[2] * n[3] * n[7]))
    );
}

uint8_t destair_holt_cell(bit_image_t *bit_image, bit_image_t *to_remove, uint32_t x, uint32_t y) {
    if (!bit_image_pixel_from_coord(bit_image, x, y)) {
        return 0;
    }
    uint8_t neighbours[8];
    bit_image_neighbours_from_coord(bit_image, x, y, neighbours);
    return _destair_holt_cell_1(neighbours) || _destair_holt_cell_2(neighbours);
}

void destair_holt(bit_image_t *bit_image, bit_image_t *to_remove) {
    bit_image_clear(to_remove);
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            if (!destair_holt_cell(bit_image, to_remove, x, y)) {
                continue;
            }
            uint32_t index = x + bit_image->width * y;
            uint32_t byte_index = index / 8;
            uint8_t bit_index = index % 8;
            to_remove->bytes[byte_index] |= 1 << bit_index;
        }
    }
}
