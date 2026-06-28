#include <stdio.h>
#include "../../src/image_processing/gradient_sobel.h"
#include "../../src/util/float_array.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Input atleast one filename.\n");
        exit(0);
    }

    char filename[75];
    image_t image;
    image_t image_grayscale;
    float_image_t float_image;
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        snprintf(filename, 75, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("-- Loaded. Width: %d, Height: %d, Channels: %d\n", image.width, image.height, image.channels);

        image_to_grayscale(&image, &image_grayscale, 1);
        snprintf(filename, 75, "out/test/gradient_sobel/%s-temp.png", argv[i]);
        image_write(&image_grayscale, filename);
        printf("-- Converted to grayscale.\n");
        
        uint32_t num_pixels = image.width * image.height;
        float_image.width = image.width;
        float_image.height = image.height;
        float_image.values = (float *)malloc(num_pixels * sizeof(float));
        gradient_sobel_magnitude(&image_grayscale, &float_image);
        printf("-- Computed Sobel gradient magnitude.\n");

        float max_value = float_array_max(float_image.values, num_pixels);
        printf("-- Computed max value.\n");

        float_image_to_image(&float_image, &image_grayscale, 0, max_value);
        printf("-- Converted to image.\n");

        snprintf(filename, 75, "out/test/gradient_sobel/%s.png", argv[i]);
        image_write(&image_grayscale, filename);
        printf("-- Written.\n");

        image_free(&image);
        free(image_grayscale.pixels);
        free(float_image.values);
    }
}