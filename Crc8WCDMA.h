//
// Created by test on 7/18/18.
//

#ifndef CRC_WPMC_CRC8WCDMA_H
#define CRC_WPMC_CRC8WCDMA_H

#include "Crc8Base.h"

class Crc8WCDMA : public Crc8Base {
public:
    Crc8WCDMA() : Crc8Base(0b11011001) {}

    uint8_t mod(uint8_t p) {
        p = p ^ (p << 7) ^ (p << 3) ^ (p << 2) ^ (p << 1);
        p = p ^ (p >> 7) ^ (p >> 4) ^ (p >> 3) ^ (p >> 1);
        return p;
    }
};


#endif //CRC_WPMC_CRC8WCDMA_H
