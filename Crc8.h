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
};


#endif //CRC_WPMC_CRC8_H
