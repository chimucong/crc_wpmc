//
// Created by test on 7/18/18.
//

#ifndef CRC_WPMC_CRC8CCITT_H
#define CRC_WPMC_CRC8CCITT_H

#include "Crc8Base.h"

class Crc8CCITT : public Crc8Base {
public:
    Crc8CCITT() : Crc8Base(0b11100000) {}

    uint8_t mod(uint8_t p) {
        p = p ^ (p << 6) ^ (p << 7);
        p = p ^ (p >> 1) ^ (p >> 2);
        return p;
    }

    uint8_t mod16(uint16_t p) {
        p = p ^ (p << 14) ^ (p << 12) ^ (p << 8) ^ (p << 7) ^ (p << 6);
        p = (p >> 8) ^ (p >> 9) ^ (p >> 10);
        return (uint8_t) p;
    }

    uint8_t mod32(uint32_t p) {
        p = p ^ (p << 31) ^ (p << 30) ^ (p << 28) ^ (p << 23) ^ (p << 21)
            ^ (p << 19) ^ (p << 18) ^ (p << 16) ^ (p << 14) ^ (p << 12)
            ^ (p << 8) ^ (p << 7) ^ (p << 6);
        p = (p >> 24) ^ (p >> 25) ^ (p >> 26);
        return p;
    }

    uint8_t crc_2(uint8_t *data, uint64_t length) {
        uint16_t *start = (uint16_t *) data;
        uint16_t *end = (uint16_t *) (data + length);
        uint16_t p = 0;
        while (start < end) {
            p ^= *start;
            p = p ^ (p << 14) ^ (p << 12) ^ (p << 8) ^ (p << 7) ^ (p << 6);
            p = (p >> 8) ^ (p >> 9) ^ (p >> 10);
            start++;
        }
        return p;
    }

    uint8_t crc_4(uint8_t *data, uint64_t length) {
        uint32_t *start = (uint32_t *) data;
        uint32_t *end = (uint32_t *) (data + length);
        uint32_t p = 0;
        while (start < end) {
            p ^= *start;
            p = p ^ (p << 31) ^ (p << 30) ^ (p << 28) ^ (p << 23) ^ (p << 21)
                ^ (p << 19) ^ (p << 18) ^ (p << 16) ^ (p << 14) ^ (p << 12)
                ^ (p << 8) ^ (p << 7) ^ (p << 6);
            p = (p >> 24) ^ (p >> 25) ^ (p >> 26);
            start++;
        }
        return p;
    }
};


#endif //CRC_WPMC_CRC8CCITT_H
