#include <stdio.h>
#include "../../src/fingerprint_minutae/fingerprint_minutae.h"
#include "../../src/thinning/thinning_zhang_suen.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("First arg, 0 or 1 for do invert. Rest are filenames to load.\n");
        exit(0);
    }

    int do_invert;
    sscanf(argv[1], "%d", &do_invert);

    image_t image;
    bit_image_t bit_image;
    bit_image_t to_remove;
    fingerprint_minutia_t *minutae;
    image_t image_minutae;
    char filename[75];
    for (int i = 2; i < argc; i++) {
        printf("%s.png\n", argv[i]);
        snprintf(filename, 75, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("-- Loaded image. Width: %d, Height: %d, Channels: %d.\n", image.width, image.height, image.channels);

        bit_image_from_image(&bit_image, &image, 126, 1);
        if (do_invert) {
            bit_image_invert(&bit_image);
        }
        printf("-- Bit-ified image.\n");

        to_remove.width = bit_image.width;
        to_remove.height = bit_image.height;
        to_remove.num_bytes = bit_image.num_bytes;
        to_remove.bytes = (uint8_t *)malloc(bit_image.num_bytes);
        thinning_zhang_suen(&bit_image, &to_remove);

        uint32_t minutia_count = fingerprint_minutae_count(&bit_image);
        printf("-- Counted minutae: %d.\n", minutia_count);
        
        minutae = (fingerprint_minutia_t *)malloc(minutia_count * sizeof(fingerprint_minutia_t));
        fingerprint_minutae_write(&bit_image, minutae);
        printf("-- Written all minutae to array.\n");

        bit_image_to_image(&bit_image, &image_minutae, 3, 1);
        image_add_minutae(&image_minutae, minutae, minutia_count);
        snprintf(filename, 75, "out/test/fingerprint_minutae/%s.png", argv[i]);
        image_write(&image_minutae, filename);
        printf("-- Written.\n");

        image_free(&image);
        free(bit_image.bytes);
        free(to_remove.bytes);
        free(minutae);
        free(image_minutae.pixels);
    }
}
