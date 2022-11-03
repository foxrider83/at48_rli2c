/* 
 * File:   rli2c.h
 * Author: Infoxelec
 *
 * Created on 6 octobre 2022, 14:31
 */
#include <avr/io.h>
#include "./I2CSlave.h"

#ifndef RLI2C_H
#define	RLI2C_H

void I2C_received(uint8_t received_data);
void I2C_requested();
void go();

#endif	/* RLI2C_H */

