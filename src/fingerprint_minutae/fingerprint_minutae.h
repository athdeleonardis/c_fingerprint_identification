#ifndef HEADER_FINGERPRINT_MINUTAE
#define HEADER_FINGERPRINT_MINUTAE

#include <stdint.h>
#include "../image/bit_image.h"

#define FINGERPRINT_MINUTIA_NONE 0
#define FINGERPRINT_MINUTIA_RIDGE_ENDING 1
#define FINGERPRINT_MINUTIA_BIFURCATION 2

typedef struct fingerprint_minutia {
    uint8_t type;
    uint32_t x;
    uint32_t y;
} fingerprint_minutia_t;

uint8_t fingerprint_minutia_at_coord(bit_image_t *bit_image, uint32_t x, uint32_t y);
uint32_t fingerprint_minutae_count(bit_image_t *bit_image);
void fingerprint_minutae_write(bit_image_t *bit_image, fingerprint_minutia_t *minutae);
void image_add_minutae(image_t *image, fingerprint_minutia_t *minutae, uint32_t minutae_count);

#endif