//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRC16BASE_H
#define CRC_WPMC_CRC16BASE_H

#include "CrcBase.h"

class Crc16Base : public CrcBase<uint16_t> {
public:
    Crc16Base(uint16_t poly) : CrcBase(poly) {}

    uint16_t crc_s1(uint8_t *data, uint64_t length) {
        uint8_t *p = (uint8_t *) data;
        uint8_t *end = (uint8_t *) (data + length);
        uint16_t crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = (crc >> 8) ^ table_8[crc & 0xff];
            p++;
        }
        return crc;
    }

    uint16_t crc_s2(uint8_t *data, uint64_t length) {
        uint16_t *p = (uint16_t *) data;
        uint16_t *end = (uint16_t *) (data + length);
        uint16_t crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = table_16[crc & 0xff] ^ table_8[(crc >> 8) & 0xff];
            p++;
        }
        return (uint16_t) crc;
    }

    uint16_t crc_s4(uint8_t *data, uint64_t length) {
        uint32_t *p = (uint32_t *) data;
        uint32_t *end = (uint32_t *) (data + length);
        uint32_t crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = table_32[crc & 0xff] ^ table_24[(crc >> 8) & 0xff]
                  ^ table_16[(crc >> 16) & 0xff] ^ table_8[(crc >> 24) & 0xff];
            p++;
        }
        return (uint16_t) crc;
    }

    uint16_t crc_s8(uint8_t *data, uint64_t length) {
        uint64_t *p = (uint64_t *) data;
        uint64_t *end = (uint64_t *) (data + length);
        uint64_t crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = table_64[crc & 0xff] ^ table_56[(crc >> 8) & 0xff]
                  ^ table_48[(crc >> 16) & 0xff] ^ table_40[(crc >> 24) & 0xff]
                  ^ table_32[(crc >> 32) & 0xff] ^ table_24[(crc >> 40) & 0xff]
                  ^ table_16[(crc >> 48) & 0xff] ^ table_8[(crc >> 56) & 0xff];
            p++;
        }
        return (uint16_t) crc;
    }
};


#endif //CRC_WPMC_CRC16BASE_H
