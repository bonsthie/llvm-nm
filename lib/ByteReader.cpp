#include <cassert>
#include <cstdint>
#include <cstring>
#include <llvm/ByteReader.h>

namespace llvm {

size_t ByteReader::readBitsLSB(size_t n, uint64_t &ret) {
    assert(n <= 64 && "Cannot read more than 64 bits");

    size_t avail = bitsRemaining();
    if (n > avail)
        n = avail;

    size_t byteOffset = _index;
    size_t bitOffset = _indexBits;

    uint64_t window = 0;
    size_t   bytesToRead = (n + bitOffset + 7) / 8;
    size_t   toCopy = std::min(bytesToRead, sizeof(window));

    std::memcpy(&window, _data + byteOffset, toCopy);

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    window = __builtin_bswap64(window);
#endif

    window >>= bitOffset;
    ret = window & ((uint64_t(1) << n) - 1);

    _advanceOfBits(n);
    return n;
}

size_t ByteReader::readBitsMSB(size_t n, uint64_t &ret) {
    assert(n <= 64 && "Cannot read more than 64 bits");

    size_t avail = bitsRemaining();
    if (n > avail)
        n = avail;

    size_t byteOffset = _index;
    size_t bitOffset = _indexBits;

    uint64_t window = 0;
    size_t   bytesToRead = (n + bitOffset + 7) / 8;
    size_t   toCopy = std::min(bytesToRead, sizeof(window));
    std::memcpy(&window, _data + byteOffset, toCopy);

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    window = __builtin_bswap64(window);
#endif

    size_t totalBits = toCopy * 8;

    size_t shiftLeft = (64 - totalBits) + bitOffset;
    window <<= shiftLeft;

    size_t shiftRight = 64 - n;
    ret = window >> shiftRight;

    _advanceOfBits(n);
    return n;
}

size_t ByteReader::readBits(size_t n, uint8_t &ret) {
    assert(n <= 8 && "you can't read more than 8 bits at a time");
    uint64_t tmp = 0;
    size_t   bits = readBits(n, tmp);
    ret = static_cast<uint8_t>(tmp);
    return bits;
}

size_t ByteReader::readVBR(size_t n, uint64_t &ret) {
    if (n <= 1)
        return 0;

    size_t bitsRead = 0;
    size_t shift = 0;
    bool   last = false;
	uint64_t K = n - 1;

    uint64_t result = 0;
    do {
        uint64_t chunk;
        bitsRead += readBits(n, chunk);

        last = (chunk >> K & 1) == 0;
        uint64_t payload = chunk & ((1ULL << K) - 1);
        result |= payload << shift;
        shift += K;

    } while (last == false);

    ret = result;
    return bitsRead;
}

uint8_t ByteReader::readByte() {
    // need exactly 8 bits
    if (bitsRemaining() < 8) {
        _advanceOfBits(bitsRemaining());
        return 0;
    }
    uint8_t v = 0;
    readBits(8, v);
    return v;
}

std::vector<uint8_t> ByteReader::readBytes(size_t n) {
    std::vector<uint8_t> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        if (bitsRemaining() < 8)
            break;
        out.push_back(readByte());
    }
    return out;
}

bool ByteReader::isOverflowBits(size_t n) const { return n > bitsRemaining(); }

size_t ByteReader::bitsRemaining() const { return (_size - _index) * 8 - _indexBits; }

size_t ByteReader::byteRemaining() const { return _size - _index; }

void ByteReader::_advanceOfBits(size_t n) {
    size_t bitsLeftInByte = 8 - _indexBits;
    if (n < bitsLeftInByte) {
        _indexBits += n;
        return;
    }
    n -= bitsLeftInByte;
    _index += 1 + (n / 8);
    _indexBits = n % 8;
}

} // namespace llvm
