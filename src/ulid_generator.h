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
static const char EncodeCharacters[33] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";

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

    inline void GenerateRandomnessPart(std::mt19937& mt, ULID& ulid) {
        for (int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
            addNumberAsUint8t(Rand255(mt), i, ulid);
        }
    }

    inline void addNumberAsUint8t(uint8_t n, int index, ULID& ulid) {
        ulid.data[index] = n;
    }
};

#endif //MYSQL_ULID_ULID_GENERATOR_H
