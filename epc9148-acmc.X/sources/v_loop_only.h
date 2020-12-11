/* ********************************************************************************
 * z-Domain Control Loop Designer, Version 0.9.0.76
 * ********************************************************************************
 * 1p1z controller function declarations and compensation filter coefficients
 * derived for following operating conditions:
 * ********************************************************************************
 *
 *  Controller Type:    1P1Z - Basic Integrator
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
 * Date/Time:           2/20/2020 5:32:11 PM
 * *******************************************************************************/

#ifndef __SPECIAL_FUNCTION_LAYER_V_LOOP_ONLY_H__
#define __SPECIAL_FUNCTION_LAYER_V_LOOP_ONLY_H__

#include <xc.h> // include processor files - each processor file is guarded
#include <dsp.h> // include DSP data types (e.g. fractional)
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

#include "npnz16b.h" // include NPNZ library header file

/* *******************************************************************************
 * Data Arrays:
 * The cNPNZ_t data structure contains pointers to coefficient, control and error
 * history arrays. The pointer target objects (variables and arrays) are defined
 * in controller source file v_loop_only.c
 *
 * Type definitions for A- and B- coefficient arrays as well as error- and control
 * history arrays are aligned in memory using the 'packed' attribute for optimized
 * addressing during DSP computations. These aligned data structures need to be
 * placed in specific memory locations to allow direct X/Y-access from the DSP.
 * This X/Y-memory placement is covered by the declarations used in controller
 * source file v_loop_only.c
 * ******************************************************************************/
typedef struct
{
    volatile fractional ACoefficients[1]; // A-Coefficients
    volatile fractional BCoefficients[2]; // B-Coefficients
} __attribute__((packed)) V_LOOP_ONLY_CONTROL_LOOP_COEFFICIENTS_t;

typedef struct
{
    volatile fractional ControlHistory[1];  // Control History Array
    volatile fractional ErrorHistory[2];  // Error History Array
} __attribute__((packed)) V_LOOP_ONLY_CONTROL_LOOP_HISTORIES_t;


extern volatile cNPNZ16b_t v_loop_only; // user-controller data object

/* *******************************************************************************
 * Function call prototypes for initialization routines and control loops
 * ******************************************************************************/

// Initialization of v_loop_only controller object
extern volatile uint16_t v_loop_only_Init( // v_loop_only initialization function call
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Clears the 1P1Z controller output and error histories
extern void v_loop_only_Reset( // v_loop_only reset function call (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );

// Loads user-defined values into 1P1Z controller output and error histories
extern void v_loop_only_Precharge( // v_loop_only history pre-charge function call (Assembly)
        volatile cNPNZ16b_t* controller, // Pointer to nPnZ data type object
        volatile fractional ctrl_input, // user-defined, constant error history value
        volatile fractional ctrl_output // user-defined, constant control output history value
    );

// Calls the v_loop_only controller object
extern void v_loop_only_Update( // Calls the 1P1Z controller (Assembly)
        volatile cNPNZ16b_t* controller // Pointer to nPnZ data type object
    );


#endif // end of __SPECIAL_FUNCTION_LAYER_V_LOOP_ONLY_H__
 
