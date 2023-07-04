#ifndef MYSQL_ULID_ULID_GENERATOR_H
#define MYSQL_ULID_ULID_GENERATOR_H
#include <iostream>
#include <ctime>
#include <mysql_time.h>

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
};

#endif //MYSQL_ULID_ULID_GENERATOR_H
