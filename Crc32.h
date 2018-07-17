//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRC32_H
#define CRC_WPMC_CRC32_H

#include "Crc32Base.h"

class Crc32 : public Crc32Base {
public:
    Crc32() : Crc32Base(0b11101101101110001000001100100000) {
    }

    //CRC-32 32 26 23 22 16 12 11 10 8 7 5 4 2 1 0
    uint32_t mod(uint32_t p) {
        p = p ^ (p << 31) ^ (p << 30) ^ (p << 29) ^ (p << 28)
            ^ (p << 26) ^ (p << 25) ^ (p << 24) ^ (p << 16)
            ^ (p << 12) ^ (p << 10) ^ (p << 9) ^ (p << 6);
        p = p ^ (p >> 26) ^ (p >> 23) ^ (p >> 22) ^ (p >> 16)
            ^ (p >> 12) ^ (p >> 11) ^ (p >> 10) ^ (p >> 8)
            ^ (p >> 7) ^ (p >> 5) ^ (p >> 4) ^ (p >> 2)
            ^ (p >> 1);
        return p;
    }
};


#endif //CRC_WPMC_CRC32_H
