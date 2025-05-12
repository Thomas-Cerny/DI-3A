#include "p33EV32GM002.h"

_FOSCSEL(FNOSC_FRC) 
_FOSC(OSCIOFNC_ON & IOL1WAY_OFF) _FWDT(FWDTEN_OFF) 

/* 
* UKOL 8: 
* GENERUJ NAPETI 3,2V POMOCI SPI 
* propojit RB8 -> RB5, RB6 -> RB7 
* multimetr na CA a GND 
*/

int a;

int main() 
{ 
    TRISB = 0x0060;
    ANSELB = 0;

    PR2 = 28346;
    T2CON = 0x8030; 

    a = SPI1BUF; 
    SPI1STAT = 0x0000; 
    SPI1CON1 = 0x0520; // 0000 0101 0010 0000
    SPI1CON2 = 0; 
    SPI1STATbits.SPIROV = 0; 
    SPI1STATbits.SPIEN = 1; 

    IEC0bits.T2IE = 1; 
    IEC0bits.SPI1IE=1; 
    INTCON2bits.GIE = 1; 

    while (1) 
    { 
       asm("NOP"); 
    } 
} 

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) 
{ 
    IFS0bits.T2IF = 0; 
    PORTBbits.RB13 = 0; 
    a = SPI1BUF; // prvni cislo voli jestli je vystup na CA a CB, dalsi 3 napeti SPI1BUF = 0x1ff8; 
} 

void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void) 
{ 
    IFS0bits.SPI1IF = 0; 
    PORTBbits.RB13 = 1; 
}