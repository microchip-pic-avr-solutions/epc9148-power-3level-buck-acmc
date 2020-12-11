/*
 * File:   init_cmp.c
 * Author: Y07281
 *
 * Created on December 18, 2019
 */

#include <xc.h>
#include <stdint.h>
#include "user.h"


volatile uint16_t ConfigureOPA (void) {

    // Set the OPA1 to the options selected in the User Interface

    // AMPEN2 enabled; AMPEN1 enabled; AMPON enabled; 
    AMPCON1L = 0x8001; //Disabling AMPPON bit initially
    // NCHDIS2 Wide input voltage range; NCHDIS1 Wide input voltage range; 
    AMPCON1H = 0x00;
    
    AMPCON1Lbits.AMPEN1 = 1; //Enable OPA1;
    
    return (1);
}
