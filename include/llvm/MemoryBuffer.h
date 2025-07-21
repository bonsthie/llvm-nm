#ifndef MEMORYBUFFER_H
#define MEMORYBUFFER_H

#include <cstdint>
#include <fcntl.h>
#include <stdexcept>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace llvm {

class MemoryBuffer {
    void  *_data = nullptr;
    size_t _size = 0;
    int    _fd = -1;

  public:
    explicit MemoryBuffer(char const *path) {
        _fd = ::open(path, O_RDONLY);
        if (_fd < 0)
            throw std::runtime_error("open failed");

        struct stat st;
        if (fstat(_fd, &st) < 0) {
            ::close(_fd);
            throw std::runtime_error("stat failed");
        }
        _size = st.st_size;

        _data = mmap(nullptr, _size, PROT_READ, MAP_PRIVATE, _fd, 0);
        if (_data == MAP_FAILED) {
            ::close(_fd);
            throw std::runtime_error("mmap failed");
        }
    }

    ~MemoryBuffer() {
        if (_data && _data != MAP_FAILED)
            munmap(_data, _size);
        if (_fd >= 0)
            close(_fd);
    }

    MemoryBuffer(MemoryBuffer const &) = delete;
    MemoryBuffer &operator=(MemoryBuffer const &) = delete;

    MemoryBuffer(MemoryBuffer &&o) noexcept : _data(o._data), _size(o._size), _fd(o._fd) {
        o._data = nullptr;
        o._fd = -1;
        o._size = 0;
    }

    MemoryBuffer &operator=(MemoryBuffer &&o) noexcept {
        if (this != &o) {
            this->~MemoryBuffer();
            new (this) MemoryBuffer(std::move(o));
        }
        return *this;
    }

    size_t size() const { return _size; }

    std::string_view view() const { return {static_cast<char const *>(_data), _size}; }

    void *raw() const { return _data; }

    operator std::string_view() const { return view(); }
};

} // namespace llvm

#endif // MEMORYBUFFER_H
