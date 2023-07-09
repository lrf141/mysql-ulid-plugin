#include "gtest/gtest.h"
#include <chrono>
#include <algorithm>

#include "ulid_generator.h"

TEST(test_generate_timestamp_part, set_as_binary) {
    ULID ulid;
    // first 42 bits are all one.
    time_t timestamp = 281474976710655L;
    ulid.GenerateTimestampPart(timestamp);
    int i;
    for (i = 0; i < TIMESTAMP_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
    for (; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(0));
    }
};

TEST(test_generate_random_number_part, set_as_binary) {
    ULID ulid;
    std::random_device rnd;
    std::mt19937 mt(rnd());
    ulid.GenerateRandomnessPart(mt);
    int i;
    for (i = 0; i < TIMESTAMP_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(0));
    }
    for (; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ASSERT_GE(ulid.data[i], static_cast<uint8_t>(0));
        ASSERT_LE(ulid.data[i], static_cast<uint8_t>(255));
    }
}

TEST(test_add_number_as_uint8t, set_as_uint8t) {
    ULID ulid;
    time_t timestamp = 281474976710655L;
    ulid.GenerateTimestampPart(timestamp);
    for(int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ulid.addDataByIndexAsUint8t(static_cast<uint8_t>(255), i);
    }
    int i;
    for (i = 0; i < TIMESTAMP_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
    for (; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
}

TEST(test_encode, encode_as_crockfords_base32) {
    ULID ulid;
    time_t time = 1688894191930L;
    ulid.GenerateTimestampPart(time);
    for(int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ulid.addDataByIndexAsUint8t(static_cast<uint8_t>(255), i);
    }
    std::string ulidString = ulid.Encode();
    ASSERT_EQ(ulidString, "01H4WZ0E9TZZZZZZR000000000");
    ASSERT_EQ(ulidString.length(), ULID_STRING_LENGTH - 1);
}

TEST(test_encode, correspond_timestamp_and_lex_order) {
    ULID ulid;
    time_t time = 1688894191930L;
    ulid.GenerateTimestampPart(time);
    for(int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ulid.addDataByIndexAsUint8t(static_cast<uint8_t>(255), i);
    }
    std::string ulidString1 = ulid.Encode();

    ulid.GenerateTimestampPart(time + 1);
    std::string ulidString2 = ulid.Encode();

    int diffCount = ulidString1.compare(ulidString2);
    ASSERT_LT(diffCount, 0);
}

TEST(test_encode, encode_characters) {
    ULID ulid;
    time_t time = 1688894191930L;
    ulid.GenerateTimestampPart(time);
    for(int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ulid.addDataByIndexAsUint8t(static_cast<uint8_t>(255), i);
    }
    std::string ulidString = ulid.Encode();

    for (int i = 0; i < ULID_STRING_LENGTH; i++) {
        char c = ulidString[i];
        int res = std::count(std::begin(EncodeCharacters),
                             std::end(EncodeCharacters),
                             c
                             );
        ASSERT_EQ(res, 1);
    }
}