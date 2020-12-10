![image](images/microchip.jpg) 

## EPC9148 Ultra-Thin 250 W 48 V Three-Level Synchronous Buck Converter - Average Current Mode Control Firmware
**2-Phase Synchronous Buck Converter with Advanced Voltage Mode Control and Current Balancing**

<p>
  <center>
    Top View <br>
    <img src="images/9148_top.png" alt="EPC9148 Top View" width="300">
  </center>
</p>

## Summary
This code example demonstrates a closed loop average current mode control implementation for dsPIC33CK. It has specifically been developed for the EPC9148 3-Level buck converter reference design.

The board starts up the buck converter automatically when power is applied to the board, providing a regulated output voltage of 12 V at the output of the converter. The startup procedure is controlled and executed by the power controller state machine and includes an configurable startup procedure with power-on delay, ramp up period and power good delay before dropping into constant regulation mode.
An additional fault handler routine continuously monitors incoming ADC data and peripheral status bits and shuts down the power supply if the input voltage is outside the defined maximum range of 16.5 V to 62.5 V (UVLO/OVLO) or if the output voltage is more than 0.5 V out of regulation for more than 10 milliseconds.

A single, high-speed type IV (4P4Z) voltage mode controller with enforced PWM steering is used to automatically create balanced phase currents in both phases of this interleaved converter. An underlying current balancing scheme compensates component tolerances and deviations over temperature. A built-in adaptive gain control algorithm stabilizes gain variations of the voltage loop controller during input- and output voltage transients, stabilizing cross-over frequency and output impedance, supporting control bandwidths of 25 kHz, for improved transient response, helping to minimize power distribution network (PDN) decoupling capacity.

#### Product Features:
  - Input Voltage: 42 V to 64 V
  - Output Voltage: 5 ... 20 V DC (12 V default setting)
  - Switching Frequency: 400 kHz
  - Control Frequency: 400 kHz
  - Cross-Over Frequency: ~10 kHz (depends on VIN and if AGC is on/off)
  - Phase Margin: ~ 50°
  - Gain Margin: ~ 12 dB

