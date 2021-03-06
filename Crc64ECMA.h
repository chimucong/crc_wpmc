//
// Created by test on 7/19/18.
//

#ifndef CRC_WPMC_CRC64ECMA_H
#define CRC_WPMC_CRC64ECMA_H

#include "Crc64Base.h"
//% CRC-64-ECMA 64
// 62
// 57 55 54 53 52
// 47 46 45 40
// 39 38 37 35 33 32 31
// 29 27 24 23 22 21
// 19 17 13 12 10
// 9 7 4 1 0

//%    1 1 0 0 1 0 0 1 0 1    1 0 1 1 0 0 0 1 0 1    0 1 1 1 1 0 0 1 0 1    0 1 1 1 0 1 0 1 1 1    1 0 0 0 0 1 1 1 0 0    0 0 1 1 1 1 0 1 0 0    0 0 1 0 1
//% 0xC96C5795D7870F42
//a = [1 1 0 0 1 0 0 1 0 1    1 0 1 1 0 0 0 1 0 1    0 1 1 1 1 0 0 1 0 1    0 1 1 1 0 1 0 1 1 1    1 0 0 0 0 1 1 1 0 0    0 0 1 1 1 1 0 1 0 0    0 0 1 0 1];
//b = [repelem(0,128),1];
//[q,r] =  gfdeconv(b,a);
//q
//% 0     1(1)     0     0     1(4)     1(5)     1(6)     0     0     0
//% 0     1(11)     1(12)    1(13)     1(14)     1(15)     0     0     1(18)     0
//% 0     0     1(22)     1(23)     0     0     1(26)     1(27)    0     1(29)
//% 1(30)     0     0     0     0     0     1(36)     0     1(38)     1(39)
//% 1(40)     0     0     1(43)     0     1(45)     0     0     1(48)     0
//% 1(50)     1(51)     0     0     0     1(55)     1(56)     1(57)     1(58)     0
//% 1(60)     0     1(62)     0     1(64)
class Crc64ECMA : public Crc64Base {
public:
    Crc64ECMA() : Crc64Base(0xC96C5795D7870F42) {}

    uint64_t mod(uint64_t p) {
// 63 60 59 58
// 53 52 51 50 49 46
// 42 41 38 37 35
// 34 28 26 25
// 24 21 19 16
// 14 13 9 8 7 6
// 4 2 0
        p = p ^ (p << 63) ^ (p << 60) ^ (p << 59) ^ (p << 58)
            ^ (p << 53) ^ (p << 52) ^ (p << 51) ^ (p << 50) ^ (p << 49) ^ (p << 46)
            ^ (p << 42) ^ (p << 41) ^ (p << 38) ^ (p << 37) ^ (p << 35)
            ^ (p << 34) ^ (p << 28) ^ (p << 26) ^ (p << 25)
            ^ (p << 24) ^ (p << 21) ^ (p << 19) ^ (p << 16)
            ^ (p << 14) ^ (p << 13) ^ (p << 9) ^ (p << 8) ^ (p << 7) ^ (p << 6)
            ^ (p << 4) ^ (p << 2);
        p = p ^ (p >> 62)
            ^ (p >> 57) ^ (p >> 55) ^ (p >> 54) ^ (p >> 53) ^ (p >> 52)
            ^ (p >> 47) ^ (p >> 46) ^ (p >> 45) ^ (p >> 40)
            ^ (p >> 39) ^ (p >> 38) ^ (p >> 37) ^ (p >> 35) ^ (p >> 33) ^ (p >> 32) ^ (p >> 31)
            ^ (p >> 29) ^ (p >> 27) ^ (p >> 24) ^ (p >> 23) ^ (p >> 22) ^ (p >> 21)
            ^ (p >> 19) ^ (p >> 17) ^ (p >> 13) ^ (p >> 12) ^ (p >> 10)
            ^ (p >> 9) ^ (p >> 7) ^ (p >> 4) ^ (p >> 1);
        return p;
    }
};


#endif //CRC_WPMC_CRC64ECMA_H
