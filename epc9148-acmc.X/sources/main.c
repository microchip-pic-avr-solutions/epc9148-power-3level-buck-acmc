/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */

#include <xc.h>
#include <dsp.h>
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdlib.h>

#include "globals.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
//#include "npnz16b.h"          /* User funct/params, such as InitApp              */


/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/

int16_t main(void) {

    volatile uint16_t timeout=0;
    
    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Configure required peripherals */
    ConfigureGPIOs();
    ConfigureUART();
    ConfigureSystemTimer();
    ConfigureADC();
    ConfigurePWM();
    ConfigureOPA();
    ConfigureControlLoops();
    ConfigureComparators();
    LaunchPWM();
    
    /* Initialize IO ports and peripherals */
    
    systemstate = off;
    systemstateprevious = off;

    mscounter = 0;
    /*Initialize UART Transmission*/

    tx_count = 0;
//    rx_count = 0;
//    
    T1CONbits.TON = 1;
    
    while (1) {
        
        /* Polling on the interrupt flag bit of timer1 creates a fixed 100usec
         * time step of the main state machine without loosing addition CPU cycles
         * in interrupt latencies. 
         * This fixed clock pace allows deterministic task execution of power control
         * state machine and background tasks like the UART communication or the use
         * of a safer, windowed watchdog timer setting  */
        
        while((!_T1IF) && (timeout++ < 5000));
        _T1IF = 0;
        timeout = 0;
//        LATB ^= (1 << 6);
//        
//        // Clear Watchdog timer
//        ClrWdt();
//
        /* debug , no power control state machine*/
//        // process ms counter 
//        ++mscounter; 
//        if (mscounter > 10000) {
//            mscounter = 10000;
//        }        
//        if (mscounter == 10000) {
//            mscounter = 0;
//            SendData();
//        }        

        /* with power control state machine*/
        // process ms counter 
        ++mscounter; 
        if (mscounter > 10000) {
            mscounter = 10000;
        }        
        // Execute the power control state machine
        PowerControlStateMachine();

        // Send messages via UART with a base clock of 1 sec
//        if (systemstate == running)
//        {
//            if (mscounter == 10000) {
//                mscounter = 0;
                SendData();
//            }
//        }        


    }
}
