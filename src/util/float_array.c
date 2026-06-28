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