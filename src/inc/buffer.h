#pragma once
#ifndef BUFFER_H
#define BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct {
    uint8_t *buffer;
    uint16_t idxIn;
    uint16_t idxOut;
    uint16_t size;
} buffer_t;

typedef enum {
    BUFFER_STATUS_ERROR = 0,
    BUFFER_STATUS_SUCCESS = 1
} BufferErrorStatus_t;


void BufferPut(uint8_t symbol, buffer_t *buf);

char BufferPop(buffer_t *buf);

uint16_t BufferGetCount(buffer_t *buf);

char BufferShowSymbol(uint16_t symbolNumber, buffer_t *buf);

void BufferClear(buffer_t *buf);

BufferErrorStatus_t BufferInit(buffer_t *ring, uint8_t *buf, uint16_t size);

uint16_t BufferCRC16ccitt(buffer_t *buf, uint16_t length, uint16_t position);

#ifdef __cplusplus
}
#endif
#endif // BUFFER_H