//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRC16CCITT_H
#define CRC_WPMC_CRC16CCITT_H

#include "Crc16Base.h"

class Crc16CCITT : public Crc16Base {
public:
    Crc16CCITT() : Crc16Base(0b1000010000001000) {}

    uint16_t mod(uint16_t p) {
        p = p ^ (p << 4) ^ (p << 8) ^ (p << 11) ^ (p << 12);
        p = p ^ (p >> 5) ^ (p >> 12);
        return p;
    }

};


#endif //CRC_WPMC_CRC16CCITT_H
