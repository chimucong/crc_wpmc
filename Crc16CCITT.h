//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRC16CCITT_H
#define CRC_WPMC_CRC16CCITT_H

#include "Crc16Base.h"

class Crc16CCITT:public Crc16Base {
public:
    Crc16CCITT() : Crc16Base(0b1000010000001000) {}

    uint16_t mod(uint16_t p) {
        uint16_t a, b, c, d;
        a = p << 4;
        b = p << 8;
        c = p << 11;
        d = p << 12;
        p = p ^ a ^ b ^ c ^ d;
        a = p >> 5;
        b = p >> 12;
        p = a ^ b ^ p;
        return p;
    }

};


#endif //CRC_WPMC_CRC16CCITT_H
