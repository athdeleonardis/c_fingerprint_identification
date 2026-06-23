#include <stdio.h>
#include <stdint.h>
#include "destair_holt.h"
#include "thinning_zhang_suen.h"

// Cell neighbour labellings
// 7 0 1
// 6 x 2
// 5 4 3

//                                 cell neighbour   0,  1,  2,  3,  4,  5,  6,  7
uint32_t _thinning_zhang_suen_cell_offset_x[] = {   0,  1,  1,  1,  0, -1, -1, -1 };
uint32_t _thinning_zhang_suen_cell_offset_y[] = {  -1, -1,  0,  1,  1,  1,  0, -1 };

//
// 'thinning_zhang_suen.c' implementations
//

void _thinning_zhang_suen_calculate_neighbours(bit_image_t *bit_image, uint32_t x, uint32_t y, uint8_t neighbours[]) {
    for (uint8_t i = 0; i < 8; i++) {
        neighbours[i] = bit_image_pixel_from_coord(
            bit_image,
            x + _thinning_zhang_suen_cell_offset_x[i],
            y + _thinning_zhang_suen_cell_offset_y[i]
        );
    }
    neighbours[8] = neighbours[0];
}

uint8_t _thinning_zhang_suen_condition_neighbours_count(uint8_t neighbours[]) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < 8; i++) {
        count += neighbours[i];
    }
    return count > 1 && count < 7;
}

uint8_t _thinning_zhang_suen_condition_neighbours_increase(uint8_t neighbours[]) {
    uint8_t num_increases = 0;
    for (uint8_t i = 0; i < 8; i++) {
        num_increases += neighbours[i + 1] > neighbours[i];
        if (num_increases > 1)
            return 0;
    }
    return num_increases;
}

uint8_t _thinning_zhang_suen_condition_pass_1(uint8_t neighbours[]) {
    return !(neighbours[0] * neighbours[2] * neighbours[4]) && !(neighbours[2] * neighbours[4] * neighbours[6]);
}

uint8_t _thinning_zhang_suen_condition_pass_2(uint8_t neighbours[]) {
    return !(neighbours[0] * neighbours[2] * neighbours[6]) && !(neighbours[0] * neighbours[4] * neighbours[6]);
}

//
// 'thinning_zhang_suen.h' implementations
//

uint8_t thinning_zhang_suen_pass_1_cell(bit_image_t *bit_image, uint32_t x, uint32_t y) {
    uint8_t neighbours[9];
    _thinning_zhang_suen_calculate_neighbours(bit_image, x, y, neighbours);
    return
        _thinning_zhang_suen_condition_neighbours_count(neighbours) &&
        _thinning_zhang_suen_condition_neighbours_increase(neighbours) &&
        _thinning_zhang_suen_condition_pass_1(neighbours);
}

uint8_t thinning_zhang_suen_pass_2_cell(bit_image_t *bit_image, uint32_t x, uint32_t y) {
    uint8_t neighbours[9];
    _thinning_zhang_suen_calculate_neighbours(bit_image, x, y, neighbours);
    return
        _thinning_zhang_suen_condition_neighbours_count(neighbours) &&
        _thinning_zhang_suen_condition_neighbours_increase(neighbours) &&
        _thinning_zhang_suen_condition_pass_2(neighbours);
}

uint8_t thinning_zhang_suen_pass_1(bit_image_t *bit_image, bit_image_t *to_remove) {
    uint8_t unfinished = 0;
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            uint32_t bit_index = x + bit_image->width * y;
            if (!bit_image_bit_from_index(bit_image, bit_index)) {
                continue;
            }

            uint8_t do_remove = thinning_zhang_suen_pass_1_cell(bit_image, x, y);
            if (!do_remove) {
                continue;
            }

            unfinished = 1;
            uint32_t byte_index = bit_index / 8;
            uint8_t bit_offset = bit_index % 8;
            to_remove->bytes[byte_index] |= 1 << bit_offset;
        }
    }
    return unfinished;
}

uint8_t thinning_zhang_suen_pass_2(bit_image_t *bit_image, bit_image_t *to_remove) {
    uint8_t unfinished = 0;
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            uint32_t bit_index = x + bit_image->width * y;
            if (!bit_image_bit_from_index(bit_image, bit_index)) {
                continue;
            }

            uint8_t do_remove = thinning_zhang_suen_pass_2_cell(bit_image, x, y);
            if (!do_remove) {
                continue;
            }

            unfinished = 1;
            uint32_t byte_index = bit_index / 8;
            uint8_t bit_offset = bit_index % 8;
            to_remove->bytes[byte_index] |= 1 << bit_offset;
        }
    }
    return unfinished;
}

uint8_t thinning_zhang_suen_pass(bit_image_t *bit_image, bit_image_t *to_remove) {
    bit_image_clear(to_remove);
    uint8_t unfinished1 = thinning_zhang_suen_pass_1(bit_image, to_remove);
    if (unfinished1) {
        bit_image_remove_all(bit_image, to_remove);
    }

    bit_image_clear(to_remove);
    uint8_t unfinished2 = thinning_zhang_suen_pass_2(bit_image, to_remove);
    if (unfinished2) {
        bit_image_remove_all(bit_image, to_remove);
    }
    return unfinished1 || unfinished2;
}

void thinning_zhang_suen(bit_image_t *bit_image, bit_image_t *to_remove) {
    int iteration = 0;
    while (thinning_zhang_suen_pass(bit_image, to_remove));
    destair_holt(bit_image, to_remove);
}