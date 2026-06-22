#include "fingerprint_minutae.h"

// Neighbour indices
// 7 0 1
// 6 x 2
// 5 4 3

//                       neigbour   0,  1,  2,  3,  4,  5,  6,  7
uint32_t _neighbour_offset_x[8] = {  0,  1,  1,  1,  0, -1, -1, -1 };
uint32_t _neighbour_offset_y[8] = { -1, -1,  0,  1,  1,  1,  0, -1 };

uint8_t fingerprint_minutia_at_coord(bit_image_t *bit_image, uint32_t x, uint32_t y) {
    if (!bit_image_pixel_from_coord(bit_image, x, y)) {
        return FINGERPRINT_MINUTIA_NONE;
    }
    uint8_t count = 0;
    for (uint8_t i = 0; i < 8; i++) {
        count += bit_image_pixel_from_coord(
            bit_image,
            x + _neighbour_offset_x[i],
            y + _neighbour_offset_y[i]
        );
        if (count > 3) {
            return FINGERPRINT_MINUTIA_NONE;
        }
    }
    if (count == 1) {
        return FINGERPRINT_MINUTIA_RIDGE_ENDING;
    }
    if (count == 3) {
        return FINGERPRINT_MINUTIA_BIFURCATION;
    }
    return FINGERPRINT_MINUTIA_NONE;
}

uint32_t fingerprint_minutae_count(bit_image_t *bit_image) {
    uint32_t count = 0;
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            count += fingerprint_minutia_at_coord(bit_image, x, y) != FINGERPRINT_MINUTIA_NONE;
        }
    }
    return count;
}

void fingerprint_minutae_write(bit_image_t *bit_image, fingerprint_minutia_t *minutae) {
    for (uint32_t y = 1; y < bit_image->height - 1; y++) {
        for (uint32_t x = 1; x < bit_image->width - 1; x++) {
            uint8_t minutia = fingerprint_minutia_at_coord(bit_image, x, y);
            if (minutia == FINGERPRINT_MINUTIA_NONE) {
                continue;
            }
            minutae->type = minutia;
            minutae->x = x;
            minutae->y = y;
            minutae++;
        }
    }
}

void image_add_minutae(image_t *image, fingerprint_minutia_t *minutae, uint32_t minutae_count) {
    if (image->channels < 3)
        return;
    for (uint32_t i = 0; i < minutae_count; i++) {
        uint8_t red = (minutae[i].type == FINGERPRINT_MINUTIA_RIDGE_ENDING) * 255;
        uint8_t blue = (minutae[i].type == FINGERPRINT_MINUTIA_BIFURCATION) * 255;
        image_set_pixel(image, minutae[i].x, minutae[i].y, red, blue, 0, 255);
    }
}
