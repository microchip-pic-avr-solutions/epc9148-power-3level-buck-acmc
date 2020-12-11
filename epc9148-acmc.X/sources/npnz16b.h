/* ********************************************************************************
* z-Domain Control Loop Designer, Version 0.9.0.76
* ********************************************************************************
* Generic library header for z-domain compensation filter assembly functions
* CGS Version: 1.0.0
* CGS Date:    11/08/19
* ********************************************************************************/
#ifndef __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__
#define __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__

#include <xc.h> // include processor files - each processor file is guarded
#include <dsp.h> // include DSP data types (e.g. fractional)
#include <stdint.h> // include standard integer number data types
#include <stdbool.h> // include standard boolean data types (true/false)

/* Status flags (Single Bit) */
#define NPNZ16_STATUS_LSAT_SET             1
#define NPNZ16_STATUS_LSAT_CLEAR           0
#define NPNZ16_STATUS_USAT_SET             1
#define NPNZ16_STATUS_USAT_CLEAR           0
#define NPNZ16_STATUS_INPUT_INVERTED       1
#define NPNZ16_STATUS_INPUT_NOT_INVERTED   0
#define NPNZ16_STATUS_ENABLED              1
#define NPNZ16_STATUS_DISABLED             0

/* Status flags (bit-field) */
typedef enum {
    CONTROLLER_STATUS_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_SATUATION_MSK = 0b0000000000000011,
    CONTROLLER_STATUS_LSAT_ACTIVE = 0b0000000000000001,
    CONTROLLER_STATUS_LSAT_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_USAT_ACTIVE = 0b0000000000000010,
    CONTROLLER_STATUS_USAT_CLEAR = 0b0000000000000000,
    CONTROLLER_STATUS_INV_INPUT_OFF = 0b0000000000000000,
    CONTROLLER_STATUS_INV_INPUT_ON = 0b0100000000000000,
    CONTROLLER_STATUS_ENABLE_OFF = 0b0000000000000000,
    CONTROLLER_STATUS_ENABLE_ON = 0b1000000000000000
} CONTROLLER_STATUS_FLAGS_t;

typedef union {
    struct {
        volatile unsigned flt_clamp_min : 1; // Bit 0: control loop is clamped at minimum output level
        volatile unsigned flt_clamp_max : 1; // Bit 1: control loop is clamped at maximum output level
        volatile unsigned : 1; // Bit 2: reserved
        volatile unsigned : 1; // Bit 3: reserved
        volatile unsigned : 1; // Bit 4: reserved
        volatile unsigned : 1; // Bit 5: reserved
        volatile unsigned : 1; // Bit 6: reserved
        volatile unsigned : 1; // Bit 7: reserved
        volatile unsigned : 1; // Bit 8: reserved
        volatile unsigned : 1; // Bit 9: reserved
        volatile unsigned : 1; // Bit 11: reserved
        volatile unsigned : 1; // Bit 11: reserved
        volatile unsigned : 1; // Bit 12: reserved
        volatile unsigned : 1; // Bit 13: reserved
        volatile unsigned invert_input: 1; // Bit 14: when set, most recent error input value to controller is inverted
        volatile unsigned enable : 1; // Bit 15: enables/disables control loop execution
    } __attribute__((packed))bits;    // Controller status bit-field for direct bit access
    volatile uint16_t value;          // Controller status full register access
} __attribute__((packed))CONTROLLER_STATUS_t; // Controller status data structure

