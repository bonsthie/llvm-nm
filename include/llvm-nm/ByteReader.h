#ifndef BYTEREADER_H
#define BYTEREADER_H

#include <cstdint>
class BitsReader {
	uint8_t *_data;

public:
	BitsReader(void *data) : _data((uint8_t *)data) {}



};

#endif // BYTEREADER_H

