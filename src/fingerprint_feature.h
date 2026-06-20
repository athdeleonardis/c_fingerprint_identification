#ifndef FINGERPRINT_FEATURE
#define FINGERPRINT_FEATURE

#include <stdint.h>

#define FINGERPRINT_FEATURE_A (uint8_t)0x01
#define FINGERPRINT_FEATURE_B (uint8_t)0x02

typedef struct fingerprint_feature_a {
    int temp;
} fingerprint_feature_a_t;

typedef struct fingerprint_feature_b {
    int temp;
} fingerprint_feature_b_t;

typedef struct fingerprint_feature {
    uint8_t type;
    uint32_t x;
    uint32_t y;
    union {
        fingerprint_feature_a_t a;
        fingerprint_feature_b_t b;
    };
} fingerprint_feature_t;

void fingerprint_feature_a(uint8_t **buffer, uint32_t x, uint32_t y);
void fingerprint_feature_b(uint8_t **buffer, uint32_t x, uint32_t y);

#endif