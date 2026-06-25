#include <stdio.h>
#include "../../src/image_processing/morphological_image_processing.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("First arg is 0 or 1 to invert, second is num of iterations, rest of args are filenames.\n");
        exit(0);
    }

    int do_invert;
    int iterations;
    sscanf(argv[1], "%d", &do_invert);
    sscanf(argv[2], "%d", &iterations);

    char filename[75];
    image_t image;
    bit_image_t bit_image;
    bit_image_t changes;
    for (int i = 3; i < argc; i++) {
        printf(argv[i]);
        snprintf(filename, 75, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("-- Loaded. Width: %d, Height: %d, Channels: %d\n", image.width, image.height, image.channels);

        bit_image_from_image(&bit_image, &image, 126, 1);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        changes.width = bit_image.width;
        changes.height = bit_image.height;
        changes.num_bytes = bit_image.num_bytes;
        changes.bytes = (uint8_t *)malloc(changes.num_bytes);

        for (int j = 1; j < iterations + 1; j++) {
            morphology_dilation(&bit_image, &changes);
            snprintf(filename, 75, "out/test/morphological_image_processing/%s-dilation-%d.png", argv[i], j);
            bit_image_write(&bit_image, filename);
            printf("-- Dilation %d written.\n", j);
        }

        bit_image_from_image(&bit_image, &image, 126, 0);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        for (int j = 1; j < iterations + 1; j++) {
            morphology_erosion(&bit_image, &changes);
            snprintf(filename, 75, "out/test/morphological_image_processing/%s-erosion-%d.png", argv[i], j);
            bit_image_write(&bit_image, filename);
            printf("-- Erosion %d written.\n", j);
        }

        bit_image_from_image(&bit_image, &image, 126, 0);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        for (int j = 1; j < iterations + 1; j++) {
            morphology_opening(&bit_image, &changes);
            snprintf(filename, 75, "out/test/morphological_image_processing/%s-opening-%d.png", argv[i], j);
            bit_image_write(&bit_image, filename);
            printf("-- Opening %d written.\n", j);
        }

        bit_image_from_image(&bit_image, &image, 126, 0);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        for (int j = 1; j < iterations + 1; j++) {
            morphology_closing(&bit_image, &changes);
            snprintf(filename, 75, "out/test/morphological_image_processing/%s-closing-%d.png", argv[i], j);
            bit_image_write(&bit_image, filename);
            printf("-- Closing %d written.\n", j);
        }

        image_free(&image);
        free(bit_image.bytes);
        free(changes.bytes);
    }
}
