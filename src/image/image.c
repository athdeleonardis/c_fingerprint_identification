#include "image.h"

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

uint8_t image_write(image_t *image, const char *file) {
    int success = stbi_write_png(file, image->width, image->height, image->channels, image->pixels, image->width * image->channels);
    return success != 0;
}

void image_free(image_t *image) {
    stbi_image_free(image->pixels);
}
