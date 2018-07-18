//
// Created by test on 7/18/18.
//

#ifndef CRC_WPMC_CRC16DECT_H
#define CRC_WPMC_CRC16DECT_H

#include "Crc16Base.h"

class Crc16DECT : public Crc16Base {
public:
    Crc16DECT() : Crc16Base(0b1001000110100000) {}

    uint16_t mod(uint16_t p) {
        p = p ^ (p << 13) ^ (p << 12) ^ (p << 9) ^ (p << 8) ^ (p << 6);
        p = p ^ (p >> 10) ^ (p >> 8) ^ (p >> 7) ^ (p >> 3);
        return p;
    }
};


#endif //CRC_WPMC_CRC16DECT_H
