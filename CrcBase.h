//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRCBASE_H
#define CRC_WPMC_CRCBASE_H

#include <stdint-gcc.h>


template<class T>
class CrcBase {
public:
    T POLY;
    T table_8[256];
    T table_16[256];
    T table_24[256];
    T table_32[256];
    T table_40[256];
    T table_48[256];
    T table_56[256];
    T table_64[256];

    explicit CrcBase(T poly) {
        this->POLY = poly;
        init();
    }

    void init() {
        for (uint32_t i = 0; i < 256; i++) {
            T tmp = i;
            table_8[i] = shift(tmp, 8);
            table_16[i] = shift(tmp, 16);
            table_24[i] = shift(tmp, 24);
            table_32[i] = shift(tmp, 32);
            table_40[i] = shift(tmp, 40);
            table_48[i] = shift(tmp, 48);
            table_56[i] = shift(tmp, 56);
            table_64[i] = shift(tmp, 64);
        }
    }

    int type_length() {
        return sizeof(T) * 8;
    }

    T shift(T p, int count) {
        for (int i = 0; i < count; i++) {
            if (p & 0x01) {
                p = p >> 1;
                p = p ^ POLY;
            } else {
                p = p >> 1;
            }
        }
        return p;
    }

    T serial(T p) {
        int l = type_length();
        for (int i = 0; i < l; i++) {
            if (p & 0x01) {
                p = p >> 1;
                p = p ^ POLY;
            } else {
                p = p >> 1;
            }
        }
        return p;
    }

    T crc_serial(uint8_t *data, uint64_t length) {
        T *p = (T *) data;
        T *end = (T *) (data + length);
        T crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = serial(crc);
            p++;
        }
        return crc;
    }

    T crc(uint8_t *data, uint64_t length) {
        T *p = (T *) data;
        T *end = (T *) (data + length);
        T crc = 0;
        while (p < end) {
            crc ^= *p;
            crc = mod(crc);
            p++;
        }
        return crc;
    }

    virtual T crc_s1(uint8_t *data, uint64_t length) = 0;

    virtual T crc_s2(uint8_t *data, uint64_t length) = 0;

    virtual T crc_s4(uint8_t *data, uint64_t length) = 0;

    virtual T crc_s8(uint8_t *data, uint64_t length) = 0;

    virtual T mod(T p) = 0;
};


#endif //CRC_WPMC_CRCBASE_H
