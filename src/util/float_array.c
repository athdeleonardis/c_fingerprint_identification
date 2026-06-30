#include "float_array.h"

float float_array_max(float *array, int array_size) {
    float max = array[0];
    for (int i = 1; i < array_size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

void float_array_merge_sort_values(float *a, float *b) {
    if (*a <= *b) {
        return;
    }
    float t = *b;
    *b = *a;
    *a = t;
}

void float_array_merge_sort_merge(float *array_1, int length_1, float *array_2, int length_2, float *array_out) {
    int i1 = 0;
    int i2 = 0;
    int io = 0;
    while (i1 < length_1 && i2 < length_2) {
        if (array_1[i1] < array_2[i2]) {
            array_out[io] = array_1[i1];
            i1++;
        } else {
            array_out[io] = array_2[i2];
            i2++;
        }
        io++;
    }
    for (; i1 < length_1; i1++, io++) {
        array_out[io] = array_1[i1];
    }
    for (; i2 < length_2; i2++, io++) {
        array_out[io] = array_2[i2];
    }
}

void float_array_merge_sort(float *array, float *array_temp, int array_size) {
    if (array_size == 1) {
        return;
    }
    if (array_size == 2) {
        float_array_merge_sort_values(array, array + 1);
        return;
    }
    int array_size_left = array_size / 2;
    int array_size_right = array_size - array_size_left;
    float_array_merge_sort(array, array_temp, array_size_left);
    float_array_merge_sort(array + array_size_left, array_temp + array_size_left, array_size_right);
    float_array_merge_sort_merge(array, array_size_left, array + array_size_left, array_size_right, array_temp);
    for (int i = 0; i < array_size; i++) {
        array[i] = array_temp[i];
    }
}
