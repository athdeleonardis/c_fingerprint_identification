#include "fingerprint_feature.h"

fingerprint_feature_t *fingerprint_feature_type(uint8_t **buffer, uint8_t type, uint32_t x, uint32_t y) {
    fingerprint_feature_t *feature = (fingerprint_feature_t *)*buffer;
    *buffer += sizeof(fingerprint_feature_t);
    feature->type = type;
    feature->x = x;
    feature->y = y;
}

void fingerprint_feature_a(uint8_t **buffer, uint32_t x, uint32_t y) {
    fingerprint_feature_type(buffer, FINGERPRINT_FEATURE_A, x, y);
}

void fingerprint_feature_b(uint8_t **buffer, uint32_t x, uint32_t y) {
    fingerprint_feature_type(buffer, FINGERPRINT_FEATURE_B, x, y);
}
