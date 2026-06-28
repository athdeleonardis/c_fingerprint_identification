#ifndef HEADER_GRADIENT_SOBEL
#define HEADER_GRADIENT_SOBEL

#include "../image/image.h"
#include "../image/float_image.h"

float gradient_sobel_x_cell(image_t *image, uint32_t x, uint32_t y);
float gradient_sobel_y_cell(image_t *image, uint32_t x, uint32_t y);
float gradient_sobel_magnitude_cell(image_t *image, uint32_t x, uint32_t y);
void gradient_sobel_magnitude(image_t *image_in, float_image_t *image_out);

#endif