#ifndef MYSQL_ULID_ULID_GENERATOR_H
#define MYSQL_ULID_ULID_GENERATOR_H

#include <iostream>
#include <ctime>
#include <mysql_time.h>
#include <random>

// 6 byte
#define TIMESTAMP_PART_SIZE 6
// 10 byte
#define RANDOM_NUMBER_PART_SIZE 10

static std::uniform_int_distribution<uint8_t> Rand255(0, 255);

struct ULID {
    // ULID structured by 16 octet data
    uint8_t data[16];

    ULID() {
        for (unsigned char & i : data) {
            i = 0;
        }
    }

    inline void GenerateTimestampPart(time_t timestamp, ULID& ulid) {
        ulid.data[0] = static_cast<uint8_t>(timestamp >> 40);
        ulid.data[1] = static_cast<uint8_t>(timestamp >> 32);
        ulid.data[2] = static_cast<uint8_t>(timestamp >> 24);
        ulid.data[3] = static_cast<uint8_t>(timestamp >> 16);
        ulid.data[4] = static_cast<uint8_t>(timestamp >> 8);
        ulid.data[5] = static_cast<uint8_t>(timestamp);
    }

    inline void GenerateRandomNumberPart(std::mt19937& mt, ULID& ulid) {
        ulid.data[6] = Rand255(mt);
        ulid.data[7] = Rand255(mt);
        ulid.data[8] = Rand255(mt);
        ulid.data[9] = Rand255(mt);
        ulid.data[10] = Rand255(mt);
        ulid.data[11] = Rand255(mt);
        ulid.data[12] = Rand255(mt);
        ulid.data[13] = Rand255(mt);
        ulid.data[14] = Rand255(mt);
        ulid.data[15] = Rand255(mt);
    }
};

#endif //MYSQL_ULID_ULID_GENERATOR_H
