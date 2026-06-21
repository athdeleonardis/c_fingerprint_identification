#include <stdio.h>
#include "../../src/thinning/thinning_zhang_suen.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("First arg: 0 or 1 for do invert. Other args are files.\n");
        exit(0);
    }

    int do_invert;
    sscanf(argv[1], "%d", &do_invert);
    printf("Do invert: %d\n", do_invert);

    char filename[75];
    image_t image;
    bit_image_t bit_image;
    bit_image_t to_remove;
    for (int i = 2; i < argc; i++) {
        snprintf(filename, 75, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("Loaded image '%s.png'. Width: %d, Height: %d, Channels: %d.\n", argv[i], image.width, image.height, image.channels);
        
        bit_image_from_image(&bit_image, &image, 126, 1);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        to_remove.width = bit_image.width;
        to_remove.height = bit_image.height;
        to_remove.num_bytes = bit_image.num_bytes;
        to_remove.bytes = (uint8_t *)malloc(to_remove.num_bytes);
        printf("Bit-ified.\n");

        thinning_zhang_suen(&bit_image, &to_remove);
        printf("Applied Zhang-Suen thinning algorithm.\n");

        snprintf(filename, 75, "out/test/thinning_zhang_suen/%s.png", argv[i]);
        bit_image_write(&bit_image, filename);
        printf("Written.\n");

        image_free(&image);
        free(bit_image.bytes);
        free(to_remove.bytes);
    }
}