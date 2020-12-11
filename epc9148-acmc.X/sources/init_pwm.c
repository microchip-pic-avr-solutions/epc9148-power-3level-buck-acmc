

#include <xc.h>
#include <stdint.h>
#include "user.h"

volatile uint16_t ConfigurePWM(void) {

    /* init pwm module */
    // Make sure power to the peripheral is enabled
    PMD1bits.PWMMD = 0; // PWM Module Disable: PWM module is enabled

    // PWM GENERATOR ENABLE
    PG1CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    PG2CONLbits.ON = 0; // PWM Generator #2 Enable: PWM Generator is not enabled
    PG3CONLbits.ON = 0; // PWM Generator #3 Enable: PWM Generator is not enabled
    PG4CONLbits.ON = 0; // PWM Generator #4 Enable: PWM Generator is not enabled

    // PWM CLOCK CONTROL REGISTER
    // MCLKSEL AFPLLO - Auxiliary Clock with PLL Enabled; HRERR disabled; LOCK disabled; DIVSEL 1:2;
    PCLKCON = 0x03;
    // PCLKCONbits.LOCK = 0;       // Lock bit: Write-protected registers and bits are unlocked
    // PCLKCONbits.DIVSEL = 0b00;  // PWM Clock Divider Selection: Divide ratio is 1:2
    // PCLKCONbits.MCLKSEL = 0b11; // PWM Master Clock Selection: Auxiliary PLL post-divider output

    // FREQUENCY SCALE REGISTER & FREQUENCY SCALING MINIMUM PERIOD REGISTER
    FSCL = 0x0000;      // Reset frequency scaling register
    FSMINPER = 0x0000;  // Reset frequency scaling minimum register

    // MASTER PHASE, DUTY CYCLE AND PERIOD REGISTERS
    MPHASE = 0;     // Reset master phase
    MDC    = 0;     // Reset master duty cycle
    // MPER 16;
//    MPER = 0x10;
    // MPER   = 0;     // Master period PWM_PERIOD

    // LINEAR FEEDBACK SHIFT REGISTER
    LFSR = 0x0000;      // Reset linear feedback shift register

    // COMBINATIONAL TRIGGER REGISTERS
    // CTA1EN disabled; CTA2EN disabled; CTA3EN disabled; CTA4EN disabled;
    CMBTRIGL = 0x00;
    // CTB3EN disabled; CTB2EN disabled; CTB1EN disabled; CTB4EN disabled;
    CMBTRIGH = 0x00;
    // CMBTRIGLbits.CTA1EN = 0; // Disable Trigger Output from PWM Generator #1 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA2EN = 0; // Disable Trigger Output from PWM Generator #2 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA3EN = 0; // Disable Trigger Output from PWM Generator #3 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA4EN = 0; // Disable Trigger Output from PWM Generator #4 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA5EN = 0; // Disable Trigger Output from PWM Generator #5 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA6EN = 0; // Disable Trigger Output from PWM Generator #6 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA7EN = 0; // Disable Trigger Output from PWM Generator #7 as Source for Combinational Trigger A
    // CMBTRIGLbits.CTA8EN = 0; // Disable Trigger Output from PWM Generator #8 as Source for Combinational Trigger A
    //
    // CMBTRIGHbits.CTB1EN = 0; // Disable Trigger Output from PWM Generator #1 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB2EN = 0; // Disable Trigger Output from PWM Generator #2 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB3EN = 0; // Disable Trigger Output from PWM Generator #3 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB4EN = 0; // Disable Trigger Output from PWM Generator #4 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB5EN = 0; // Disable Trigger Output from PWM Generator #5 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB6EN = 0; // Disable Trigger Output from PWM Generator #6 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB7EN = 0; // Disable Trigger Output from PWM Generator #7 as Source for Combinational Trigger B
    // CMBTRIGHbits.CTB8EN = 0; // Disable Trigger Output from PWM Generator #8 as Source for Combinational Trigger B

    // COMBINATORIAL PWM LOGIC A CONTROL REGISTERS A-F
//    LOGCONAbits.PWMS1A = 0b0000; // Combinatorial PWM Logic Source #1 Selection: PWM1H
//    LOGCONAbits.S1APOL = 0;      // Combinatorial PWM Logic Source #1 Polarity: Input is positive logic
//    LOGCONAbits.PWMS2A = 0b0010; // Combinatorial PWM Logic Source #2 Selection: PWM2H
//    LOGCONAbits.S2APOL = 0;      // Combinatorial PWM Logic Source #2 Polarity: Input is positive logic
//    LOGCONAbits.PWMLFA = 0b01;   // Combinatorial PWM Logic Function Selection: PWMS1y & PWMS2y (AND)
//    LOGCONAbits.PWMLFAD = 0b000; // Combinatorial PWM Logic Destination Selection: No assignment, combinatorial PWM logic function is disabled

    // Reset further combinatorial logic registers
    // PWMLFA PWMS1 or PWMS2;; S1APOL Positive logic; S2APOL Positive logic; PWMLFAD No Assignment; PWMS1A PWM1H; PWMS2A PWM1H;
    LOGCONA = 0x0000;
    LOGCONB = 0x0000; // LOGCONB: COMBINATORIAL PWM LOGIC CONTROL REGISTER B
    LOGCONC = 0x0000; // LOGCONC: COMBINATORIAL PWM LOGIC CONTROL REGISTER C
    LOGCOND = 0x0000; // LOGCOND: COMBINATORIAL PWM LOGIC CONTROL REGISTER D
    LOGCONE = 0x0000; // LOGCONE: COMBINATORIAL PWM LOGIC CONTROL REGISTER E
    LOGCONF = 0x0000; // LOGCONF: COMBINATORIAL PWM LOGIC CONTROL REGISTER F

    // PWM EVENT OUTPUT CONTROL REGISTERS A-F
    // PWMEVTAbits.EVTAOEN = 0;    // PWM Event Output Enable: Event output signal is internal only
    // PWMEVTAbits.EVTAPOL = 0;    // PWM Event Output Polarity: Event output signal is active-high
    // PWMEVTAbits.EVTASTRD = 0;   // PWM Event Output Stretch Disable: Event output signal is stretched to eight PWM clock cycles minimum
    // PWMEVTAbits.EVTASYNC = 0;   // PWM Event Output Sync: Event output is not synchronized to the system clock
    // PWMEVTAbits.EVTASEL = 0b0000; // PWM Event Selection: Source is selected by the PGTRGSEL[2:0] bits
    // PWMEVTAbits.EVTAPGS = 0b000;  // PWM Event Source Selection: PWM Generator 1

    // Reset further PWM event output registers
    PWMEVTA = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER A
    PWMEVTB = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER B
    // EVTASEL ADC trigger 2; EVTASYNC Not synchronized; EVTAPOL Active-high; EVTAPGS PG1; EVTASTRD Stretched to 8 PWM clock cycles minimum; EVTAOEN enabled; 
//    PWMEVTB = 0x8090;
//    // EVTBPGS PG2; EVTBSYNC Not synchronized; EVTBPOL Active-high; EVTBSEL ADC Trigger 1; EVTBSTRD Stretched to 8 PWM clock cycles minimum; EVTBOEN enabled; 
//    PWMEVTA = 0x8081;    
    PWMEVTC = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER C
    PWMEVTD = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER D
    PWMEVTE = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER E
    PWMEVTF = 0x0000;   // PWM EVENT OUTPUT CONTROL REGISTER F    
    
    
    /* init pwm 1 */
    // PWM GENERATOR x CONTROL REGISTERS
    // PG1CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    // PG1CONLbits.TRGCNT = 0b000; // Trigger Count Select: PWM Generator produces one PWM cycle after triggered
    // PG1CONLbits.HREN = 1; // High-Resolution mode is not enabled for PWM Generator 1
    // PG1CONLbits.CLKSEL = 0b01; // Clock Selection: PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    // PG1CONLbits.MODSEL = 0b000; // PWM Mode Selection: Independent Edge PWM mode
    PG1CONL = 0x0088;  // High-Resolution enabled, PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits, Edge PWM2H
    


    PG1CONHbits.MDCSEL = 0; // Master Duty Cycle Register Selection: PWM Generator uses PGxDC register
    PG1CONHbits.MPERSEL = 0; // Master Period Register Selection: PWM Generator uses MPER register
    PG1CONHbits.MPHSEL = 0; // Master Phase Register Selection: PWM Generator uses PGxPHASE register
    PG1CONHbits.MSTEN = 0; // Master Update Enable: PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    PG1CONHbits.UPDMOD = 0b001; // PWM Buffer Update Mode Selection: SOC
    PG1CONHbits.TRGMOD = 1; // PWM Generator Trigger Mode Selection: PWM Generator operates in Retriggerable mode
    PG1CONHbits.SOCS = 0; // Start-of-Cycle Selection: Local EOC, PWM Generator is self-triggered

    // ************************
    PG1IOCONLbits.CLMOD = 0;   // If PCI current limit is active, then the CLDAT[1:0] bits define the PWM output levels
    PG1IOCONLbits.SWAP = 0;    // Swap PWM Signals to PWMxH and PWMxL Device Pins: PWMxH/L signals are mapped to their respective pins
    PG1IOCONLbits.OVRENH = 1;  // User Override Enable for PWMxH Pin: OVRDAT1 provides data for output on the PWMxH pin
    PG1IOCONLbits.OVRENL = 1;  // User Override Enable for PWMxL Pin: OVRDAT0 provides data for output on the PWMxL pin
    PG1IOCONLbits.OVRDAT = 0b00; // Data for PWMxH/PWMxL Pins if Override Event is Active: PWMxL=OVRDAT0, PWMxH=OVRDAR1
    PG1IOCONLbits.OSYNC = 0b00; // User Output Override Synchronization Control: User output overrides via the OVRENH/L and OVRDAT[1:0] bits are synchronized to the local PWM time base (next Start-of-Cycle)

    PG1IOCONLbits.FLTDAT = 0b00; // Data for PWMxH/PWMxL Pins if Fault Event is Active: PWMxL=FLTDAT0, PWMxH=FLTDAR1
    PG1IOCONLbits.CLDAT = 0b00; // Data for PWMxH/PWMxL Pins if Current-Limit Event is Active: PWMxL=CLDAT0, PWMxH=CLDAR1
    PG1IOCONLbits.FFDAT = 0b00; // Data for PWMxH/PWMxL Pins if Feed-Forward Event is Active: PWMxL=CLDAT0, PWMxH=CLDAR1
    PG1IOCONLbits.DBDAT = 0b00; // Data for PWMxH/PWMxL Pins if Debug Mode Event is Active: PWMxL=DBDAT0, PWMxH=DBDAR1

    // PGxIOCONH: PWM GENERATOR x I/O CONTROL REGISTER HIGH
    // PG1IOCONHbits.CAPSRC = 0b000;  // Time Base Capture Source Selection: No hardware source selected for time base capture ? software only
    // PG1IOCONHbits.DTCMPSEL = 0; // Dead-Time Compensation Selection: Dead-time compensation is controlled by PCI Sync logic
    // PG1IOCONHbits.PMOD = 0b00; // PWM Generator Output Mode Selection: PWM Generator outputs operate in Complementary mode
    // PG1IOCONHbits.PENH = 0; // PWMxH Output Port Enable: GPIO registers TRISx, LATx, Rxx registers control the PWMxH output pin
    // PG1IOCONHbits.PENL = 0; // PWMxL Output Port Enable: GPIO registers TRISx, LATx, Rxx registers control the PWMxL output pin
    // PG1IOCONHbits.POLH = 0; // PWMxH Output Port Enable: Output pin is active-high
    // PG1IOCONHbits.POLL = 0; // PWMxL Output Port Enable: Output pin is active-high
    PG1IOCONH = 0x0000;

    // PWM GENERATOR x STATUS REGISTER
    PG1STAT = 0x0000;   // Reset to default

    // PWM GENERATOR x EVENT REGISTER LOW
    PG1EVTLbits.ADTR1PS     = 0b00001;      // ADC Trigger 1 Postscaler Selection = 1:2 
    PG1EVTLbits.ADTR1EN3    = 0b0;          // PG1TRIGC  Compare Event is disabled as trigger source for ADC Trigger 1
    PG1EVTLbits.ADTR1EN2    = 0b1;          // PG1TRIGB  Compare Event is  enabled as trigger source for ADC Trigger 1
    PG1EVTLbits.ADTR1EN1    = 0b0;          // PG1TRIGA  Compare Event is disabled as trigger source for ADC Trigger 1
    PG1EVTLbits.UPDTRG      = 0b10;         // PG1phase triggers update 
    PG1EVTLbits.PGTRGSEL    = 0b001;        // PGxTRIGA compare event is the PWM Generator trigger

    // PWM GENERATOR x EVENT REGISTER HIGH
    PG1EVTHbits.FLTIEN      = 0b0;          // PCI Fault interrupt is disabled
    PG1EVTHbits.CLIEN       = 0b0;          // PCI Current-Limit interrupt is disabled
    PG1EVTHbits.FFIEN       = 0b0;          // PCI Feed-Forward interrupt is disabled
    PG1EVTHbits.SIEN        = 0b0;          // PCI Sync interrupt is disabled
    PG1EVTHbits.IEVTSEL     = 0b11;         // Time base interrupts are disabled
    PG1EVTHbits.ADTR2EN3    = 0b0;          // PG1TRIGC register compare event is disabled as trigger source for ADC Trigger 2
    PG1EVTHbits.ADTR2EN2    = 0b0;          // PG1TRIGB register compare event is disabled as trigger source for ADC Trigger 2
    PG1EVTHbits.ADTR2EN1    = 0b1;          // PG1TRIGA register compare event is  enabled as trigger source for ADC Trigger 2
    PG1EVTHbits.ADTR1OFS    = 0b00000;      // ADC Trigger 1 offset = No offset
//    PG1EVTH = 0x0300;

    // Reset further PCI control registers
    PG1CLPCIH       = 0x0000;          // PWM GENERATOR CL PCI REGISTER HIGH (not used)
    PG1CLPCIL       = 0x0000;          // PWM GENERATOR CL PCI REGISTER LOW  (not used)
    PG1FPCIH        = 0x0000;          // PWM GENERATOR F  PCI REGISTER HIGH (not used)
    PG1FPCIL        = 0x0000;          // PWM GENERATOR F  PCI REGISTER LOW  (not used)
    PG1FFPCIH       = 0x0000;          // PWM GENERATOR FF PCI REGISTER HIGH (not used)
    PG1FFPCIL       = 0x0000;          // PWM GENERATOR FF PCI REGISTER LOW  (not used)
    PG1SPCIH        = 0x0000;          // PWM GENERATOR S  PCI REGISTER HIGH (not used)
    PG1SPCIL        = 0x0000;          // PWM GENERATOR S  PCI REGISTER LOW  (not used)

    // PWM GENERATOR x LEADING-EDGE BLANKING REGISTER HIGH/LOW
    PG1LEBH     = 0x0000;   // Leading Edge Blanking not used
    PG1LEBL     = 0x0000;   // Leading Edge Blanking not used

    // PGxPHASE: PWM GENERATOR x PHASE REGISTER
    PG1PHASE    = PWM_PERIOD;

    // PGxDC: PWM GENERATOR x DUTY CYCLE REGISTER
    PG1DC       = PWM_PERIOD;

    // PGxDCA: PWM GENERATOR x DUTY CYCLE ADJUSTMENT REGISTER
    PG1DCA      = 0x0000;

    // PGxPER: PWM GENERATOR x PERIOD REGISTER
    PG1PER      = PWM_PERIOD;   

    // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PG1TRIGA    = (PWM_PERIOD >> 1); //(DUTY_FIXED >> 1);

    // PGxTRIGB: PWM GENERATOR x TRIGGER B REGISTER
    PG1TRIGB    = (PWM_PERIOD >> 1) - (DUTYMAX >> 1) + ADC_TRIG_OFFSET;

    // PGxTRIGC: PWM GENERATOR x TRIGGER C REGISTER
    PG1TRIGC    = 0;

    // PGxDTL: PWM GENERATOR x DEAD-TIME REGISTER LOW
    PG1DTL      = PWM_DEAD_TIME_FE;

    // PGxDTH: PWM GENERATOR x DEAD-TIME REGISTER HIGH
    PG1DTH      = PWM_DEAD_TIME_RE;    
    
    /* init pwm 2 */
    // PWM GENERATOR x CONTROL REGISTERS
    // PWM GENERATOR x CONTROL REGISTERS
    // PG2CONLbits.ON = 0; // PWM Generator #1 Enable: PWM Generator is not enabled
    // PG2CONLbits.TRGCNT = 0b000; // Trigger Count Select: PWM Generator produces one PWM cycle after triggered
    // PG2CONLbits.HREN = 1; // High-Resolution mode is not enabled for PWM Generator 1
    // PG2CONLbits.CLKSEL = 0b01; // Clock Selection: PWM Generator uses Master clock selected by the MCLKSEL[1:0] (PCLKCON[1:0]) control bits
    // PG2CONLbits.MODSEL = 0b000; // PWM Mode Selection: Independent Edge PWM mode
    PG2CONL = 0x0088;

    PG2CONHbits.MDCSEL = 0; // Master Duty Cycle Register Selection: PWM Generator uses PGxDC register
    PG2CONHbits.MPERSEL = 0; // Master Period Register Selection: PWM Generator uses MPER register
    PG2CONHbits.MPHSEL = 0; // Master Phase Register Selection: PWM Generator uses PGxPHASE register
    PG2CONHbits.MSTEN = 0; // Master Update Enable: PWM Generator does not broadcast the UPDREQ status bit state or EOC signal
    PG2CONHbits.UPDMOD = 0b001; // PWM Buffer Update Mode Selection: Slaved SOC update
    PG2CONHbits.TRGMOD = 1; // PWM Generator Trigger Mode Selection: PWM Generator operates in Retriggerable mode
    PG2CONHbits.SOCS = 0b0001; // Start-of-Cycle Selection: Trigger output selected by PG1


    PG2IOCONL = PG1IOCONL;
    PG2IOCONH = PG1IOCONH;
    PG2STAT   = PG1STAT;
    
    PG2EVTLbits.ADTR1PS     = 0b00001;      // ADC Trigger 1 Postscaler Selection = 1:2 
    PG2EVTLbits.ADTR1EN3    = 0b0;          // PG2TRIGC  Compare Event is disabled as trigger source for ADC Trigger 1
    PG2EVTLbits.ADTR1EN2    = 0b0;          // PG2TRIGB  Compare Event is disabled as trigger source for ADC Trigger 1
    PG2EVTLbits.ADTR1EN1    = 0b1;          // PG2TRIGA  Compare Event is  enabled as trigger source for ADC Trigger 1
    PG2EVTLbits.UPDTRG      = 0b10;         // PG2PHASE triggers update 
    PG2EVTLbits.PGTRGSEL    = 0b000;        // PGxTRIGA compare event is the PWM Generator trigger   
    
    PG2EVTH   = 0x0000;//PG1EVTH;
    
    PG2CLPCIH = PG1CLPCIH;
    PG2CLPCIL = PG1CLPCIL;
    PG2FPCIH  = PG1FPCIH;
    PG2FPCIL  = PG1FPCIL;
    PG2FFPCIH = PG1FFPCIH;
    PG2FFPCIL = PG1FFPCIL;
    PG2SPCIH  = PG1SPCIH;
    PG2SPCIL  = PG1SPCIL;
    PG2LEBH   = PG1LEBH;
    PG2LEBL   = PG1LEBL;
    PG2PHASE  = PG1PHASE;
    PG2DC     = PG1DC;
    PG2DCA    = PG1DCA;
    PG2PER    = PG1PER;
    // PGxTRIGA: PWM GENERATOR x TRIGGER A REGISTER
    PG2TRIGA  = (PWM_PERIOD >> 1) - (DUTYMAX >> 1);//ADC_TRIG_OFFSET; //(DUTY_FIXED >> 1);    
    PG2TRIGB  = PG1TRIGB;
    PG2TRIGC  = PG1TRIGC;
    PG2DTL    = PG1DTL;
    PG2DTH    = PG1DTH;    
    
    return (1);
}

