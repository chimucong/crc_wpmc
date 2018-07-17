#include <iostream>
#include "Crc16CCITT.h"
#include "Crc32.h"
#include "Crc64ISO.h"

using namespace std;

uint8_t *generate_data(size_t length) {
    uint8_t *data;
    data = (uint8_t *) malloc(sizeof(uint8_t) * length);
    uint8_t seed = 1;
    for (size_t i = 0; i < length; i++) {
        data[i] = seed;
        seed = seed * 37;
    }
    return data;
}

int main() {
    Crc64ISO crc;
    uint64_t length = 1024 * 1024;
    uint8_t *data = generate_data(length);
    cout << (unsigned long) crc.crc_s1(data, length) << endl;
    cout << (unsigned long) crc.crc_s2(data, length) << endl;
    cout << (unsigned long) crc.crc_s4(data, length) << endl;
    cout << (unsigned long) crc.crc_s8(data, length) << endl;
    cout << (unsigned long) crc.crc_serial(data, length) << endl;
    cout << (unsigned long) crc.crc(data, length) << endl;
    return 0;
}