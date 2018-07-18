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
};


#endif //CRC_WPMC_CRC8CCITT_H
