#include <math.h>
#include "float_array.h"

float _float_array_get(float *array, int array_width, int array_height, int x, int y) {
    if (x < 0 || y < 0 || x >= array_width || y >= array_height) {
        return 0;
    }
    return array[x + y * array_width];
}

float float_array_max(float *array, int array_size) {
    float max = array[0];
    for (int i = 1; i < array_size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

float float_array_sum(float *array, int array_size) {
    float sum = 0;
    for (int i = 0; i < array_size; i++) {
        sum += array[i];
    }
    return sum;
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

void float_array_gaussian(float *array, float stddev, int n) {
    int width = 2 * n + 1;
    stddev = 2 * stddev * stddev;
    int i = 0;
    for (int y = 0; y < width; y++) {
        for (int x = y; x < width; x++, i++) {
            int dx = x - n;
            int dy = y - n;
            array[i] = expf(-(dx * dx + dy * dy) / stddev);
        }
    }

    // Normalize the array
    int area = width * width;
    float sum = float_array_sum(array, area);
    for (i = 0; i < area; i++) {
        array[i] = array[i] / sum;
    }
}

// The window should be (2n+1)x(2n+1)
void float_array_convolution(float *array_in, float *array_out, int array_width, int array_height, float *array_window, int n) {
    int window_width = 2 * n + 1;
    for (int y = 0; y < array_height; y++) {
        for (int x = 0; x < array_width; x++) {
            float array_out_value = 0;
            for (int dy = 0; dy < window_width; dy++) {
                for (int dx = 0; dx < window_width; dx++) {
                    float array_in_value = _float_array_get(array_in, array_width, array_height, x + dx - n, y + dy - n);
                    float window_value = array_window[dx + dy * window_width];
                    array_out_value += array_in_value * window_value;
                }
            }
            array_out[x + y * array_width] = array_out_value;
        }
    }
}
