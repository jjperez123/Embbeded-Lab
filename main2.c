

#include <msp430.h>
#include <stdio.h>

#include "msp430G2553.h"
void main(void)
{
     WDTCTL = WDTPW + WDTHOLD;
    P1DIR |= BIT6;                       // P1.6 to output
    TA0CTL = TASSEL_2 + MC_1+ID_3+TACLR; // Use the SMCLK to clock the counter and set to count up mode, divider by 8
    TA0CCR0 = 31249;                     // Set maximum count value (PWM Period)
    TA0CCR1 = 6250;                      // initialise counter compare value
    TA0CCTL0 |= CCIE;                    // enabling capture and compare interrupt
    TA0CCTL1 |= CCIE;                    // enabling 4capture and compare interrupt
    TA0CCTL0 &=~CCIFG;
    TA0CCTL1 &=~CCIFG;
    _enable_interrupts();
}
#pragma vector = TIMER0_A0_VECTOR       //define the interrupt service vector
__interrupt void TA0_ISR (void)    // interrupt service routine
{
P1OUT |=BIT6;
TA0CCTL0 &=~CCIFG;
}
#pragma vector = TIMER0_A1_VECTOR       //define the interrupt service vector
__interrupt void TA1_ISR (void)    // interrupt service routine
{
P1OUT &=~BIT6;
TA0CCTL1 &=~CCIFG;
}
