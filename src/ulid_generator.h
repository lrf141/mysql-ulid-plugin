#ifndef MYSQL_ULID_ULID_GENERATOR_H
#define MYSQL_ULID_ULID_GENERATOR_H
#include <iostream>

struct ULID {
    uint8_t data[16];
    ULID() {
        for (unsigned char & i : data) {
            i = 0;
        }
    }
};

#endif //MYSQL_ULID_ULID_GENERATOR_H
