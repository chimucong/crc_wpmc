//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRC64ISO_H
#define CRC_WPMC_CRC64ISO_H

#include "Crc64Base.h"

class Crc64ISO : public Crc64Base {
public:
    Crc64ISO() : Crc64Base(0xD800000000000000) {}

    //CRC-4-ISO 64 4 3 1 0
    uint64_t mod(uint64_t p) {
        p = p ^ (p << 60) ^ (p << 61) ^ (p << 63);
        p = p ^ (p >> 4) ^ (p >> 3) ^ (p >> 1);
        return p;
    }

};


#endif //CRC_WPMC_CRC64ISO_H
