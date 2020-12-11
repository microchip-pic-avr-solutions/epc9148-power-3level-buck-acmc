# epc9148-power-3level-buck-acmc, release v1.0.0

### Release Highlights
Robust initial release for the EPC9148 250W Ultra-Thin 48V 3-Level Synchronous Buck Converter Reference Design running in average current mode control with flying capacitor voltage balancing achieving 97.8% peak efficiency.

### Features Added\Updated
This code example demonstrates an average current mode control with additional flying capacitor voltage balancing implementation for dsPIC33CK. It has specifically been developed for the EPC9148 Ultra-Thin Three-Level Synchronous Buck Converter Reference Design.

##### Technical Data
  - Input Voltage: 42 V to 64 V
  - Output Voltage: 5 ... 20 V DC (12 V default setting)
  - Switching Frequency: 400 kHz
  - Control Frequency: 400 kHz
  - Inductor Ripple Frequency: 800 kHz
  - Cross-Over Frequency: ~9 kHz (depends on VIN and if AGC is on/off)
  - Phase Margin: ~ 60°
  - Gain Margin: ~ 9 dB

##### Fault Monitor
  - Regulation Error Detection (RED)
  - Over Current Protection (OCP)
  - Over Temperature Protection (OTP)


