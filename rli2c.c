/**
 * I2C relay driver based on the MBE 762 rli2c.
 * 
 * 
 */

#include "rli2c.h"
#include "avri2c.h"

/**
 * Message from i2c master
 * @param received_data
 */
void I2C_received(uint8_t received_data)
{
    PORTLED ^= (1<<LEDG);
    i2creceived = received_data;
}

/**
 * Prepare the response to the i2c master
 */
void I2C_requested()
{
    //PORTLED ^= (1<<LEDR);
    I2C_transmitByte(i2creceived);
}

/**
 * Relay management in function of i2creceived
 * Relays 0 to 7 on PORTD, 8, 9, 10 on PORTB
 * 0x8x : activate relay x (from 0 to A)
 * 0x9x : deactivate relay x (from 0 to A)
 * 0xC0 : deactivate relays from 0 to 7
 * 0xC8 : activate all relays from 0 to 7
 */
void go(){
    data = i2creceived;
    if (data == 0xC0){
        PORTD = 0x00;
    }else if(data == 0xC8){
        PORTD = 0xFF;
    }else if ((data & 0x80) == 0x80){
        // test if data > 7
        if (data & 0x08){
            //relays 8 & 9
            uint8_t port = data & 0x03;
            if ((data & 0x10) == 0x10){
                // Use relais x
                PORTB |= (1 << port);
            }else{
                PORTB &= ~(1 << port);
            }
        }else{
            uint8_t port = data & 0x0F;
            //port = port -1;
            if ((data & 0x10) == 0x10){
                // Use relais x
                PORTD |= (1 << port);
            }else{
                PORTD &= ~(1 << port);
            }
        }
    }
}