## Related Documentation
##### Firmware Documentation
  - TODO[EPC9148 Online Firmware Documentation](https://microchip-pic-avr-examples.github.io/epc9148-power-3level-buck-acmc)

##### Firmware Documentation
  - [EPC9148 48V Three-level Synchronous Buck Converter Reference Design Product Website](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EPC9148)
  - [EPC9148 Reference Design Quick Start Guide (QSG)](https://epc-co.com/epc/documents/guides/EPC9148_qsg.pdf)
  - [EPC9148 Reference Design Schematics](https://epc-co.com/epc/documents/schematics/EPC9148_Schematic.pdf)
  
## Software Used 
  - [MPLAB® X IDE v5.40](https://www.microchip.com/mplabx-ide-windows-installer)
  - [MPLAB® XC16 Compiler v1.50](https://www.microchip.com/mplabxc16windows)
  - [PowerSmart&trade; - Digital Control Library Designer, v0.9.12.642 (Pre-Release Version)](https://areiter128.github.io/DCLD/)


## Hardware Used
The EPC9148 3-level synchronous buck converter module provides all required interfaces to program and debug the dsPIC33CK32MP102 DSC as well as test points and banana jack connectors for easy and safe handling of the kit during bench tests. The EPC9148 QSG provides detailed operating procedure instructions.


## Device Support:
Microchip devices used in this reference design:
  - [dsPIC33CK32MP102](https://www.microchip.com/dsPIC33CK32MP102)
  - [MCP6C02 Shunt Amplifier](https://www.microchip.com/MCP6C02)

EPC devices used in this reference design
  - [EPC2038: 100 V, 246 A Enhancement-Mode GaN Power Transistor](https://epc-co.com/epc/Products/eGaNFETsandICs/EPC2038.aspx)

## Setup
The board comes programmed and ready to be used when unpacked. No reprogramming of the target device is required to operate the board unless features or settings such as the nominal output voltage or start-up timing need to be modified. 

<p>
  <center>
    <a href="https://www.microchip.com/EPC9148" rel="nofollow">
      <img src="images/9148_top_setup.png" alt="EPC9148 Test Connections - Top View" width="620">
	</a>
  <br>
  EPC9148 Test Connections - Top View
  </center>
</p>

<p>
  <center>
    <a href="https://www.microchip.com/EPC9148" rel="nofollow">
      <img src="images/9148_bottom_setup.png" alt="EPC9148 Test Connections - Bottom View" width="620">
	</a>
  <br>
  EPC9148 Test Connections - Bottom View
  </center>
</p>

<p>
  <center>
    <a href="https://www.microchip.com/EPC9148" rel="nofollow">
      <img src="images/9148_connectors.png" alt="EPC9148 Measurement Connection" width="680">
	</a>
  <br>
  EPC9148 Measurement Connection
  </center>
</p>

In case firmware based features need to be changed, the Microchip dsPIC33CK controller can be re-programmed using the in-circuit serial programming port (ICSP) available on the RJ-11 programming interface as well as the 6-pin header. A ribbon cable is needed to connect the programming kit and the EPC9148. These interfaces support all of Microchip’s in-circuit programmers/debuggers, such as MPLAB® ICD4, MPLAB® REAL ICE or MPLAB® PICkit4 and previous derivatives. See [EPC9148 Quick Start Guide](https://epc-co.com/epc/documents/guides/EPC9148_qsg.pdf) for details.



## Operation
The converter is starting up automatically when more than 16.6 V DC are applied across the input terminals of the EPC9148.  Please read the [EPC9148 Quick Start Guide](https://epc-co.com/epc/documents/guides/EPC9148_qsg.pdf) to get detailed information about the requirements for setup and operation of this reference design.

## Firmware Quick-Start Guide

##### 1) Buck Converter State Machine

The state machine goes through the following steps in chronological order:

a) Initialization

In this step the control loop parameters are reset to their defaults, PWM outputs are turned off but the PWM is still running, continuously triggering the ADC to keep sampling input and output voltage as well as board temperature.

b) Reset
This is the 'fall-back' state from which the buck converter will be restarted once it has been started successfully and has been shut down due to a fault condition (e.g. input under/over voltage or over temperature condition)

c) Standby
After RESET, the state machine waits for all fault flags to be cleared and the enable and GO bits to be set.

d) Power-On Delay (POD)
Once the buck converter has been cleared the state machine will execute the startup procedure starting with the Power On Delay. This is just a simple delay during which the converter will remain inactive but the fault handler will observe the values generated by the ADC for occurring fault conditions.

e) Launch Voltage Ramp
After the Power-On delay has expired, input and output voltage will be measured. In case the converter output is pre-biased (voltage = non-zero), the power controller will be 'pre-charged' with an artificial control history and PWM output to softly ramp up the output voltage from its most recent level. 

f) Voltage Ramp-Up
Now the digital feedback loop and PWM are enabled and the closed loop system reference value is incremented with every execution of the state machine (100 µsec interval). The control loop has been adjusted to operate with a cross-over frequency of >10 kHz matching the maximum perturbation frequency allowed to keep the control system stable.  

g) Power Good Delay
After the reference voltage has been increased to the pre-defined nominal level, the state machine switches over into the Power Good Delay period. This is another, simple delay where the control loop is in steady state waiting for the delay period to expire.

h) Online
After the Power Good Delay has expired, the converter drops into nominal operation. In this condition it continuously observes the reference value for changes. Should any other part of the firmware change the controller reference, the state machine will softly tune into the new level instead of hard-switching the reference. 

i) Suspend/Error
If the power controller is shut down and reset by external commands (e.g. fault handler detecting a fault condition or through user-interaction), the state machine is switching into the SUSPEND state, which disables the PWM outputs and control loop execution, clears the control histories and resets the state machine back to RESET

##### 2) Cycle-by-Cycle Voltage Control Loop

This firmware uses a digital type IV controller to close the feedback loop in voltage mode control. This digital loop reads the most recent ADC sample of the output voltage and processes the derived value through a digital type IV (4P4Z) compensation filter. The numeric output is checked and, when necessary, clamped to user-defined minimum/maximum thresholds before being written to the PWM duty cycle register. As EPC9143 is a multiphase converter, a special PWM steering mode has been implemented supporting high-speed current balancing between the two phases. The voltage mode controller has been extended with a self-adapting loop gain tuning algorithm (AGC) stabilizing the frequency domain characteristic over input voltage, output voltage and load, always providing the exact same bandwidth of >25 kHz and stability margins across the entire operating range.

<p>
  <center>
    <a href="https://www.microchip.com/EPC9148" rel="nofollow">
      <img src="images/EPC9148_three_level_control_system.JPG" alt="EPC9148 three level control system" width="800">
	</a>
  <br>
  EPC9148 three level control system
  </center>
</p>

This control loop can be turned on/off by using the ENABLE bit in the STATUS word of the cNPNZ_t controller data structure. The adaptive loop gain modulation is permanently active as soon as the control loop is enabled.

##### 3) Digital Controller Design

The control loop source code is configured and generated by the PowerSmart&trade; - Digital Control Library Designer (DCLD) software.

This additional design software is available for download on Github Pages:

  - [PowerSmart&trade; Digital Control Library Designer Github Page](https://areiter128.github.io/DCLD)

Once installed, the controller configuration can be modified. The most recent configuration can be opened from within the MPLAB X® IDE by right-clicking on the file 'DPSK3_VMC.dcld' located in the Important Files folder of the Project Manager. When right-clicked, select 'Open In System' to open the configuration in PowerSmart&trade; DCLD. 

Please refer to the user guide of PowerSmart&trade; DCLD which is included in the software and can be opened from the help menu of the application.

##### 4) User Control

No user control interface has been added to the firmware. Any change to the firmware and fundamental operation of the reference design, including reprogramming of the nominal output voltage can be done by editing the hardware-specific values in the hardware description header file 'epc9148_r40_hwdescr.h' located in 'Project Manager => Header Files/Config'

Converter settings in this file are defined as physical values such as Volt, Ampere, Ohm, etc. Each defined value is converted into binary numbers by so-called macros, at compile time. Thus, users do not have to convert values manually.

##### Example:
To program the converter to provide a nominal output voltage different from the 12 V DC set by default, follow these steps:

  - Open the project in MPLAB X® IDE
  - Navigate to 'Header Files/Config/epc9148_r40_hwdescr.h' using the Project Manager on the left of the main window
  - Go to line #325 (see below)
  - Change the give settings as desired
  - Build the program
  - Remove power from the input of the EPC9148 board
  - Connect a valid ICSP programming device (e.g. MPLAB ICD4, MPLAB PICkit4) to the PC and the EPC9148 board
  - Program the device with the target device being powered by the debugger/programmer
  - Disconnect the ICSP programming device from the EPC9148
  - Apply valid input voltage across the input terminals of EPC9148 and observe the output of the EPC9148 reference design

The setting for the nominal output voltage is found in lines #324 through #326.

    #define BUCK_VOUT_NOMINAL           (float)12.000  // Nominal output voltage
    #define BUCK_VOUT_TOLERANCE_MAX     (float)0.500   // Output voltage tolerance [+/-]
    #define BUCK_VOUT_TOLERANCE_MIN     (float)0.100   // Output voltage tolerance [+/-]

###### Please note:
The tolerance settings above include the transient response at a maximum load step. The value for maximum output voltage tolerance 'BUCK_VOUT_TOLERANCE_MAX' is observed by the fault handler. Should the output voltage reading divert from the most recent reference voltage value by more than the given range, the converter will be shut down and a REGULATION ERROR will be indicated. The power supply will automatically recover as soon as the fault condition has been cleared and the recover delay period specified by BUCK_REGERR_RECOVERY_DELAY in line #527 of the EPC9148 hardware description header file has expired.

(line numbers given may be subject to change)

##### 5) Power Plant Measurement Support

This code examples includes an alternative, proportional control loop which is commonly used during measurements of the frequency response of the power plant. When the following define is set to TRUE, the common main control loop is replaced by the proportional controller.

    app_power_control.c, line 33:   #define PLANT_MEASUREMENT   false


###### PLEASE NOTE:
PROPORTIONAL CONTROLLERS ARE BY DEFAULT UNSTABLE AND NOT SUITED TO REGULATE THE OUTPUT OF A POWER SUPPLY UNDER NORMAL OPERATING CONDITIONS. DURING A PLANT MEASUREMENT IT IS MANDATORY THAT INPUT VOLTAGE AND LOAD REMAIN STABLE AND DO NOT CHANGE. 

FOR MORE INFORMATION ABOUT HOW TO CONDUCT A POWER PLANT MEASUREMENT, PLEASE READ THE SECTIONS IN THE PowerSmart&trade; DCLD USER GUIDE.

_________________________________________________
(c) 2020, Microchip Technology Inc.

