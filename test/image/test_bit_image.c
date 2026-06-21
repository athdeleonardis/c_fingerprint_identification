#include <stdio.h>
#include "../../src/image/image.h"
#include "../../src/image/bit_image.h"

void bit_image_print(bit_image_t *bi) {
    printf("Bit image. Width: %d, Height: %d\n", bi->width, bi->height);
    for (int y = 0; y < bi->height; y++) {
        for (int x = 0; x < bi->width; x++) {
            if (bit_image_pixel_from_coord(bi, x, y)) {
                printf("#");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter atleast one filename to bit-image-ify.\n");
        exit(0);
    }

    image_t image;
    bit_image_t bit_image;
    char filename[75];
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        snprintf(filename, 50, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("Loaded image '%s'. Width: %d, Height: %d, Channels: %d\n", argv[i], image.width, image.height, image.channels);

        bit_image_from_image(&bit_image, &image, 126, 1);
        printf("Bit-ified.\n");
        bit_image_print(&bit_image);

        snprintf(filename, 50, "out/test/bit_image/%s.png", argv[i]);
        bit_image_write(&bit_image, filename);
        printf("Written.\n");

        bit_image_invert(&bit_image);
        printf("Inverted.\n");
        snprintf(filename, 50, "out/test/bit_image/%s-inverted.png", argv[i]);
        bit_image_write(&bit_image, filename);
        printf("Written.\n");

        image_free(&image);
        free(bit_image.bytes);
    }
}
