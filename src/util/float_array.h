#ifndef HEADER_FLOAT_ARRAY
#define HEADER_FLOAT_ARRAY

float float_array_max(float *array, int array_size);
float float_array_sum(float *array, int array_size);
void float_array_merge_sort(float *array, float *array_temp, int array_size);
void float_array_gaussian(float *array, float stddev, int n);
void float_array_convolution(float *array_in, float *array_out, int array_width, int array_height, float *array_window, int n);

#endif