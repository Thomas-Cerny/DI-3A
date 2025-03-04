/*
* 3. ULOHA: GENERUJ OBD. SIGNALY (PRERUSENI)
* 1) 1KHZ
* 2) 1KHZ
*    500HZ
*    250HZ
*    125HZ
*/

#include <p33EV32GM002.h>

_FOSCSEL( FNOSC_FRC )
_FOSC( OSCIOFNC_ON & IOL1WAY_OFF)
_FWDT( FWDTEN_OFF )

int main()
{
    ANSELA = ANSELB = 0;
    TRISA = TRISB = 0;
    PR2 = 1842;
    PR3 = 3685;
    PR4 = 7370;
    PR5 = 14740;
    T2CON = T3CON = T4CON = T5CON = 0x8000;

    INTCON2bits.GIE = 1;
    IEC0bits.T2IE = IEC0bits.T3IE = 1;
    IEC1bits.T4IE = IEC1BITS.T5IE = 1;

    while (1)
    {
        asm("NOP");
    }
}

void __attribute__ ((interrupt, auto_psv)) _T2Interrupt(void)
{
    IFS0bits.T2IF = 0;
    PORTAbits.RA4 = !PORTAbits.RA4;
}

void __attribute__ ((interrupt, auto_psv)) _T3Interrupt(void)
{
    IFS0bits.T3IF = 0;
    PORTAbits.RA1 = !PORTAbits.RA1;
}

void __attribute__ ((interrupt, auto_psv)) _T4Interrupt(void)
{
    IFS1bits.T4IF = 0;
    PORTAbits.RA2 = !PORTAbits.RA2;
}

void __attribute__ ((interrupt, auto_psv)) _T5Interrupt(void)
{
    IFS1bits.T5IF = 0;
    PORTAbits.RA3 = !PORTAbits.RA3;
}