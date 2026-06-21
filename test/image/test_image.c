#include <stdio.h>
#include <string.h>
#include "../../src/image/image.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Enter atleast one file to copy.");
        exit(0);
    }

    image_t image;
    char filename[50];
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        snprintf(filename, 50, "in/%s.png", argv[i]);
        image_load(&image, filename);
        printf("Loaded image. Width: %d, Height: %d, Channels: %d", image.width, image.height, image.channels);
        snprintf(filename, 50, "out/test/image/%s.png", argv[i]);
        image_write(&image, filename);
        image_free(&image);
    }
}