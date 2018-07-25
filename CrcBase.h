//
// Created by test on 7/17/18.
//

#ifndef CRC_WPMC_CRCBASE_H
#define CRC_WPMC_CRCBASE_H

#include <iostream>
#include<chrono>

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
        uint8_t *data = generate_data(length);
        {
            auto b1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < rep; i++)
                crc1 = crc_s1(data, length);
            auto e1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d1 = e1 - b1;
            cout << "s1\t\t" << d1.count() << '\t' << double(length) * rep / d1.count() / 1024 / 1024 << endl;
        }
        {
            auto b1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < rep; i++)
                crc1 = crc_s1(data, length);
            auto e1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d1 = e1 - b1;
            cout << "s1\t\t" << d1.count() << '\t' << double(length) * rep / d1.count() / 1024 / 1024 << endl;
        }
        {
            auto b2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < rep; i++)
                crc2 = crc_s2(data, length);
            auto e2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d2 = e2 - b2;
            cout << "s2\t\t" << d2.count() << '\t' << double(length) * rep / d2.count() / 1024 / 1024 << endl;
        }
        {
            auto b2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < rep; i++)
                crc2 = crc_s2(data, length);
            auto e2 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> d2 = e2 - b2;
            cout << "s2\t\t" << d2.count() << '\t' << double(length) * rep / d2.count() / 1024 / 1024 << endl;
        }

        auto b3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < rep; i++)
            crc3 = crc_s4(data, length);
        auto e3 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d3 = e3 - b3;

        auto b4 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < rep; i++)
            crc4 = crc_s8(data, length);
        auto e4 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d4 = e4 - b4;

        auto b5 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < rep; i++)
            crc5 = crc(data, length);
        auto e5 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d5 = e5 - b5;

        auto b6 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < rep; i++)
            crc6 = crc_serial(data, length);
        auto e6 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> d6 = e6 - b6;


        cout << "s4\t\t" << d3.count() << '\t' << double(length) * rep / d3.count() / 1024 / 1024 << endl;
        cout << "s8\t\t" << d4.count() << '\t' << double(length) * rep / d4.count() / 1024 / 1024 << endl;
        cout << "crc\t\t" << d5.count() << '\t' << double(length) * rep / d5.count() / 1024 / 1024 << endl;
        cout << "serial\t" << d6.count() << '\t' << double(length) * rep / d6.count() / 1024 / 1024 << endl;

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
