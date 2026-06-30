#include <stdio.h>
#include <stdlib.h>
#include "../../src/util/float_array.h"

void print_items(float *items, int n) {
    for (int i = 0; i < n; i++) {
        printf("%f ", items[i]);
    }
}

int main(int argc, char *argv[]) {
    int n;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Number of items: %d\n", n);
    float *items = (float *)malloc(2 * n * sizeof(float));
    float *items_temp = items + n;

    printf("Enter items: ");
    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i);
        scanf("%f", items + i);
        printf("Entered: %f\n", items[i]);
    }
    printf("Items entered: ");
    print_items(items, n);
    printf("\n");

    float_array_merge_sort(items, items_temp, n);
    printf("Items sorted: ");
    print_items(items, n);
    printf("\n");

    free(items);
}