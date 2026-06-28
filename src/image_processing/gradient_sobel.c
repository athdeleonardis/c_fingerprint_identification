#include "gradient_sobel.h"
#include "math.h"

uint8_t _gradient_sobel_image_pixel_wrapper(image_t *image, uint32_t x, uint32_t y) {
    if (x < 0) {
        x = 0;
    } else if (x >= image->width) {
        x = image->width - 1;
    }
    if (y < 0) {
        y = 0;
    } else if (y >= image->height) {
        y = image->height - 1;
    }
    uint32_t index = x + image->width * y;
    return image->pixels[index];
}

// expects a grayscale image
// -1  0  1
// -2  0  2
// -1  0  1
float gradient_sobel_x_cell(image_t *image, uint32_t x, uint32_t y) {
    return (float)_gradient_sobel_image_pixel_wrapper(image, x + 1, y - 1)
        + 2 * _gradient_sobel_image_pixel_wrapper(image, x + 1, y)
        + _gradient_sobel_image_pixel_wrapper(image, x + 1, y + 1)
        - _gradient_sobel_image_pixel_wrapper(image, x - 1, y - 1)
        - 2 * _gradient_sobel_image_pixel_wrapper(image, x - 1, y)
        - _gradient_sobel_image_pixel_wrapper(image, x - 1, y + 1);
}

// expects a grayscale image
// -1 -2 -1
//  0  0  0
//  1  2  1
float gradient_sobel_y_cell(image_t *image, uint32_t x, uint32_t y) {
    return (float)_gradient_sobel_image_pixel_wrapper(image, x - 1, y + 1)
        + 2 * _gradient_sobel_image_pixel_wrapper(image, x, y + 1)
        + _gradient_sobel_image_pixel_wrapper(image, x + 1, y + 1)
        - _gradient_sobel_image_pixel_wrapper(image, x - 1, y - 1)
        - 2 * _gradient_sobel_image_pixel_wrapper(image, x, y - 1)
        - _gradient_sobel_image_pixel_wrapper(image, x + 1, y - 1);
}

float gradient_sobel_magnitude_cell(image_t *image, uint32_t x, uint32_t y) {
    float dx = gradient_sobel_x_cell(image, x, y);
    float dy = gradient_sobel_y_cell(image, x, y);
    return sqrtf(dx * dx + dy * dy);
}

void gradient_sobel_magnitude(image_t *image_in, float_image_t *image_out) {
    for (uint32_t y = 0; y < image_out->height; y++) {
        for (uint32_t x = 0; x < image_out->width; x++) {
            uint32_t index = x + image_out->width * y;
            image_out->values[index] = gradient_sobel_magnitude_cell(image_in, x, y);
        }
    }
}
