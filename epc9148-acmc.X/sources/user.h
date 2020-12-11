
#ifndef SYSTEM_USER_DEFINES_H
#define SYSTEM_USER_DEFINES_H

#include <xc.h>
#include <stdint.h>

/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

//#define FRCCLK      7370000L    // Nominal FRC frequency
//#define FRCTUN      28          // FRC tuning value
//#define FRCTUNRATIO 0.00047     // FRC frequency increment per tuning-tick
//
//#define FRC         (volatile uint32_t)(FRCCLK * (1 + (FRCTUN * FRCTUNRATIO)))    // Nominal FRC frequency
//#define PLL_N1      2
//#define PLL_M       75
//#define PLL_N2      2
//#define FOSC        (volatile uint32_t)((FRC * PLL_M) / (PLL_N1 * PLL_N2)) // Target CPU frequency (2x MIPS)
//#define FCY         (volatile uint32_t)(FOSC/2.0)  // Target peripheral clock frequency
//#define FP          FCY  // Synonym for target peripheral clock frequency
//
//#define FACLK       (volatile uint32_t)(16 * 8 * FRC) //Aux clock frequency to calculate period counters, 1.06nS
//#define TACLK       (float)(1.0/((float)FACLK))

#define PWM_CLOCK   4000000000L   // PWM Generator Base Clock Frequency in [Hz]

#define SWITCHFREQ  400000L  // define your switching frequency ***DAVID***
#define PWM_PERIOD  10000 //((volatile uint16_t) (PWM_CLOCK/SWITCHFREQ))
//#define PWM_RES                     (1.0/PWM_CLOCK)         // PWM Resolution

#define PWM_DEAD_TIME_RE            36  // Falling edge dead time x[250ps]
#define PWM_DEAD_TIME_FE            24  // Falling edge dead time

#define MAXDUTYPERCENT  46.0 //units are % to establish the maximum duty-cycle  ***DAVID***
#define MINDUTYPERCENT  0.5 // %
#define DUTYMAX         ((unsigned const int) (PWM_PERIOD * MAXDUTYPERCENT / 100.0)) //
#define DUTYMIN         ((unsigned const int) (PWM_PERIOD * MINDUTYPERCENT / 100.0))
#define DUTY_FIXED      ((volatile uint16_t) (PWM_PERIOD * 25.0 / 100.0))
#define DUTY_FIXED2      ((volatile uint16_t) (PWM_PERIOD * 45.0 / 100.0))
//#define VCFLYDELTA      2 // Cfly voltage max allowed imbalance voltage [V]
#define VOUTACTUALVOLTS 19//20.05 //***DAVID***
//#define INDUCTORCURRENTRIPPLE ((const int) (3300.0/10.0/4096*32768.0*10.0))
//#define INDUCTORCURRENTRIPPLE 5.5 //A

#define ADC_TRIG_OFFSET    1920
//#define ADCSAMPLEDELAY PWM_PERIOD-600
//#define SADCSAMPLEDELAY PWM_PERIOD-2200
#define ILIMITACTUALAMPS 16 //***DAVID*** output current
#define VOUTKEEPOFFATSTARTUP 2.0  //***DAVID*** pre-bias
#define VINMINFOR5V 6.5
#define RAMPRATE 30 //***DAVID***  // 30 for 28V, 45 for 56V
#define MAXOFFSET 100 //***YZ*** max duty cycle imbalance units [250ps]
//#define MAXOFFSETNEG 51
//#define MAXOFFSETINC 20 // when in sub stable, max additional ducy cycle offset
#define UVLO_ON 14.0 //***DAVID***
#define UVLO_OFF 12.0 //***DAVID***
#define OVLO_ON 80.0 //***DAVID***
#define OVLO_OFF 85.0 //***DAVID*** //cannot exceed 69 due to max ADC value and divider
#define TEMPERATURESD 1550 //***DAVID***
#define TEMPERATUREON 1500 //***DAVID***

#define VREF 3.3
#define ADCSCALE (1<<12)  //12 bit ADC value
//#define MAXTEMPERATURE 850 //850 = 85degC
//#define TEMPERATUREOFFSET 620 //remove 0.5V offset
//#define TEMPERATURESCALE ((const int) (3300.0/10.0/4096*32768.0*10.0)) //scale is 0.1degC = 1
//#define CURRENTSCALE ((const int) (0.15/3.3*4096))

#define VOUTADC(X) ((const int) ((X * 1.0/(7.5+1.0)/VREF*ADCSCALE +0.5) )) //do not converter to Q15
#define VINADC(X) ((const int) ((X * 2.0/(39.0 + 2.0)/VREF * ADCSCALE + 0.5) )) //do not convert to Q15
#define IOUTADC(X) ((const int) ((X * 0.1)/VREF * ADCSCALE + 0.5)) //do not convert to Q15
#define VCFLYADC(X) ((const int) (X * 2.0/(39.0 + 2.0)/VREF * ADCSCALE + 0.5)) // do not convert to Q15



#define VFLY_P_IBIT     2   // 1/4 is Kp
#define VFLY_I_IBIT     8  // 1/512 is Ki
#define VFLY_I_LIMIT    20480

#define VOUT_I_LIMIT    32000

#define M_ASR16(X,Y) ((X >> Y) | (( (int)X < 0)?(0xffff << (16-Y)):0))  // shift right. use this in capacitor voltage PI loop to save time




#define PWMDISABLED { PG1IOCONH &= 0xFFF3; PG2IOCONH &= 0xFFF3; }
#define PWMENABLE   { PG1IOCONH |= 0x000C; PG2IOCONH |= 0x000C; }

#define PWMHOLD     { PG1IOCONL |= 0x3000; PG2IOCONL |= 0x3000; } // Set override bits 
#define PWMRELEASE  { PG1IOCONL &= 0xCFFF; PG2IOCONL &= 0xCFFF; } // clear override bits


#define ENABLEINPUT PORTBbits.RB5

//// These macros are used for UART Transmission of Data
//#define BAUDRATE 		9600
//#define BRGVAL 		((FCY/BAUDRATE)/16)-1  //instruction cycle frequency = 70 MHz = fcy
//#define DELAY_105uS     asm volatile ("REPEAT, #4201"); Nop(); // 105uS delay
//#define DELAY_1uS     asm volatile ("REPEAT, #34"); Nop(); // 105uS delay was 69
//#define DELAY_5uS     asm volatile ("REPEAT, #349"); Nop(); // 105uS delay

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

//void InitApp(void);         /* I/O and Peripheral Initialization */

extern volatile uint16_t ConfigureOscillator(void);
extern volatile uint16_t ConfigureSystemTimer(void);
extern volatile uint16_t ConfigureGPIOs(void);
extern volatile uint16_t ConfigureUART(void);
extern volatile uint16_t ConfigureADC(void);
extern volatile uint16_t ConfigurePWM(void);
extern volatile uint16_t LaunchPWM(void);
extern volatile uint16_t ConfigureOPA (void);
extern volatile uint16_t ConfigureControlLoops(void);
extern volatile uint16_t ConfigureComparators(void);
extern volatile uint16_t PowerControlStateMachine(void);

extern void SendData(void);

//void FilterData(void);

// state machine for the whole converter
enum STATES {
    off,
    outputdischarged,
    waiting5v,
    chargeCfly,
    softstart_v,
    softstart,
    running,
    error
};

// state machine for determining the direction (positive or negative) for capacitor voltage balancing output signal (deltaDQ2)
enum CTRSTATES {
    v_only,
    vNi
};



#endif // end of SYSTEM_USER_DEFINES_H
