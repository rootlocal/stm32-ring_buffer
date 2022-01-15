#include "inc/buffer_crc.h"

uint32_t CalcCRC32_MPEG2(uint8_t *data, uint32_t DataLength) {
    uint32_t Checksum = 0xFFFFFFFF;

    for (uint32_t i = 0; i < DataLength; i++) {
        uint8_t top = (uint8_t) (Checksum >> 24);
        top ^= data[i];
        Checksum = (Checksum << 8) ^ crc_table[top];
    }

    return Checksum;
}

uint32_t CalcCRC32(uint8_t *pData, size_t count, uint32_t init) {
    uint32_t crc;
    uint32_t *p32 = (uint32_t *) pData;
    size_t count32 = count >> 2;

    if (0xFFFFFFFF == init) {
        CRC->CR |= CRC_CR_RESET;
    }

    while (count32--) {
        CRC->DR = __RBIT(*p32++);
    }

    crc = __RBIT(CRC->DR);
    count = count % 4;
    if (count) {
        CRC->DR = __RBIT(crc);

        switch (count) {
            case 1:
                CRC->DR = __RBIT((*p32 & 0x000000FF) ^ crc) >> 24;
                crc = (crc >> 8) ^ __RBIT(CRC->DR);
                break;
            case 2:
                CRC->DR = (__RBIT((*p32 & 0x0000FFFF) ^ crc) >> 16);
                crc = (crc >> 16) ^ __RBIT(CRC->DR);
                break;
            case 3:
                CRC->DR = __RBIT((*p32 & 0x00FFFFFF) ^ crc) >> 8;
                crc = (crc >> 24) ^ __RBIT(CRC->DR);
                break;
            default:
                break;
        }
    }
    return ~crc;
}
