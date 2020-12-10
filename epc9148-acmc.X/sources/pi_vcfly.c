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

#include "pi_vcfly.h"

/* ***************************************************************************************
 * Data Arrays:
 * This source file declares the default parameters of the z-domain compensation filter.  
 * The cNPNZ_t data structure contains two pointers to A- and B- coefficient arrays and   
 * two pointers to control and error history arrays.                                      
 * For optimized data procesing during DSP computations, these arrays must be located in  
 * specific memory locations (X-space for coefficient arrays and Y-space for control and  
 * error history arrays).  
 * The following declarations are used to define the array data contents, their length    
 * and memory location. These declarations are made publicly accessible through defines   
 * in pi_vcfly.h
 * ***************************************************************************************/

	volatile PI_VCFLY_CONTROL_LOOP_COEFFICIENTS_t __attribute__((space(xmemory), near)) pi_vcfly_coefficients; // A/B-Coefficients 
	volatile uint16_t pi_vcfly_ACoefficients_size = (sizeof(pi_vcfly_coefficients.ACoefficients)/sizeof(pi_vcfly_coefficients.ACoefficients[0])); // A-coefficient array size
	volatile uint16_t pi_vcfly_BCoefficients_size = (sizeof(pi_vcfly_coefficients.BCoefficients)/sizeof(pi_vcfly_coefficients.BCoefficients[0])); // B-coefficient array size

	volatile PI_VCFLY_CONTROL_LOOP_HISTORIES_t __attribute__((space(ymemory), far)) pi_vcfly_histories; // Control/Error Histories 
	volatile uint16_t pi_vcfly_ControlHistory_size = (sizeof(pi_vcfly_histories.ControlHistory)/sizeof(pi_vcfly_histories.ControlHistory[0])); // Control history array size
	volatile uint16_t pi_vcfly_ErrorHistory_size = (sizeof(pi_vcfly_histories.ErrorHistory)/sizeof(pi_vcfly_histories.ErrorHistory[0])); // Error history array size

/* ***************************************************************************************
 * 	Pole&Zero Placement:
 * ***************************************************************************************
 *
 * 	fP0:	270 Hz 
 *
 * ***************************************************************************************
 * 	Filter Coefficients and Parameters:
 * ***************************************************************************************/

	volatile fractional pi_vcfly_ACoefficients [1] = 
	{
		0x0000	// Coefficient A1 will be multiplied with controller output u(n-1)
	};

	volatile fractional pi_vcfly_BCoefficients [2] = 
	{
		0x487D,	// Coefficient B0 will be multiplied with error input e(n)
		0x0000	// Coefficient B1 will be multiplied with error input e(n-1)
	};


	volatile int16_t pi_vcfly_pre_scaler = 3;
	volatile int16_t pi_vcfly_post_shift_A = 2; // this is the post shift
	volatile int16_t pi_vcfly_post_shift_B = 8; // B-term does not exist
	volatile fractional pi_vcfly_post_scaler = 0x0000;

	volatile cNPNZ16b_t pi_vcfly; // user-controller data object

/* ***************************************************************************************/

volatile uint16_t pi_vcfly_Init(volatile cNPNZ16b_t* controller)
{
	volatile uint16_t i = 0;

	// Initialize controller data structure at runtime with pre-defined default values
	controller->status.value = CONTROLLER_STATUS_CLEAR;  // clear all status flag bits (will turn off execution))

	controller->ptrACoefficients = &pi_vcfly_coefficients.ACoefficients[0]; // initialize pointer to A-coefficients array
	controller->ptrBCoefficients = &pi_vcfly_coefficients.BCoefficients[0]; // initialize pointer to B-coefficients array
	controller->ptrControlHistory = &pi_vcfly_histories.ControlHistory[0]; // initialize pointer to control history array
	controller->ptrErrorHistory = &pi_vcfly_histories.ErrorHistory[0]; // initialize pointer to error history array
	controller->normPostShiftA = pi_vcfly_post_shift_A; // initialize A-coefficients/single bit-shift scaler
	controller->normPostShiftB = pi_vcfly_post_shift_B; // initialize B-coefficients/dual/post scale factor bit-shift scaler
	controller->normPostScaler = pi_vcfly_post_scaler; // initialize control output value normalization scaling factor
	controller->normPreShift = pi_vcfly_pre_scaler; // initialize A-coefficients/single bit-shift scaler

	controller->ACoefficientsArraySize = pi_vcfly_ACoefficients_size; // initialize A-coefficients array size
	controller->BCoefficientsArraySize = pi_vcfly_BCoefficients_size; // initialize A-coefficients array size
	controller->ControlHistoryArraySize = pi_vcfly_ControlHistory_size; // initialize control history array size
	controller->ErrorHistoryArraySize = pi_vcfly_ErrorHistory_size; // initialize error history array size


	// Load default set of A-coefficients from user RAM into X-Space controller A-array
	for(i=0; i<controller->ACoefficientsArraySize; i++)
	{
		pi_vcfly_coefficients.ACoefficients[i] = pi_vcfly_ACoefficients[i];
	}

	// Load default set of B-coefficients from user RAM into X-Space controller B-array
	for(i=0; i<controller->BCoefficientsArraySize; i++)
	{
		pi_vcfly_coefficients.BCoefficients[i] = pi_vcfly_BCoefficients[i];
	}

	// Clear error and control histories of the 1P1Z controller
	pi_vcfly_Reset(&pi_vcfly);

	return(1);
}


