/*
* 1. ULOHA: KOPIRUJ DATA Z PORTUA NA PORTB
* RA (PORTA) RA0-4
* RB (PORTB) RB0-15
*/

#include "p33EV32GM002.h"

_FOSCSEL ( FNOSC_FRC )
_FOSC ( OSCIOFNC_ON & IOL1WAY_OFF )
_FWDT ( FWDTEN_OFF )

int main()
{
    ANSELA = ANSELB = 0;
    TRISA = 0x0001;
    TRISB = 0x8001;
    CNPUA = 0x0001;
    CNPDB = 0x8000;

    while (1)
    {
        PORTAbits.RA2 = PORTAbits.RA0;
        PORTBbits.RB14 = PORTBbits.RB0;
        PORTAbits.RA1 = PORTBbits.RB15;

        asm("NOP");
    }
}