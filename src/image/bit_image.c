#include "bit_image.h"

typedef uint8_t (*bit_from_image_t)(image_t *image, uint32_t index, uint8_t threshold);

uint8_t _bit_from_image_1_channel(image_t *image, uint32_t index, uint8_t threshold) {
    return image->pixels[index] > threshold;
}

uint8_t _bit_from_image_3_channels(image_t *image, uint32_t index, uint8_t threshold) {
    uint8_t brightness = (image->pixels[index] + image->pixels[index + 1] + image->pixels[index + 2]) / 3;
    return brightness > threshold;
}

uint8_t _bit_from_image_4_channels(image_t *image, uint32_t index, uint8_t threshold) {
    uint8_t brightness = (image->pixels[index] + image->pixels[index + 1] + image->pixels[index + 2]) / 3;
    brightness = (brightness * image->pixels[index + 3]) / 255;
    return brightness > threshold;
}

uint8_t bit_image_pixel_from_coord(bit_image_t *image, uint32_t x, uint32_t y) {
    uint32_t index = x + image->width * y;
    uint32_t byte_index = index / 8;
    uint8_t bit_offset = index % 8;
    return (image->bytes[byte_index] & (1 << bit_offset)) > 0;
}

uint8_t bit_image_bit_from_index(bit_image_t *image, uint32_t index) {
    uint32_t byte_index = index / 8;
    uint8_t bit_offset = index % 8;
    return (image->bytes[byte_index] & (1 << bit_offset)) > 0;
}

void bit_image_set_pixel_zero(bit_image_t *image, uint32_t x, uint32_t y) {
    uint32_t index = x + image->width * y;
    uint32_t byte_index = index / 8;
    uint32_t bit_offset = index % 8;
    image->bytes[byte_index] &= ~(1 << bit_offset);
}

void bit_image_from_image(bit_image_t *bit_image, image_t *image, uint8_t threshold, uint8_t do_allocate) {
    bit_image->width = image->width;
    bit_image->height = image->height;

    bit_image->num_bytes = bit_image->width * bit_image->height;
    bit_image->num_bytes = bit_image->num_bytes / 8 + (bit_image->num_bytes % 8 > 0);
    if (do_allocate) {
        bit_image->bytes = (uint8_t *)malloc(bit_image->num_bytes);
    }

    bit_from_image_t bit_from_image = NULL;
    switch (image->channels) {
        case 1: {
            bit_from_image = _bit_from_image_1_channel;
            break;
        }
        case 3: {
            bit_from_image = _bit_from_image_3_channels;
            break;
        }
        case 4: {
            bit_from_image = _bit_from_image_4_channels;
            break;
        }
    }

    uint32_t index_max = image->width * image->height * image->channels;
    for (uint32_t index = 0; index < index_max; index += image->channels) {
        uint32_t pixel_index = index / image->channels;
        uint32_t byte_index = pixel_index / 8;
        uint8_t bit_offset = pixel_index % 8;
        if (bit_offset == 0) {
            bit_image->bytes[byte_index] = 0;
        }
        uint8_t value = bit_from_image(image, index, threshold);
        if (value) {
            bit_image->bytes[byte_index] |= value << bit_offset;
        }
    }
}

void bit_image_invert(bit_image_t *bit_image) {
    for (uint32_t byte_index = 0; byte_index < bit_image->num_bytes; byte_index++) {
        bit_image->bytes[byte_index] = ~bit_image->bytes[byte_index];
    }
}

void bit_image_clear(bit_image_t *bit_image) {
    for (uint32_t byte_index = 0; byte_index < bit_image->num_bytes; byte_index++) {
        bit_image->bytes[byte_index] = 0;
    }
}

void bit_image_write(bit_image_t *bit_image, const char *file) {
    uint32_t index_max = bit_image->width * bit_image->height;
    uint8_t *buffer = (uint8_t *)malloc(index_max);
    for (uint32_t index = 0; index < index_max; index++) {
        buffer[index] = bit_image_bit_from_index(bit_image, index) * 255;
    }
    image_t image = { .width=bit_image->width, .height=bit_image->height, .channels=1, .pixels=buffer };
    image_write(&image, file);
    free(buffer);
}
