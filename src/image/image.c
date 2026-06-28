#include "image.h"

uint8_t _image_to_grayscale_cell_1(image_t *image, uint32_t index) {
    return image->pixels[index];
}

uint8_t _image_to_grayscale_cell_2(image_t *image, uint32_t index) {
    return ((uint16_t)image->pixels[index]) * image->pixels[index + 1] / 255;
}

uint8_t _image_to_grayscale_cell_3(image_t *image, uint32_t index) {
    return ((uint16_t)image->pixels[index] + image->pixels[index + 1] + image->pixels[index + 2]) / 3;
}

uint8_t _image_to_grayscale_cell_4(image_t *image, uint32_t index) {
    return ((uint32_t)image->pixels[index] + image->pixels[index + 1] + image->pixels[index + 2]) * image->pixels[index + 3] / (3 * 255);
}

uint8_t _image_to_grayscale_cell(image_t *image, uint32_t index) {
    switch (image->channels) {
        case 1:
            return _image_to_grayscale_cell_1(image, index);
        case 2:
            return _image_to_grayscale_cell_2(image, index);
        case 3:
            return _image_to_grayscale_cell_3(image, index);
        case 4:
            return _image_to_grayscale_cell_4(image, index);            
    }
}

uint8_t image_load(image_t *image, const char *file) {
    int width;
    int height;
    int channels;
    image->pixels = stbi_load(file, &width, &height, &channels, 0);
    image->width = width;
    image->height = height;
    image->channels = channels;
    return image->pixels != NULL;
}

void image_set_pixel(image_t *image, uint32_t x, uint32_t y, uint8_t c1, uint8_t c2, uint8_t c3, uint8_t c4) {
    uint32_t index = (x + image->width * y) * image->channels;
    image->pixels[index] = c1;
    if (image->channels > 1) {
        image->pixels[index + 1] = c2;
    }
    if (image->channels > 2) {
        image->pixels[index + 2] = c3;
    }
    if (image->channels > 3) {
        image->pixels[index + 3] = c4;
    }
}

void image_to_grayscale(image_t *image_in, image_t *image_out, uint8_t do_allocate) {
    image_out->width = image_in->width;
    image_out->height = image_in->height;
    image_out->channels = 1;
    uint32_t index_max = image_in->width * image_in->height;

    if (do_allocate) {
        image_out->pixels = (uint8_t *)malloc(index_max);
    }

    for (uint32_t index = 0; index < index_max; index++) {
        image_out->pixels[index] = _image_to_grayscale_cell(image_in, index * image_in->channels);
    }
}

uint8_t image_write(image_t *image, const char *file) {
    int success = stbi_write_png(file, image->width, image->height, image->channels, image->pixels, image->width * image->channels);
    return success != 0;
}

void image_free(image_t *image) {
    stbi_image_free(image->pixels);
}