typedef struct {
    // External control and monitoring
    volatile CONTROLLER_STATUS_t status; // Control Loop Status flags

    // Input/Output to controller
    volatile uint16_t* ptrSource; // Pointer to source register or variable where the input value is read from (e.g. ADCBUF0)
    volatile uint16_t* ptrTarget; // Pointer to target register or variable where the control output is written to (e.g. PCD1)
    volatile uint16_t* ptrControlReference; // Pointer to global variable of input register holding the controller reference value (e.g. uint16_t my_ref)

    // Filter coefficients and input/output histories
    volatile fractional* ptrACoefficients; // Pointer to A coefficients located in X-space
    volatile fractional* ptrBCoefficients; // Pointer to B coefficients located in X-space
    volatile fractional* ptrControlHistory; // Pointer to n delay-line samples located in Y-space with first sample being the most recent
    volatile fractional* ptrErrorHistory; // Pointer to n+1 delay-line samples located in Y-space with first sample being the most recent

    // Array size information
    volatile uint16_t ACoefficientsArraySize; // Size of the A coefficients array in X-space
    volatile uint16_t BCoefficientsArraySize; // Size of the B coefficients array in X-space
    volatile uint16_t ControlHistoryArraySize; // Size of the control history array in Y-space
    volatile uint16_t ErrorHistoryArraySize; // Size of the error history array in Y-space

    // Feedback scaling Input/Output Normalization
    volatile int16_t normPreShift; // Normalization of ADC-resolution to Q15 (R/W)
    volatile int16_t normPostShiftA; // Normalization of A-term control output to Q15 (R/W)
    volatile int16_t normPostShiftB; // Normalization of B-term control output to Q15 (R/W)
    volatile int16_t normPostScaler; // Control output normalization factor (Q15) (R/W)

    // Feedback conditioning
    volatile int16_t InputOffset; // Control input source offset value (R/W)

    // System clamping/Anti-windup
    volatile int16_t MinOutput; // Minimum output value used for clamping (R/W)
    volatile int16_t MaxOutput; // Maximum output value used for clamping (R/W)

    // Voltage/Average Current Mode Control Trigger handling
    volatile uint16_t* ptrADCTriggerARegister; // Pointer to ADC trigger #1 register (e.g. TRIG1)
    volatile uint16_t ADCTriggerAOffset; // ADC trigger #1 offset to compensate propagation delays
    volatile uint16_t* ptrADCTriggerBRegister; // Pointer to ADC trigger #2 register (e.g. TRIG2)
    volatile uint16_t ADCTriggerBOffset; // ADC trigger #2 offset to compensate propagation delays

    // Data Provider Sources
    volatile uint16_t* ptrDataProviderControlInput; // Pointer to external data buffer of most recent control input
    volatile uint16_t* ptrDataProviderControlError; // Pointer to external data buffer of most recent control error
    volatile uint16_t* ptrDataProviderControlOutput; // Pointer to external data buffer of most recent control output

} __attribute__((packed))cNPNZ16b_t; // Generic nPnZ Controller Object with 16-bit fixed point coefficients, data input and data output


typedef struct {
    // External control and monitoring
    volatile CONTROLLER_STATUS_t status; // Control Loop Status flags

    // Input/Output to controller
    volatile uint16_t* ptrSource; // Pointer to source register or variable where the input value is read from (e.g. ADCBUF0)
    volatile uint16_t* ptrTarget; // Pointer to target register or variable where the control output is written to (e.g. PCD1)
    volatile uint16_t* ptrControlReference; // Pointer to global variable of input register holding the controller reference value (e.g. uint16_t my_ref)

    // Filter coefficients and input/output histories
    volatile int32_t* ptrACoefficients; // Pointer to A coefficients located in X-space
    volatile int32_t* ptrBCoefficients; // Pointer to B coefficients located in X-space
    volatile fractional* ptrControlHistory; // Pointer to n delay-line samples located in Y-space with first sample being the most recent
    volatile fractional* ptrErrorHistory; // Pointer to n+1 delay-line samples located in Y-space with first sample being the most recent

    // Array size information
    volatile uint16_t ACoefficientsArraySize; // Size of the A coefficients array in X-space
    volatile uint16_t BCoefficientsArraySize; // Size of the B coefficients array in X-space
    volatile uint16_t ControlHistoryArraySize; // Size of the control history array in Y-space
    volatile uint16_t ErrorHistoryArraySize; // Size of the error history array in Y-space

    // Feedback scaling Input/Output Normalization
    volatile int16_t normPreShift; // Normalization of ADC-resolution to Q15 (R/W)
    volatile int16_t normPostShiftA; // Normalization of A-term control output to Q15 (R/W)
    volatile int16_t normPostShiftB; // Normalization of B-term control output to Q15 (R/W)
    volatile int16_t normPostScaler; // Control output normalization factor (Q15) (R/W)

    // Feedback conditioning
    volatile int16_t InputOffset; // Control input source offset value (R/W)

    // System clamping/Anti-windup
    volatile int16_t MinOutput; // Minimum output value used for clamping (R/W)
    volatile int16_t MaxOutput; // Maximum output value used for clamping (R/W)

    // Voltage/Average Current Mode Control Trigger handling
    volatile uint16_t* ptrADCTriggerARegister; // Pointer to ADC trigger #1 register (e.g. TRIG1)
    volatile uint16_t ADCTriggerAOffset; // ADC trigger #1 offset to compensate propagation delays
    volatile uint16_t* ptrADCTriggerBRegister; // Pointer to ADC trigger #2 register (e.g. TRIG2)
    volatile uint16_t ADCTriggerBOffset; // ADC trigger #2 offset to compensate propagation delays

    // Data Provider Sources
    volatile uint16_t* ptrDataProviderControlInput; // Pointer to external data buffer of most recent control input
    volatile uint16_t* ptrDataProviderControlError; // Pointer to external data buffer of most recent control error
    volatile uint16_t* ptrDataProviderControlOutput; // Pointer to external data buffer of most recent control output

} __attribute__((packed))cNPNZ3216b_t; // Generic nPnZ Controller Object with 32-bit fast floating point coefficients, 16-bit data input and data output


/* ********************************************************************************/
#endif	// end of __SPECIAL_FUNCTION_LAYER_LIB_NPNZ_H__ header file section

