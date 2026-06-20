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

uint8_t image_write(image_t *image, const char *file) {
    int success = stbi_write_png(file, image->width, image->height, image->channels, image->pixels, image->width * image->channels);
    return success != 0;
}

void image_free(image_t *image) {
    stbi_image_free(image->pixels);
}
