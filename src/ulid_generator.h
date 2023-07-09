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
// Encoded characters size + '\0'
#define ULID_STRING_LENGTH 27

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

    inline void GenerateTimestampPart(time_t timestamp) {
        for (int i = 0, bitShift = 40; i < TIMESTAMP_PART_SIZE; i++, bitShift -= 8) {
            addDataByIndexAsUint8t(static_cast<uint8_t>(timestamp >> bitShift), i);
        }
    }

    inline void GenerateRandomnessPart(std::mt19937& mt) {
        for (int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
            addDataByIndexAsUint8t(Rand255(mt), i);
        }
    }

    inline void addDataByIndexAsUint8t(uint8_t n, int index) {
        data[index] = n;
    }

    /**
     * Encode as Crockford's Base32
     * See: https://www.crockford.com/base32.html
     * @param encodedData
     * @return
     */
    inline std::string Encode() {
        char encodedData[ULID_STRING_LENGTH];
        encodedData[ULID_STRING_LENGTH - 1] = '\0';
        EncodeTimestampPart(encodedData);
        EncodeRandomnessPart(encodedData);
        return std::string(encodedData);
    }

    inline void EncodeTimestampPart(char encodedData[ULID_STRING_LENGTH]) {
        encodedData[0] = EncodeCharacters[(data[0] & 224) >> 5];
        encodedData[1] = EncodeCharacters[(data[0] & 31)];
        encodedData[2] = EncodeCharacters[(data[1] & 248) >> 3];
        encodedData[3] = EncodeCharacters[((data[1] & 7) << 2) | ((data[2] & 192) >> 6)];
        encodedData[4] = EncodeCharacters[(data[2] & 62) >> 1];
        encodedData[5] = EncodeCharacters[((data[2] & 1) << 4) | ((data[3] & 240) >> 4)];
        encodedData[6] = EncodeCharacters[((data[3] & 15) << 1) | ((data[4] & 128) >> 7)];
        encodedData[7] = EncodeCharacters[(data[4] & 124) >> 2];
        encodedData[8] = EncodeCharacters[((data[4] & 3) << 3) | (data[5] & 224) >> 5];
        encodedData[9] = EncodeCharacters[data[5] & 31];
    }

    inline void EncodeRandomnessPart(char encodedData[ULID_STRING_LENGTH]) {
        encodedData[10] = EncodeCharacters[(data[6] & 248) >> 3];
        encodedData[11] = EncodeCharacters[((data[6] & 7) << 2) | ((data[7] & 192) >> 6)];
        encodedData[12] = EncodeCharacters[(data[7] & 62) >> 1];
        encodedData[13] = EncodeCharacters[((data[7] & 1) << 4) | ((data[8] & 240) >> 4)];
        encodedData[14] = EncodeCharacters[((data[8] & 15) << 1) | ((data[9] & 128) >> 7)];
        encodedData[15] = EncodeCharacters[(data[9] & 124) >> 2];
        encodedData[16] = EncodeCharacters[((data[9] & 3) << 3) | ((data[10] & 224) >> 5)];
        encodedData[17] = EncodeCharacters[data[10] & 31];
        encodedData[18] = EncodeCharacters[(data[11] & 248) >> 3];
        encodedData[19] = EncodeCharacters[((data[11] & 7) << 2) | ((data[12] & 192) >> 6)];
        encodedData[20] = EncodeCharacters[(data[12] & 62) >> 1];
        encodedData[21] = EncodeCharacters[((data[12] & 1) << 4) | ((data[13] & 240) >> 4)];
        encodedData[22] = EncodeCharacters[((data[13] & 15) << 1) | ((data[14] & 128) >> 7)];
        encodedData[23] = EncodeCharacters[(data[14] & 124) >> 2];
        encodedData[24] = EncodeCharacters[((data[14] & 3) << 3) | ((data[15] & 224) >> 5)];
        encodedData[25] = EncodeCharacters[data[15] & 31];
    }

    inline std::string Create(time_t timestamp) {
        std::random_device randomDevice;
        std::mt19937 mt(randomDevice());
        GenerateTimestampPart(timestamp);
        GenerateRandomnessPart(mt);
        return Encode();
    }
};

#endif //MYSQL_ULID_ULID_GENERATOR_H
