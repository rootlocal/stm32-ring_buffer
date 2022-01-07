#include "buffer.h"

void BufferPut(char symbol, buffer_t *buf) {
    buf->buffer[buf->idxIn++] = symbol;

    if (buf->idxIn >= buf->size) {
        buf->idxIn = 0;
    }
}

char BufferPop(buffer_t *buf) {
    uint8_t retVal = buf->buffer[buf->idxOut++];

    if (buf->idxOut >= buf->size) {
        buf->idxOut = 0;
    }

    return retVal;
}

uint16_t BufferGetCount(buffer_t *buf) {
    uint16_t retVal = 0;

    if (buf->idxIn < buf->idxOut) {
        retVal = buf->size + buf->idxIn - buf->idxOut;
    } else {
        retVal = buf->idxIn - buf->idxOut;
    }

    return retVal;
}

char BufferShowSymbol(uint16_t symbolNumber, buffer_t *buf) {
    uint32_t pointer = buf->idxOut + symbolNumber;
    int32_t retVal = -1;

    if (symbolNumber < BufferGetCount(buf)) {

        if (pointer > buf->size) {
            pointer -= buf->size;
        }

        retVal = buf->buffer[pointer];
    }

    return retVal;
}

void BufferClear(buffer_t *buf) {
    buf->idxIn = 0;
    buf->idxOut = 0;
}

BufferErrorStatus_t BufferInit(buffer_t *ring, char *buf, uint16_t size) {
    ring->size = size;
    ring->buffer = buf;
    BufferClear(ring);

    return (ring->buffer ? BUFFER_STATUS_SUCCESS : BUFFER_STATUS_ERROR);
}

uint16_t BufferCRC16ccittIntermediate(buffer_t *buf, uint16_t length, uint16_t tmpCrc, uint16_t position) {
    uint16_t crc = tmpCrc;
    uint16_t crcTab;
    uint8_t byte;

    while (length--) {
        crcTab = 0x0000;
        byte = (BufferShowSymbol(length + position, buf)) ^ (crc >> 8);
        if (byte & 0x01) crcTab ^= 0x1021;
        if (byte & 0x02) crcTab ^= 0x2042;
        if (byte & 0x04) crcTab ^= 0x4084;
        if (byte & 0x08) crcTab ^= 0x8108;
        if (byte & 0x10) crcTab ^= 0x1231;
        if (byte & 0x20) crcTab ^= 0x2462;
        if (byte & 0x40) crcTab ^= 0x48C4;
        if (byte & 0x80) crcTab ^= 0x9188;

        crc = (((crc & 0xFF) ^ (crcTab >> 8)) << 8) | (crcTab & 0xFF);
    }

    return crc;
}

uint16_t BufferCRC16ccitt(buffer_t *buf, uint16_t length, uint16_t position) {
    return BufferCRC16ccittIntermediate(buf, length, 0xFFFF, position);
}