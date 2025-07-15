#include "llvm/ByteReader.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

using namespace nm;

TEST(ByteReaderTest, ReadByteCorrectly) {
    uint8_t data[] = {0x12, 0x34, 0x56};
    ByteReader reader(data, sizeof(data));

    EXPECT_EQ(reader.readByte(), 0x12);
    EXPECT_EQ(reader.readByte(), 0x34);
    EXPECT_EQ(reader.readByte(), 0x56);
    EXPECT_EQ(reader.byteRemaining(), 0);
}

TEST(ByteReaderTest, ReadBitsWorks) {
    uint8_t data[] = {0b10101010, 0b10101100, 0b11110000};
    ByteReader reader(data, sizeof(data));

    uint64_t result = 0;
	size_t bitsRead = reader.readBits(1, result);
    EXPECT_EQ(bitsRead, 1);
    EXPECT_EQ(result, 1);
	
	bitsRead = reader.readBits(1, result);
    EXPECT_EQ(bitsRead, 1);
    EXPECT_EQ(result, 0);

	bitsRead = reader.readBits(1, result);
    EXPECT_EQ(bitsRead, 1);
    EXPECT_EQ(result, 1);
	bitsRead = reader.readBits(5, result);


    bitsRead = reader.readBits(4, result);
    EXPECT_EQ(bitsRead, 4);
    EXPECT_EQ(result, 0b1010);

    bitsRead = reader.readBits(4, result);
    EXPECT_EQ(bitsRead, 4);
    EXPECT_EQ(result, 0b1100);

    bitsRead = reader.readBits(8, result);
    EXPECT_EQ(bitsRead, 8);
    EXPECT_EQ(result, 0b11110000);
}

TEST(ByteReaderTest, BitsRemainingTracksCorrectly) {
    uint8_t data[] = {0xFF, 0x00};
    ByteReader reader(data, sizeof(data));

    EXPECT_EQ(reader.bitsRemaining(), 16);
    uint64_t tmp;
    reader.readBits(7, tmp);
    EXPECT_EQ(reader.bitsRemaining(), 9);
    reader.readBits(9, tmp);
    EXPECT_EQ(reader.bitsRemaining(), 0);
}

TEST(ByteReaderTest, ReadBytesWorks) {
    uint8_t data[] = {0xDE, 0xAD, 0xBE, 0xEF};
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

TEST(ByteReaderTest, IsOverflowBitsCorrect) {
    uint8_t data[] = {0x00};
    ByteReader reader(data, 1);

    EXPECT_FALSE(reader.isOverflowBits(8));
    uint64_t tmp;
    reader.readBits(8, tmp);
    EXPECT_TRUE(reader.isOverflowBits(1));
    EXPECT_EQ(reader.bitsRemaining(), 0);
}

