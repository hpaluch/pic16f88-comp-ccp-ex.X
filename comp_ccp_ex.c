/*
 * File:   comp_ccp_ex.c - advanced demo - measuring non-wave frequency
 *                         using Comparator and CCP
 * DevKit: DM163045 - PICDEM Lab Development Kit
 *    MCU: PIC1688 PDIP
 * SW: MPLAB X IDE v5.45, XC8 v2.32, DFP 1.2.33
 * 
 * Current function - milestone 2:
 * - 3 Short LED flashes on RA3 PIN2 using TMR0 IRQ
 * - one flash is 64ms ( maximum TMR0 perios : 256 * 256 / 1_000_000 = 0.065 s
 * - 1 MHz f_cy (CLK/4) out on RA6/OSC2/CLK0 PIN 15
 * 
 * Circuit:
 *                       
 *                LED   470R
 * RA3 PIN2 ------|<|--|==|-- +5V
 * 
 * RA6 PIN15 -- f_osc/4 = 1 MHz ---> to scope/f_meter
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
#ifndef __DEBUG
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled fo debug)
#else
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#endif
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON        // Low-Voltage Programming Enable bit ON
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

// use "LATch" variable to avoid read-modify-write problems etc.
volatile unsigned char vLATA = ~0;


void flash_LED(void)
{
    // flash LED will set LED on, reset TMR0 and enable TMR0
    // later TMR0_ISR will set LED off and disable TMR0
    TMR0 = 0;NOP();NOP();NOP();TMR0=0;
    // use negative logic
    vLATA = vLATA & ~iLED_MASK;
    PORTA = vLATA;
}

// mostly copy and paste from 
// https://microchipdeveloper.com/projects:mcu1101-project-6
// NOTE: PIC16F88 has single interrupt handler, so we must
//       find who cause interrupt...
void __interrupt() INTERRUPT_InterruptManager (void)
{
    if (INTCONbits.TMR0IF){
        // turn off LED (negative logic)
        vLATA = vLATA | iLED_MASK;
        PORTA = vLATA;
        INTCONbits.TMR0IF = 0; // must ACK interrupt
    }
    // later we will use also Comparator interrupt etc...
}

void main(void) {

    // initialize PINs as soon as possible
    PORTA = vLATA;
    TRISA = ~iLED_MASK; // only our LED set as output
    PORTA = vLATA; // ensure that values are really set
    ANSEL = 0; // disable all analog inputs => enable digital I/O

    OSCCONbits.IRCF = 0b110;    // f = 4 MHz => 1 MHz instruction clock
    // wait until OSC is stable, otherwise we will screw up 1st
    // call of __delay_ms() !!! it will be much slower then expected!!
    while(OSCCONbits.IOFS == 0){/*nop*/};
    vLATA ^= iLED_MASK;
    PORTA = vLATA; // toggle LEDs to signal that OSC is stable and running

    // setup TMR0
    CLRWDT();
    // nRBPU_MASK =1 - pull-ups disabled, 
    // T0CS = 0 - use instruction clock, PSA = 0, prescaler to TMR0
    // PS_MASK = 7 - prescaler 1:256 (max))
    OPTION_REG = _OPTION_REG_nRBPU_MASK | _OPTION_REG_PS_MASK;
    TMR0 = 0;
    // Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;
    // Enabling TMR0 interrupt.
    INTCONbits.TMR0IE = 1;
    // globally enable interrupts
    INTCONbits.GIE = 1;
    
    while(1){
        unsigned char i;
        // 3 quick flashes
        for(i=0;i<3;i++){
            flash_LED();
            __delay_ms(300);            
        }
        // followed by longer pause
        __delay_ms(2000);
    }
    return;
}
