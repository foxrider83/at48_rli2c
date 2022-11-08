/*
 * File:   avr_rli2c.c
 * Author: Infoxelec
 *
 * Created on 5 juillet 2022, 14:01
 * Based on the MBE RLI2C with NXP 762 controller
 * The relays 0 to 7 are on PORTD, relays 8 & 9 are PB0, PB1.
 * 
 * 
 */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "./avr_rli2c.h"
#include "./I2CSlave.h"
#include "./rli2c.h"

int main(void) {
    cli();
    CPU_init();
    sei();
    for(;;) {
        PORTLED ^= (1<<LEDY);
        if (i2creceived != 0){
            go();
        }
        _delay_ms(500);
    }
}

void CPU_init(){
    DDRD = 0xFF;    //Set PORTD as output
    PORTD = 0x00;   //No pullup
    
    DDRB |= (1<<PORTB0) | (1<<PORTB1)| (1<<PORTB2);
    PORTB &= ~((1<<PORTB0) | (1<<PORTB1)| (1<<PORTB2));

    #ifdef LEDBeat
        DDRLED |= _BV(LEDG) | _BV(LEDR) | _BV(LEDY) | _BV(LEDBeat);    //Set PORTC0..3 as output
        PORTLED &= ~(_BV(LEDR)) | ~(_BV(LEDY)) | ~(_BV(LEDG)) | ~(_BV(LEDBeat)); //Set ouput to 0
    #else
        DDRLED |= (1<<LEDG) | (1<<LEDR) | (1<<LEDY);
        PORTLED &= ~((1<<LEDR)) | ~((1<<LEDY)) | ~((1<<LEDG));
    #endif
      // set received/requested callbacks
    I2C_setCallbacks(I2C_received, I2C_requested);
    // init I2C
    I2C_init(I2C_ADDR);
}