volatile uint16_t LaunchPWM(void) {

    volatile uint16_t timeout=0;

    PG1CONLbits.ON = 1; // PWM Generator #1 Enable: PWM Generator is enabled
    PG2CONLbits.ON = 1; // PWM Generator #2 Enable: PWM Generator is enabled

    while((!PCLKCONbits.HRRDY) && (!PCLKCONbits.HRERR) && (timeout++ < 8000)); // Wait for READY bit

    if(timeout >= 8000) // if High Resolution Ready Bit has not been set or error occurred
    { return(0); }      // skip ENABLE and return failure code

    PG1STATbits.UPDREQ = 1; // Update all PWM registers of PG1
    PG2STATbits.UPDREQ = 1; // Update all PWM registers of PG2

    while(((PG1STATbits.UPDATE) || (PG2STATbits.UPDATE)) && (timeout++<8000));

//    PG1IOCONHbits.PENH = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxH output pin
//    PG1IOCONHbits.PENL = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxL output pin
//    PG2IOCONHbits.PENH = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxH output pin
//    PG2IOCONHbits.PENL = 1; // PWMxH Output Port Enable: PWM generator controls the PWMxL output pin
//
//    // SAFE, GLITCH-FREE STARTUP AS OVERRIDE LOGIC IS SYNCHRONIZED BY EOC
//    PG1IOCONLbits.OVRENH = 0;  // User Override Enable for PWMxH Pin: User override disabled
//    PG1IOCONLbits.OVRENL = 0;  // User Override Enable for PWMxL Pin: User override disabled
//    PG2IOCONLbits.OVRENH = 0;  // User Override Enable for PWMxH Pin: User override disabled
//    PG2IOCONLbits.OVRENL = 0;  // User Override Enable for PWMxL Pin: User override disabled

    return(1);

}