/*
 * File:   globals.c
 * Author: M91406.LA
 *
 * Created on November 2, 2019, 4:52 PM
 */


#include <xc.h>
#include "npnz16b.h"

volatile uint16_t vin_adc, vout_adc, iout_adc, v_ref, i_ref, duty_out, v_cfly, v_cfly_ref, deltaD_offset, i_loop2_out;
volatile uint16_t i_trigger, v_trigger;
volatile int16_t temperature_adc;
volatile int16_t vcfly[2];
volatile int16_t v_loop_POSB_load, v_loop_POSB_noload;

volatile int16_t e_cfly, sum_e_cfly, e_neg, e_pos, e20_n1, e20_n2;
volatile uint16_t v_loop_error, v_loop_only_error;
volatile int16_t deltaDQ2;
//volatile int16_t maxdeltaDpos, maxdeltaDneg;
volatile int16_t systemstate, systemstateprevious, controlstate;
volatile int16_t statechanged;
volatile int16_t newadcavailable;
volatile int16_t numberofphases;
volatile int16_t mscounter;
volatile int16_t deltaD;
volatile int16_t rx_count;
volatile int16_t tx_count, low_iout_count;
volatile int16_t pwm2_count;
volatile uint8_t command_int8;
volatile int16_t deltaDmax;
volatile extern cNPNZ16b_t v_loop, i_loop, pi_vcfly, v_loop_only;

