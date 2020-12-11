/*
 * File:   power_control.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 3:52 PM
 */


#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "globals.h"


volatile uint16_t PowerControlStateMachine(void) {
    
    static uint16_t delay=0;
//    static uint16_t delayTest;
    
    if (systemstate != systemstateprevious) {
        statechanged = 1;
        systemstateprevious = systemstate;
    }
    
    
    switch (systemstate) {
        case off:
            if (statechanged == 1) {
                statechanged = 0; //allow for delay for on/off events
                mscounter = 0;
            }
//            LATB |= (1 << 5);                
            PWMDISABLED;
            PWMHOLD;

            v_ref = 0;
            i_ref = 0;
            e_cfly = 0;
            sum_e_cfly = 0;
//            e_pos = 0;
//            e_neg = 0;
//            e20_n1 = 0;
//            e20_n2 = 0;
            deltaD_offset = 4;
            DACCTRL1Lbits.DACON = 0; // disable current comparator
    

            if ((mscounter > 100)) //&& 
                 //   (vin_adc > VINADC(UVLO_ON)) && 
                //    (vin_adc < VINADC(OVLO_ON))  &&
                  //  (temperature_adc < TEMPERATUREON) 
            {
                systemstate = outputdischarged;
                
            }
            break;

        case outputdischarged:
            statechanged = 0;
            if (vout_adc < VOUTADC(VOUTKEEPOFFATSTARTUP)) {
                systemstate = waiting5v;
            }
//                if (ENABLEINPUT == 0) {
//                    systemstate = off;
//                }
            break;
            
        case waiting5v:
            statechanged = 0;
            if (vin_adc > VINADC(VINMINFOR5V)) {
                systemstate = chargeCfly;
                // Turn on Q4
                LATB = (1 << 15);    
//                PWMENABLE; // enable all PWMs
                PWMRELEASE;
//                v_ref = vout_adc + RAMPRATE;
//                /* enable controller */
//                low_iout_count = 0;
//                e_cfly = 0;
//                sum_e_cfly = 0;
////                pi_vcfly.status.bits.enable = 1;
//                v_loop.status.bits.enable = 1;
//                i_loop.status.bits.enable = 1;
//                v_loop_only.status.bits.enable = 1;
//                v_loop_only_Precharge(&v_loop_only , 0 , 50 );
//                v_loop_Precharge(&v_loop , 0 , IOUTADC(0.3) );
//                i_loop_Precharge(&i_loop , 0 , 50 );                 
            }
            break;

        case chargeCfly:
            statechanged = 0;
//            LATC &= ~(1 << 2);
            if ( (v_cfly) > (v_cfly_ref-VCFLYADC(0.5)) ) {

                systemstate = softstart_v;
                v_ref = vout_adc + RAMPRATE;
                /* enable controller */
//                pi_vcfly.status.bits.enable = 1;
                e_cfly = 0;
                sum_e_cfly = 0;       
                v_loop.status.bits.enable = 1;
                i_loop.status.bits.enable = 1;
                v_loop_only.status.bits.enable = 1;    
                v_loop_only_Precharge(&v_loop_only , RAMPRATE , 200 );
                v_loop_Precharge(&v_loop , RAMPRATE , IOUTADC(0.15) );
                i_loop_Precharge(&i_loop , 0 , 200 );  
                _PWM2IF = 0;
                pwm2_count = 0;
                _PWM2IE = 1;
                
                delay = 0;

//                LATC |= (1 << 2);
            }
//                if (ENABLEINPUT == 0) {
//                    systemstate = off;
//                }
            break;
            
        case softstart_v:
            if (statechanged == 1) {
                statechanged = 0;
            }
            if (newadcavailable == 1) {
                newadcavailable = 0;
                newadcavailable = 0;
                v_ref += RAMPRATE;
                delay++;
            }        
            if ( (vout_adc > VOUTADC(3)) || (delay > 25) ) {
                v_ref = vout_adc;
                systemstate = softstart;
                v_loop_Precharge(&v_loop , v_loop_only_error , IOUTADC(0.15) );
                i_loop_Precharge(&i_loop , 0 , duty_out );
                DACCTRL1Lbits.DACON = 1; // enable current comparator
            }            
            break;

        case softstart:
//            LATC &= ~(1 << 2);
            if (statechanged == 1) {
                statechanged = 0;
//                    Iout_PID.controlReference = IOUTADC(ILIMITACTUALAMPS);
            }
            if (newadcavailable == 1) {
                newadcavailable = 0;
                newadcavailable = 0;
                v_ref += RAMPRATE;
            }
//            if (v_ref > VOUTADC(5)) {
//                CMP2CONbits.CMPON = 1;
//            }
            if (v_ref >= VOUTADC(VOUTACTUALVOLTS)) {
                v_ref = VOUTADC(VOUTACTUALVOLTS);
                systemstate = running;
//                LATB &= ~(1 << 5);
//                LATB |= (1 << 3);
                delay = 0;
            }
//                if (ENABLEINPUT == 0)//|| (vin_adc < VINADC(UVLO_OFF))
//                       // || (vin_adc > VINADC(OVLO_OFF))) 
//                {
//                    systemstate = off;
//                }
            break;

        case running:
//                LATC = 1 << 7;
            statechanged = 0;
//                if (ENABLEINPUT == 0)//|| (vin_adc < VINADC(UVLO_OFF)) 
//                      //  || (vin_adc > VINADC(OVLO_OFF))) 
//                {
//                    systemstate = off;
//                }
            if (newadcavailable == 1) {
//                    LATC = 1 << 7;
                newadcavailable = 0;
                newadcavailable = 0;

            }
            break;

        case error:
            break;
    }
    
    
    return (1);
}
