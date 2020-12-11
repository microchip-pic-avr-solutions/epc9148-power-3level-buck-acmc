/*
 * File:   ini_adc.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 2:13 PM
 */


#include <xc.h>
#include <stdint.h>
#include "user.h"


volatile uint16_t ConfigureADC(void) {

    volatile uint16_t timeout=0;    
    /* init adc module */
    // Make sure power to peripheral is enabled
    PMD1bits.ADC1MD = 0; // ADC Module Power Disable: ADC module power is enabled

    // ADCON1L: ADC CONTROL REGISTER 1 LOW
    ADCON1Lbits.ADON = 0; // ADC Enable: ADC module is off during configuration
    ADCON1Lbits.ADSIDL = 0; // ADC Stop in Idle Mode: Continues module operation in Idle mode

    // ADCON1H: ADC CONTROL REGISTER 1 HIGH
    // ADCON1Hbits.SHRRES = 0b11; // Shared ADC Core Resolution Selection: 12-bit resolution ADC resolution = 12-bit (0...4095 ticks)
    // ADCON1Hbits.FORM = 0; // Fractional Data Output Format: Integer
    // FORM Integer; SHRRES 12-bit resolution;
    ADCON1H = 0x60;

    // ADCON2L: ADC CONTROL REGISTER 2 LOW
    ADCON2Lbits.REFCIE = 0;; // Band Gap and Reference Voltage Ready Common Interrupt Enable: Common interrupt is disabled for the band gap ready event
    ADCON2Lbits.REFERCIE = 0; // Band Gap or Reference Voltage Error Common Interrupt Enable: Disabled
    ADCON2Lbits.EIEN = 1; // Early Interrupts Enable: The early interrupt feature is enabled
    //ADCON2Lbits.PTGEN = 0; // External Conversion Request Interface: Disabled
    ADCON2Lbits.SHREISEL = 0b111; // Shared Core Early Interrupt Time Selection: Early interrupt is set and interrupt is generated 8 TADCORE clocks prior to when the data are ready
    ADCON2Lbits.SHRADCS = 0b0000010; // Shared ADC Core Input Clock Divider: 4:1

    // ADCON2H: ADC CONTROL REGISTER 2 HIGH
    ADCON2Hbits.SHRSAMC = 2; // Shared ADC Core Sample Time Selection: 4x TADs sampling time
    ADCON2Hbits.REFERR = 0; // reset error flag
    ADCON2Hbits.REFRDY = 0; // reset bandgap status bit

    // ADCON3L: ADC CONTROL REGISTER 3 LOW
    // ADCON3Lbits.REFSEL = 0b000; // ADC Reference Voltage Selection: AVDD-toAVSS
    // ADCON3Lbits.SUSPEND = 0; // All ADC Core Triggers Disable: All ADC cores can be triggered
    // ADCON3Lbits.SUSPCIE = 0; // Suspend All ADC Cores Common Interrupt Enable: Common interrupt is not generated for suspend ADC cores
    // ADCON3Lbits.SUSPRDY = 0; // All ADC Cores Suspended Flag: ADC cores have previous conversions in progress
    // ADCON3Lbits.SHRSAMP = 0; // Shared ADC Core Sampling Direct Control: use hardware trigger
    // ADCON3Lbits.CNVRTCH = 0; // Software Individual Channel Conversion Trigger: Next individual channel conversion trigger can be generated (not used)
    // ADCON3Lbits.SWLCTRG = 0; // Software Level-Sensitive Common Trigger: No software, level-sensitive common triggers are generated (not used)
    // ADCON3Lbits.SWCTRG = 0; // Software Common Trigger: Ready to generate the next software common trigger (not used)
    // ADCON3Lbits.CNVCHSEL = 0; // Channel Number Selection for Software Individual Channel Conversion Trigger: AN0 (not used)
    // SWCTRG disabled; SHRSAMP disabled; SUSPEND disabled; SWLCTRG disabled; SUSPCIE disabled; CNVCHSEL AN0; REFSEL disabled;
    ADCON3L = 0x00;

    // ADCON3H: ADC CONTROL REGISTER 3 HIGH
    ADCON3Hbits.CLKSEL = 0b10; // ADC Module Clock Source Selection: AFVCODIV (this is AFvco/4 = 250 MHz)
    ADCON3Hbits.CLKDIV = 0b000000; // ADC Module Clock Source Divider: 1 Source Clock Period
    ADCON3Hbits.SHREN = 0; // Shared ADC Core Enable: Shared ADC core is disabled
    ADCON3Hbits.C0EN = 0; // Dedicated ADC Core 0 Enable: Dedicated ADC Core 0 is disabled
    ADCON3Hbits.C1EN = 0; // Dedicated ADC Core 1 Enable: Dedicated ADC Core 1 is disabled

    // ADCON4L: ADC CONTROL REGISTER 4 LOW
    // ADCON4Lbits.SAMC0EN = 0;  // Dedicated ADC Core 0 Conversion Delay Enable: Immediate conversion
    // ADCON4Lbits.SAMC1EN = 0;  // Dedicated ADC Core 1 Conversion Delay Enable: Immediate conversion
    // SAMC0EN disabled; SAMC1EN disabled;
    ADCON4L = 0x00;

    // ADCON4H: ADC CONTROL REGISTER 4 HIGH
    ADCON4Hbits.C0CHS = 0b00; // Dedicated ADC Core 0 Input Channel Selection: AN0
    ADCON4Hbits.C1CHS = 0b00; // Dedicated ADC Core 1 Input Channel Selection: AN1

    // ADCON5L: ADC CONTROL REGISTER 5 LOW
    // ADCON5Lbits.SHRRDY: Shared ADC Core Ready Flag (read only)
    // ADCON5Lbits.C0RDY: Dedicated ADC Core 0 Ready Flag (read only)
    // ADCON5Lbits.C1RDY: Dedicated ADC Core 1 Ready Flag (read only)
    ADCON5Lbits.SHRPWR = 0; // Shared ADC Core Power Enable: ADC core is off
    ADCON5Lbits.C0PWR = 0; // Dedicated ADC Core 0 Power Enable: ADC core is off
    ADCON5Lbits.C1PWR = 0; // Dedicated ADC Core 1 Power Enable: ADC core is off

    // ADCON5H: ADC CONTROL REGISTER 5 HIGH
    ADCON5Hbits.WARMTIME = 0b1111; // ADC Dedicated Core x Power-up Delay: 32768 Source Clock Periods
    ADCON5Hbits.SHRCIE = 0; // Shared ADC Core Ready Common Interrupt Enable: Common interrupt is disabled for an ADC core ready event
    ADCON5Hbits.C0CIE = 0; // C1CIE: Dedicated ADC Core 0 Ready Common Interrupt Enable: Common interrupt is disabled
    ADCON5Hbits.C1CIE = 0; // C1CIE: Dedicated ADC Core 1 Ready Common Interrupt Enable: Common interrupt is disabled

    // ADCORExL: DEDICATED ADC CORE x CONTROL REGISTER LOW
    ADCORE1Lbits.SAMC = 0b0000000000;   // Dedicated ADC Core 1 Conversion Delay Selection: 2 TADCORE (minimum)
    ADCORE0Lbits.SAMC = 0b0000000000;   // Dedicated ADC Core 0 Conversion Delay Selection: 2 TADCORE (minimum)

    // ADCORExH: DEDICATED ADC CORE x CONTROL REGISTER HIGH
    ADCORE0Hbits.RES = 0b11; // ADC Core x Resolution Selection: 12 bit
    ADCORE0Hbits.ADCS = 0b0000010; // ADC Core x Input Clock Divider: 4 Source Clock Periods
    ADCORE0Hbits.EISEL = 0b111; // Early interrupt is set and an interrupt is generated 8 TADCORE clocks prior

    ADCORE1Hbits.RES = 0b11; // ADC Core x Resolution Selection: 12 bit
    ADCORE1Hbits.ADCS = 0b0000010; // ADC Core x Input Clock Divider: 4 Source Clock Periods
    ADCORE1Hbits.EISEL = 0b111; // Early interrupt is set and an interrupt is generated 8 TADCORE clocks prior    
    

    _TRGSRC0 = 0b00110;  // AN0 PWM2 Trigger1
    _TRGSRC1 = 0b00100;  // AN1 PWM1 Trigger1
    _TRGSRC2 = 0b00110;  // AN0 PWM2 Trigger1
    _TRGSRC3 = 0b00110;  // AN0 PWM2 Trigger1
    
    //TRGSRC3 PWM1 Trigger1; TRGSRC2 PWM2 Trigger1; 
//    ADTRIG0H = 0x606;
//
//    
//    ADEIELbits.EIEN0 = 1; // Early interrupt is enabled for the channel
//    ADIELbits.IE0 = 1;
//    _ADCAN0IP = 5;
//    _ADCAN0IF = 0;
//    _ADCAN0IE = 1;
    
    ADEIELbits.EIEN1 = 1; // Early interrupt is enabled for the channel
    ADIELbits.IE1 = 1;
    _ADCAN1IP = 5;
    _ADCAN1IF = 0;
    _ADCAN1IE = 1;    
//    
////    ADIELbits.IE3 = 1;
////    _ADCAN3IP = 5;
////    _ADCAN3IF = 0;
////    _ADCAN3IE = 1;    
//    
//    ADIELbits.IE4 = 1;
//    _ADCAN4IP = 5;
//    _ADCAN4IF = 0;
//    _ADCAN4IE = 1;
//    
//
//
    /* launch adc */
    if(ADCON1Lbits.ADON) return(1);

    ADCON1Lbits.ADON = 1; // ADC Enable: ADC module is enabled first

    ADCON5Lbits.SHRPWR = 1; // Enabling Shared ADC Core analog circuits power
    while((!ADCON5Lbits.SHRRDY) && (timeout++<8000));
    if((!ADCON5Lbits.SHRRDY) || (timeout>=8000)) return(0);
    ADCON3Hbits.SHREN  = 1; // Enable Shared ADC digital circuitry

    ADCON5Lbits.C0PWR = 1; // Dedicated ADC Core 0 Power Enable: ADC core is on
    while((!ADCON5Lbits.C0RDY) && (timeout++<8000));
    if((!ADCON5Lbits.C0RDY) || (timeout>=8000)) return(0);
    ADCON3Hbits.C0EN  = 1; // Dedicated Core 0 is not enabled

    ADCON5Lbits.C1PWR = 1; // Dedicated ADC Core 1 Power Enable: ADC core is on
    while((!ADCON5Lbits.C1RDY) && (timeout++<8000));
    if((!ADCON5Lbits.C1RDY) || (timeout>=8000)) return(0);
    ADCON3Hbits.C1EN  = 1; // Dedicated Core 1 is not enabled    
    return (1);
}
