#include "llvm/ByteReader.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

using namespace nm;

// ——— Basic (non‑fixture) tests ———
TEST(ByteReaderBasicTest, ReadByteCorrectly) {
    uint8_t    data[] = {0x12, 0x34, 0x56};
    ByteReader reader(data, sizeof(data));

    EXPECT_EQ(reader.readByte(), 0x12);
    EXPECT_EQ(reader.readByte(), 0x34);
    EXPECT_EQ(reader.readByte(), 0x56);
    EXPECT_EQ(reader.byteRemaining(), 0);
}

TEST(ByteReaderBasicTest, BitsRemainingTracksCorrectly) {
    uint8_t    data[] = {0xFF, 0x00};
    ByteReader reader(data, sizeof(data));

    EXPECT_EQ(reader.bitsRemaining(), 16);
    uint64_t tmp;
    reader.readBitsLSB(7, tmp);
    EXPECT_EQ(reader.bitsRemaining(), 9);
    reader.readBitsLSB(9, tmp);
    EXPECT_EQ(reader.bitsRemaining(), 0);
}

TEST(ByteReaderBasicTest, ReadBytesWorks) {
    uint8_t    data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    ByteReader reader(data, sizeof(data));

    auto bytes = reader.readBytes(2);
    ASSERT_EQ(bytes.size(), 2);
    EXPECT_EQ(bytes[0], 0xDE);
    EXPECT_EQ(bytes[1], 0xAD);

    bytes = reader.readBytes(2);
    ASSERT_EQ(bytes.size(), 2);
    EXPECT_EQ(bytes[0], 0xBE);
    EXPECT_EQ(bytes[1], 0xEF);
}

TEST(ByteReaderBasicTest, IsOverflowBitsCorrect) {
    uint8_t    data[] = {0x00};
    ByteReader reader(data, 1);

    EXPECT_FALSE(reader.isOverflowBits(8));
    uint64_t tmp;
    reader.readBitsLSB(8, tmp);
    EXPECT_TRUE(reader.isOverflowBits(1));
    EXPECT_EQ(reader.bitsRemaining(), 0);
}


class ByteReaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        data_ = { 0b11110000, 0b10101100, 0b11110000 };
    }

    std::vector<uint8_t> data_;
};

TEST_F(ByteReaderTest, ReadBitsLSB_NibbleByNibble) {
    ByteReader reader(data_.data(), data_.size());
    uint64_t result = 0;

    // First nibble LSB-first → 0b0000
    EXPECT_EQ(reader.readBitsLSB(4, result), 4u);
    EXPECT_EQ(result, 0b0000ULL);

    // Second nibble → 0b1111
    EXPECT_EQ(reader.readBitsLSB(4, result), 4u);
    EXPECT_EQ(result, 0b1111ULL);
}

TEST_F(ByteReaderTest, ReadBitsMSB_NibbleByNibble) {
    ByteReader reader(data_.data(), data_.size());
    uint64_t result = 0;

    // First nibble MSB-first → 0b1111
    EXPECT_EQ(reader.readBitsMSB(4, result), 4u);
    EXPECT_EQ(result, 0b1111ULL);

    // Second nibble → 0b0000
    EXPECT_EQ(reader.readBitsMSB(4, result), 4u);
    EXPECT_EQ(result, 0b0000ULL);
}

TEST_F(ByteReaderTest, ReadBitsLSB_ACrossByteBoundary) {
    ByteReader reader(data_.data(), data_.size());
    uint64_t result = 0;

    // Read 12 bits LSB-first: low 8 bits of byte0 then low 4 of byte1
    EXPECT_EQ(reader.readBitsLSB(12, result), 12u);
	EXPECT_EQ(result, 0xCF0ULL);
}

TEST_F(ByteReaderTest, ReadBitsMSB_ACrossByteBoundary) {
    ByteReader reader(data_.data(), data_.size());
    uint64_t result = 0;

    // Read 12 bits MSB-first: high 8 bits of byte0 then high 4 of byte1
    EXPECT_EQ(reader.readBitsMSB(12, result), 12u);
	EXPECT_EQ(result, 0xACFULL);
}
