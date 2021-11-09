/*
 * main3.c
 *
 *  Created on: Oct 25, 2021
 *  Q1. Using WDT timer interrupt process, Toggle your RED and Green LED with 256msec interval on.
 *      Author: jochyperez
 */


#include <msp430.h>
#include <stdio.h>

#include "msp430G2553.h"

#define RedLED BIT6
#define GreenLED BIT0
#define ToggleLeds (P1OUT ^= RedLED | GreenLED)
#define Button BIT3
void main(void)
{
     BCSCTL2 |= DIVS_3;     // divide clock by 8
     WDTCTL  = WDT_MDLY_32; // set watch dog in timer mode
     IE1 |= WDTIE;          // enables interrupt
     P1DIR = RedLED | GreenLED; // sets as output mode
     P1OUT = RedLED;            // initially turns on red led
     _enable_interrupt();       // enables interrupt
     LPM1;

}

#pragma vector = WDT_VECTOR
__interrupt void WDT(void){

    P1OUT = ToggleLeds;
}

