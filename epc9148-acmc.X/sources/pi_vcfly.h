/* ***************************************************************************************
 * z-Domain Control Loop Designer Version 0.9.0.70.
 * ***************************************************************************************
 * 1p1z compensation filter coefficients derived for following operating conditions:
 * ***************************************************************************************
 *
 * 	Controller Type:	1P1Z - Basic Integrator
 * 	Sampling Frequency:	100000 Hz 
 * 	Fixed Point Format:	15
 * 	Scaling Mode:		1 - Single Bit-Shift Scaling
 * 	Input Gain:			1
 * 
 * ***************************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_PI_VCFLY_H__
#define __SPECIAL_FUNCTION_LAYER_PI_VCFLY_H__

#include <xc.h>
#include <dsp.h>
#include <stdint.h>

#include "npnz16b.h"

/* ***************************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error history 
 * arrays. The pointer target objects (variables and arrays) are defined in               
 * pi_vcfly.c
 * This header file holds the public declarations for these variables and arrays.         
 * 
 * Type definitions for A- and B- coefficient arrays as well as error- and control history
 * arrays are aligned in memory using the 'packed' attribute for optimized addressing     
 * during DSP computations. These aligned data structures need to be placed in specific   
 * memory locations to allow direct X/Y-access from the DSP. This X/Y-memory placement is 
 * covered by the declarations used in pi_vcfly.c               
 * ***************************************************************************************/

	typedef struct
	{
		volatile fractional ACoefficients[1]; // A-Coefficients
		volatile fractional BCoefficients[2]; // B-Coefficients
	} __attribute__((packed))PI_VCFLY_CONTROL_LOOP_COEFFICIENTS_t;

	typedef struct
	{
		volatile fractional ControlHistory[1];  // Control History
		volatile fractional ErrorHistory[2];    // Error History
	} __attribute__((packed))PI_VCFLY_CONTROL_LOOP_HISTORIES_t;


	extern volatile cNPNZ16b_t pi_vcfly; // user-controller data object

/* ***************************************************************************************/

// Function call prototypes for initialization routines and control loops

extern volatile uint16_t pi_vcfly_Init( // Loads default coefficients into 1P1Z controller and resets histories to zero
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void pi_vcfly_Reset( // Resets the 1P1Z controller histories
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

extern void pi_vcfly_Precharge( // Pre-charges histories of the 1P1Z with defined steady-state data
	volatile cNPNZ16b_t* controller, // Pointer to nPnZ data structure
	volatile uint16_t ctrl_input, // user-defined, constant error history value
	volatile uint16_t ctrl_output // user-defined, constant control output history value
	);

extern void pi_vcfly_Update( // Calls the 1P1Z controller
	volatile cNPNZ16b_t* controller // Pointer to nPnZ data structure
	);

#endif	// end of __SPECIAL_FUNCTION_LAYER_PI_VCFLY_H__ header file section
