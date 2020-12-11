/*
 * File:   uart.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 4:05 PM
 */


#include <xc.h>
#include "globals.h"
#include "user.h"

void SendData() { 
    char ReceivedChar;
    if (tx_count == 0) { //only check for receiver when not transmitting
        /* Check for receive errors */
        if(U1STAbits.FERR == 1)
        {
            return;
        }
        /* Must clear the overrun error to keep UART receiving */
        if(U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;
            return;
        }
        /* Get the data */
        if(!(U1STAHbits.URXBE == 1))
        {
            ReceivedChar = U1RXREG;
            if (ReceivedChar == 'A') {
                // start transmit
                tx_count = 1;
//                U1TXREG = 'R';
//                U1TXREG = 'M';
//                U1TXREG = 'C';
//                U1TXREG = 'U';
//                U1TXREG = 'A';
//                U1TXREG = 'B';
//                U1TXREG = 'C';
//                U1TXREG = 'U'; 
            uint16_t adc2 = v_cfly; //reading from ADCBUF to unsigned int  Current1
            uint16_t adc3 = iout_adc; // Vcfly pos is [1], negative is [0] 
            uint16_t adc4 = vout_adc; //reading from ADCBUF to unsigned int  Current1
            uint16_t adc5 = vin_adc; // Vcfly pos is [1], negative is [0]             
            uint8_t x1 = adc2 & 0xFF; // low byte
            uint8_t x2 = adc2 >> 8; // high byte
            uint8_t x3 = adc3 & 0xFF; // low byte
            uint8_t x4 = adc3 >> 8; // high byte         
            uint8_t x5 = adc4 & 0xFF; // low byte
            uint8_t x6 = adc4 >> 8; // high byte
            uint8_t x7 = adc5 & 0xFF; // low byte
            uint8_t x8 = adc5 >> 8; // high byte   

            U1TXREG = x1;// Transmit low bit
            U1TXREG = x2;// Transmit high bit
            U1TXREG = x3;// Transmit low bit
            U1TXREG = x4;// Transmit high bit 
            U1TXREG = x5;// Transmit low bit
            U1TXREG = x6;// Transmit high bit
            U1TXREG = x7;// Transmit low bit
            U1TXREG = x8;// Transmit high bit             
            }
        }
    }    
    if(U1STAbits.TRMT == 1) { // TX buffer empty, we can write

        if (tx_count == 1)
        {
            uint16_t adc4 = deltaDQ2;
            uint16_t adc5 = PG1PHASE;
            uint16_t adc6 = PG2PHASE;
            uint8_t x7 = systemstate;
            uint8_t x1 = adc4 & 0xFF; // low byte
            uint8_t x2 = adc4 >> 8; // high byte
            uint8_t x3 = adc5 & 0xFF; // low byte
            uint8_t x4 = adc5 >> 8; // high byte         
            uint8_t x5 = adc6 & 0xFF; // low byte
            uint8_t x6 = adc6 >> 8; // high byte   
            
                U1TXREG = x1;
                U1TXREG = x2;
                U1TXREG = x3;
                U1TXREG = x4;
                U1TXREG = x5;
                U1TXREG = x6;
                U1TXREG = x7;
                U1TXREG = 0;                

//            uint16_t adc2 = vout_adc; //reading from ADCBUF to unsigned int  Current1
//            uint16_t adc3 = i_ref; // Vcfly pos is [1], negative is [0] 
//            uint8_t x1 = adc2 & 0xFF; // low byte
//            uint8_t x2 = adc2 >> 8; // high byte
//            uint8_t x3 = adc3 & 0xFF; // low byte
//            uint8_t x4 = adc3 >> 8; // high byte        
//
//            U1TXREG = x1;// Transmit low bit
//            U1TXREG = x2;// Transmit high bit
//            U1TXREG = x3;// Transmit low bit
//            U1TXREG = x4;// Transmit high bit
//            
            tx_count = 0;
        }
    }
}


