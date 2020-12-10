/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */

#include <xc.h>
#include <stdint.h>        /* Includes uint16_t definition   */
#include <stdbool.h>       /* Includes true/false definition */

#include "globals.h"


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADCAN1Interrupt(void)
{
    LATB |= (1 << 11);
    int16_t temp_e, temp_s;
    v_cfly = ADCBUF0;
    vout_adc = ADCBUF2;
    vin_adc = ADCBUF3;
    v_cfly_ref = (vin_adc >> 1);
    newadcavailable = 1;//means that some ADC has triggered interrupt since its measurement is available
    iout_adc = ADCBUF1;
    
    
    if ( (!DAC2CONLbits.CMPSTAT) && (iout_adc < IOUTADC(0.15)) ) { // low current
//    if ( iout_adc < IOUTADC(0.15) ) { // low current    

//        LATB &= ~(1 << 11);
        v_loop_only_Update(&v_loop_only);
        v_loop_Precharge(&v_loop , v_loop_only_error , IOUTADC(0.15) );
        i_loop_Precharge(&i_loop , 0 , duty_out );         
//
    } else { // high current
//        LATB |= (1 << 11);
        v_loop_Update(&v_loop);
        i_loop_Update(&i_loop);
        v_loop_only_Precharge(&v_loop_only , v_loop_error , duty_out );   

    }   
//    i_loop2_out = (PWM_PERIOD >> 1) + ADC_TRIG_OFFSET - i_trigger;
//    LATB |= (1 << 11);
    while (PG1STATbits.UPDATE == 1);
    PG1TRIGB = (PWM_PERIOD >> 1) - i_trigger + ADC_TRIG_OFFSET;
    PG1PHASE = PWM_PERIOD - duty_out;
//    LATB &= ~(1 << 11);
    
//    pi_vcfly_Update(&pi_vcfly);
    e_cfly = v_cfly_ref - v_cfly;
    sum_e_cfly = sum_e_cfly + e_cfly;
    if (sum_e_cfly < -VFLY_I_LIMIT) {
        sum_e_cfly = -VFLY_I_LIMIT;
    } else if (sum_e_cfly > VFLY_I_LIMIT) {
        sum_e_cfly = VFLY_I_LIMIT;       
    }    
    __asm__ volatile ("asr %1, #2, %0"
        : "=r"(temp_e)
        : "r"(e_cfly) );
    
    __asm__ volatile ("asr %1, #8, %0"
        : "=r"(temp_s)
        : "r"(sum_e_cfly) );  
    deltaDQ2 = temp_e + temp_s;

    if (deltaDQ2 < -MAXOFFSET) {
        deltaDQ2 = -MAXOFFSET;
    } else if (deltaDQ2 > MAXOFFSET) {
        deltaDQ2 = MAXOFFSET;
    }    
//    deltaDQ2 = deltaD_offset - MAXOFFSET;
//    LATB |= (1 << 11);
    while (PG2STATbits.UPDATE == 1);
    PG2TRIGA = (PWM_PERIOD >> 1) - i_trigger;    
    PG2PHASE = PWM_PERIOD - duty_out + deltaDQ2;
    LATB &= ~(1 << 11);
//    
//    PG1STATbits.UPDREQ = 1; // Request PWM Data register update
//    PG2STATbits.UPDREQ = 1; // Update all PWM registers of PG2
//    LATB &= ~(1 << 10);    
    _ADCAN1IF = 0;
}

void __attribute__((interrupt, auto_psv)) _PWM2Interrupt(void) {
    pwm2_count++;
    if (pwm2_count == 1) {
        LATB |= (1 << 13);   // turn on Q3
    } else if (pwm2_count == 4) {
        PG2IOCONH |= 0x000C; // enable Q2, Q3 PWM
//        PG2IOCONL &= 0xCFFF;
    } else if (pwm2_count == 7) {
        PG1IOCONH |= 0x000C; // enable Q1, Q4 PWM
//        PG1IOCONL &= 0xCFFF;
        _PWM2IE = 0;  // disable PWM2 interrupt
    }
    _PWM2IF = 0;
}
