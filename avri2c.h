/* 
 * File:   avri2c.h
 * Author: tux
 *
 * Created on 6 octobre 2022, 14:37
 */

#define PORTLED PORTC
#define DDRLED  DDRC
#define LEDR    PORTC0
#define LEDY    PORTC1
#define LEDG    PORTC2
//#define LEDBeat PORTC3
#define I2C_ADDR    0x68

volatile uint8_t data;

void CPU_init(void);

