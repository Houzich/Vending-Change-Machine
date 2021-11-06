
#ifndef MODBUS_CRC_H
#define MODBUS_CRC_H
#ifdef __cplusplus
 extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
uint16_t  Modbus_CRC16( uint8_t * pucFrame, uint16_t usLen );
#ifdef __cplusplus
}
#endif
#endif //MODBUS_CRC_H
