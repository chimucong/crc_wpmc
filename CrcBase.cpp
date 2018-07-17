//
// Created by test on 7/17/18.
//

#include "CrcBase.h"

uint8_t *generate_data(size_t length) {
    uint8_t *data;
    data = (uint8_t *) aligned_alloc(16, sizeof(uint8_t) * length);
    uint8_t seed = 1;
    for (size_t i = 0; i < length; i++) {
        data[i] = seed;
        seed = seed * 37;
    }
    return data;
}
