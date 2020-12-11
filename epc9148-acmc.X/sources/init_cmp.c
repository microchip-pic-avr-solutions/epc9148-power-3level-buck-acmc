/*
 * File:   init_cmp.c
 * Author: YZ
 *
 * Created on December 18, 2019
 */
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "globals.h"

volatile uint16_t ConfigureComparators(void) {

    // Disable the CMP module before the initialization
    DACCTRL1Lbits.DACON = 0;
    
	// Comparator Register settings
	DACCTRL1L = 0xB1; //CLKDIV 1:4; DACON disabled; DACSIDL disabled; FCLKDIV 1:2; CLKSEL AFPLLO - Auxiliary Clock with PLL Enabled ; 
	DACCTRL2L = 0x55; //TMODTIME 85; 
	DACCTRL2H = 0x8A; //SSTIME 138; 
	DAC2CONH = 0x00; //TMCB 0; 
	DAC2CONL = 0x811D; //CMPPOL Non Inverted; HYSPOL Falling Edge; HYSSEL 15mV; DACEN enabled; FLTREN enabled; CBE disabled; IRQM Interrupts are disabled; INSEL CMP2D; DACOEN enabled; 

	//Slope Settings
	SLP2CONH = 0x00; //HME disabled; PSE Negative; SLOPEN disabled; TWME disabled; 
	SLP2CONL = 0x00; //HCFSEL None; SLPSTRT None; SLPSTOPB None; SLPSTOPA None; 
	SLP2DAT = 0x00; //SLPDAT 0; 
	DAC2DATL = 0x00; //DACDATL 0; 
	DAC2DATH = 20; //DACDATH 205 is minimum value 20;//37; 

    // Enable
//    DACCTRL1Lbits.DACON = 1;

    return (1);
}
