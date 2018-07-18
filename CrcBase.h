//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRCBASE_H
#define CRC_WPMC_CRCBASE_H

#include <time.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

uint8_t *generate_data(size_t length);

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

    void perf(uint64_t length, int rep) {
        T crc1, crc2, crc3, crc4, crc5, crc6;
        clock_t b1, e1, b2, e2, b3, e3, b4, e4, b5, e5, b6, e6;
        uint8_t *data = generate_data(length);

        b1 = clock();
        for (int i = 0; i < rep; i++)
            crc1 = crc_s1(data, length);
        e1 = clock();

        b2 = clock();
        for (int i = 0; i < rep; i++)
            crc2 = crc_s2(data, length);
        e2 = clock();

        b3 = clock();
        for (int i = 0; i < rep; i++)
            crc3 = crc_s4(data, length);
        e3 = clock();

        b4 = clock();
        for (int i = 0; i < rep; i++)
            crc4 = crc_s8(data, length);
        e4 = clock();

        b5 = clock();
        for (int i = 0; i < rep; i++)
            crc5 = crc(data, length);
        e5 = clock();

        b6 = clock();
        for (int i = 0; i < rep; i++)
            crc6 = crc_serial(data, length);
        e6 = clock();

        cout << "s1\t\t" << e1 - b1 << '\t' << double(length) * rep / (e1 - b1) * CLOCKS_PER_SEC / 1024 / 1024 << endl;
        cout << "s2\t\t" << e2 - b2 << '\t' << double(length) * rep / (e2 - b2) * CLOCKS_PER_SEC / 1024 / 1024 << endl;
        cout << "s4\t\t" << e3 - b3 << '\t' << double(length) * rep / (e3 - b3) * CLOCKS_PER_SEC / 1024 / 1024 << endl;
        cout << "s8\t\t" << e4 - b4 << '\t' << double(length) * rep / (e4 - b4) * CLOCKS_PER_SEC / 1024 / 1024 << endl;
        cout << "crc\t\t" << e5 - b5 << '\t' << double(length) * rep / (e5 - b5) * CLOCKS_PER_SEC / 1024 / 1024 << endl;
        cout << "serial\t" << e6 - b6 << '\t' << double(length) * rep / (e6 - b6) * CLOCKS_PER_SEC / 1024 / 1024
             << endl;

        cout << (unsigned long) crc1 << endl;
        cout << (unsigned long) crc2 << endl;
        cout << (unsigned long) crc3 << endl;
        cout << (unsigned long) crc4 << endl;
        cout << (unsigned long) crc5 << endl;
        cout << (unsigned long) crc6 << endl;

        free(data);
    }
};


#endif //CRC_WPMC_CRCBASE_H
