//
// Created by test on 7/18/18.
//

#ifndef CRC_WPMC_CRC8_H
#define CRC_WPMC_CRC8_H

#include "Crc8Base.h"

class Crc8 : public Crc8Base {
public:
    Crc8() : Crc8Base(0b10101011) {}

// todo check
    uint8_t mod(uint8_t p) {
        p = p ^ (p << 7) ^ (p << 6) ^ (p << 3) ^ (p << 1);
        p = p ^ (p >> 7) ^ (p >> 6) ^ (p >> 4) ^ (p >> 2);

        return p;
    }

    uint8_t crc_4(uint8_t *data, uint64_t length) {
        uint8_t *start = data;
        uint8_t *end = data + length;
        uint8_t p = 0;
        while (start < end) {
            p ^= *(start);
            p = p ^ (p << 7) ^ (p << 6) ^ (p << 3) ^ (p << 1);
            p = p ^ (p >> 7) ^ (p >> 6) ^ (p >> 4) ^ (p >> 2);

            p ^= *(start + 1);
            p = p ^ (p << 7) ^ (p << 6) ^ (p << 3) ^ (p << 1);
            p = p ^ (p >> 7) ^ (p >> 6) ^ (p >> 4) ^ (p >> 2);

            p ^= *(start + 2);
            p = p ^ (p << 7) ^ (p << 6) ^ (p << 3) ^ (p << 1);
            p = p ^ (p >> 7) ^ (p >> 6) ^ (p >> 4) ^ (p >> 2);

            p ^= *(start + 3);
            p = p ^ (p << 7) ^ (p << 6) ^ (p << 3) ^ (p << 1);
            p = p ^ (p >> 7) ^ (p >> 6) ^ (p >> 4) ^ (p >> 2);

            start += 4;
        }
        return p;
    }
};


#endif //CRC_WPMC_CRC8_H
