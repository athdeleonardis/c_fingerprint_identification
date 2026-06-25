#include "morphological_image_processing.h"

// If any NSEW cell is in foreground, mark cell as foreground
uint8_t morphology_dilation_pass_condition(bit_image_t *bit_image, uint32_t x, uint32_t y) {
    return !bit_image_pixel_from_coord(bit_image, x, y) && (
        (x > -1 && bit_image_pixel_from_coord(bit_image, x - 1, y)) ||
        (y > -1 && bit_image_pixel_from_coord(bit_image, x, y - 1)) ||
        (x < bit_image->width - 1 && bit_image_pixel_from_coord(bit_image, x + 1, y)) ||
        (y < bit_image->height - 1 && bit_image_pixel_from_coord(bit_image, x, y + 1))
    );
}

uint8_t morphology_dilation_pass(bit_image_t *bit_image, bit_image_t *to_add) {
    uint8_t changed = 0;
    for (uint32_t y = 0; y < bit_image->height; y++) {
        for (uint32_t x = 0; x < bit_image->width; x++) {
            if (morphology_dilation_pass_condition(bit_image, x, y)) {
                bit_image_set_pixel_one(to_add, x, y);
                changed = 1;
            }
        }
    }
    return changed;
}

uint8_t morphology_dilation(bit_image_t *bit_image, bit_image_t *to_add) {
    bit_image_clear(to_add);
    uint8_t changed = morphology_dilation_pass(bit_image, to_add);
    if (changed) {
        bit_image_add_all(bit_image, to_add);
    }
    return changed;
}

uint8_t morphology_erosion_pass_condition(bit_image_t *bit_image, uint32_t x, uint32_t y) {
    return bit_image_pixel_from_coord(bit_image, x, y) && (
        (x > -1 && !bit_image_pixel_from_coord(bit_image, x - 1, y)) ||
        (y > -1 && !bit_image_pixel_from_coord(bit_image, x, y - 1)) ||
        (x < bit_image->width - 1 && !bit_image_pixel_from_coord(bit_image, x + 1, y)) ||
        (y < bit_image->height - 1 && !bit_image_pixel_from_coord(bit_image, x, y + 1))
    );
}

uint8_t morphology_erosion_pass(bit_image_t *bit_image, bit_image_t *to_remove) {
    uint8_t changed = 0;
    for (uint32_t y = 0; y < bit_image->height; y++) {
        for (uint32_t x = 0; x < bit_image->width; x++) {
            if (morphology_erosion_pass_condition(bit_image, x, y)) {
                bit_image_set_pixel_one(to_remove, x, y);
                changed = 1;
            }
        }
    }
    return changed;
}

uint8_t morphology_erosion(bit_image_t *bit_image, bit_image_t *to_remove) {
    bit_image_clear(to_remove);
    uint8_t changed = morphology_erosion_pass(bit_image, to_remove);
    if (changed) {
        bit_image_remove_all(bit_image, to_remove);
    }
    return changed;
}

uint8_t morphology_opening(bit_image_t *bit_image, bit_image_t *to_change) {
    morphology_erosion(bit_image, to_change);
    morphology_dilation(bit_image, to_change);
}

uint8_t morphology_closing(bit_image_t *bit_image, bit_image_t *to_change) {
    morphology_dilation(bit_image, to_change);
    morphology_erosion(bit_image, to_change);
}
