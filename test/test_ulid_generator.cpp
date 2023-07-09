#include "gtest/gtest.h"

#include "ulid_generator.h"

TEST(test_generate_timestamp_part, set_as_binary) {
    ULID ulid;
    // first 42 bits are all one.
    time_t timestamp = 281474976710655L;
    ulid.GenerateTimestampPart(timestamp, ulid);
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
    ulid.GenerateRandomNumberPart(mt, ulid);
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
    ulid.GenerateTimestampPart(timestamp, ulid);
    for(int i = TIMESTAMP_PART_SIZE; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ulid.addNumberAsUint8t(static_cast<uint8_t>(255), i, ulid);
    }
    int i;
    for (i = 0; i < TIMESTAMP_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
    for (; i < RANDOM_NUMBER_PART_SIZE; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
}
