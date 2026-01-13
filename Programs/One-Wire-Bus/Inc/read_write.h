/**
* @file read_write.h
* @author Mihai Dicusar
* @date Jan 2026
* @brief Header file of read_write module
*/

#ifndef READ_WRITE_H
#define READ_WRITE_H

#include <stdint.h>

#define BYTE_LENGTH 8

/**
* @brief This method sends a bit to the sensor on 1-wire bus
* @param bit - bit to send (0 or 1)
* @return void
*/
void write_bit(uint8_t bit);

/**
* @brief This method sends a byte to the sensor on 1-wire bus
* @param byte - byte to send
* @return void
*/
void write_byte(uint8_t byte);

/**
* @brief This method reads a bit from the sensor on 1-wire bus
* @return bit
*/
uint8_t read_bit();

/**
* @brief This method reads a byte from the sensor on 1-wire bus
* @return byte
*/
uint8_t read_byte();

#endif