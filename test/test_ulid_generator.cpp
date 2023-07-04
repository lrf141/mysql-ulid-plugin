#include "gtest/gtest.h"

#include "ulid_generator.h"

TEST(test_generate_timestamp_part, set_as_binary) {
    ULID ulid;
    // first 42 bits are all one.
    time_t timestamp = 281474976710655L;
    ulid.GenerateTimestampPart(timestamp, ulid);
    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(ulid.data[i], static_cast<uint8_t>(255));
    }
};
