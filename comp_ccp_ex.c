/*
 * File:   comp_ccp_ex.c - advanced demo - measuring non-wave frequency
 *                         using Comparator and CCP
 * DevKit: DM163045 - PICDEM Lab Development Kit
 *    MCU: PIC1688 PDIP
 * SW: MPLAB X IDE v5.45, XC8 v2.32, DFP 1.2.33
 * 
 * Current function - milestone 1:
 * - Blinking LED on RA3 PIN1
 * - 4 MHz clock out on RA6/OSC2/CLK0 PIN 15
 * 
 * Created on May 29, 2021, 11:35 AM
 */

#define  _XTAL_FREQ 4000000 // f_osc (4MHz) for __delay_ms();)
#include <xc.h>


// CONFIG1 and 2 mostly generated from:
// Window -> Target Memory Views -> Configuration Bits
// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#ifdef __DEBUG
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT disabled fo debug)
#else
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#endif
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

// My I/O ports
#define iLED_MASK  _PORTA_RA3_MASK

// show to user which mode is compiled
#ifdef __DEBUG
#warning Build in Debug mode
#else
#warning Build in Production (Run) mode
#endif
 

void main(void) {

    OSCCONbits.IRCF = 0b110;    // f = 4 MHz => 1 MHz instruction clock
    PORTA = 0;
    TRISA = ~iLED_MASK;
    ANSEL = 0; // disable all analog inputs => enable digital I/OI/O
    while(1){
        __delay_ms(100);
        PORTA = ~PORTA;
    }
    return;
}
