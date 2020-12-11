/* ********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.0.76
 * ********************************************************************************
 * 2p2z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * ********************************************************************************
 *
 *  Controller Type:    2P2Z - Basic Current Mode Compensator
 *  Sampling Frequency: 200000 Hz
 *  Fixed Point Format: 15
 *  Scaling Mode:       3 - Dual Bit-Shift Scaling
 *  Input Gain:         1
 *
 * *******************************************************************************
 * CGS Version:         1.0.0
 * CGS Date:            11/08/19
 * *******************************************************************************
 * User:                Yuanzhe
 * Date/Time:           2/20/2020 3:33:31 PM
 * *******************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_I_LOOP_H__
#define __SPECIAL_FUNCTION_LAYER_I_LOOP_H__

#include <xc.h> // include processor files - each processor file is guarded
#include <dsp.h> // include DSP data types (e.g. fractional)
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

#include "npnz16b.h" // include NPNZ library header file

/* *******************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error
 * history arrays. The pointer target objects (variables and arrays) are defined
 * in controller source file i_loop.c
 *
 * Type definitions for A- and B- coefficient arrays as well as error- and control
 * history arrays are aligned in memory using the 'packed' attribute for optimized
 * addressing during DSP computations. These aligned data structures need to be
 * placed in specific memory locations to allow direct X/Y-access from the DSP.
 * This X/Y-memory placement is covered by the declarations used in controller
 * source file i_loop.c
 * ******************************************************************************/
typedef struct
{
    volatile fractional ACoefficients[2]; // A-Coefficients
    volatile fractional BCoefficients[3]; // B-Coefficients
} __attribute__((packed)) I_LOOP_CONTROL_LOOP_COEFFICIENTS_t;

typedef struct
{
    volatile fractional ControlHistory[2];  // Control History Array
    volatile fractional ErrorHistory[3];  // Error History Array
} __attribute__((packed)) I_LOOP_CONTROL_LOOP_HISTORIES_t;


extern volatile cNPNZ16b_t i_loop; // user-controller data object

/* *******************************************************************************
 * Function call prototypes for initialization routines and control loops
 * ******************************************************************************/

// Initialization of i_loop controller object
extern volatile uint16_t i_loop_Init( // i_loop initialization function call
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Clears the 2P2Z controller output and error histories
extern void i_loop_Reset( // i_loop reset function call (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Loads user-defined values into 2P2Z controller output and error histories
extern void i_loop_Precharge( // i_loop history pre-charge function call (Assembly)
        volatile cNPNZ16b_t* controller, // Pointer to nPnZ data type object
        volatile fractional ctrl_input, // user-defined, constant error history value
        volatile fractional ctrl_output // user-defined, constant control output history value
    );

// Calls the i_loop controller object
extern void i_loop_Update( // Calls the 2P2Z controller (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );


#endif // end of __SPECIAL_FUNCTION_LAYER_I_LOOP_H__
 
