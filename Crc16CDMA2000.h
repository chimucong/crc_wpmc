//
// Created by test on 7/18/18.
//

#ifndef CRC_WPMC_CRC16CDMA2000_H
#define CRC_WPMC_CRC16CDMA2000_H

#include "Crc16Base.h"

class Crc16CDMA2000 : public Crc16Base {
public:
    Crc16CDMA2000() : Crc16Base(0xE613) {}

    uint16_t mod(uint16_t p) {
        p = p ^ (p << 13) ^ (p << 12) ^ (p << 11) ^ (p << 10) ^ (p << 9) ^ (p << 6) ^ (p << 5) ^ (p << 4) ^ (p << 3) ^
            (p << 1);
        p = p ^ (p >> 15) ^ (p >> 14) ^ (p >> 11) ^ (p >> 6) ^ (p >> 5) ^ (p >> 2) ^ (p >> 1);
        return p;
    }
};


#endif //CRC_WPMC_CRC16CDMA2000_H
