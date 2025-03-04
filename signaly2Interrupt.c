/*
* 5. ULOHA: GENERUJ SIGNALY:
* 1) 2KHZ POKUD JE LOG. 1 NA RA0
* 2) 2KHZ POKUD JE LOG. 1 NA RA0
*    1KHZ -> RA1
*    500HZ -> RA2
*    250HZ -> RA3
*/

// Generuje signaly na RB0 - RB3

#include <p33EV32GM002.h>

_FOSCSEL( FNOSC_FRC )
_FOSC( OSCIOFNC_ON & IOL1WAY_OFF)
_FWDT( FWDTEN_OFF )

int main()
{
    ANSELA = ANSELB = 0;
    TRISA = TRISB = 0;
    PR2 = 901;
    PR3 = 1843;
    PR4 = 3685;
    PR5 = 7370;
    T2CON = T3CON = T4CON = T5CON = 0x8000;
    
    INTCON2bits.GIE = 1;
    IEC0bits.T2IE = IEC0bits.T3IE = 1;
    IEC1bits.T4IE = IEC1bits.T5IE = 1;
    
    while (1)
    {
        asm("NOP");
    }
}
  
void __attribute__ ((interrupt, shadow, auto_psv)) _T2Interrupt(void)
{
    if (PORTAbits.RA0)
    {
        IFS0bits.T2IF = 0;
        PORTBbits.RB0 = !PORTBbits.RB0;
    }
    else
        asm("NOP");
}

void __attribute__ ((interrupt, shadow, auto_psv)) _T3Interrupt(void)
{
    if (PORTAbits.RA1)
    {
        IFS0bits.T3IF = 0;
        PORTBbits.RB1 = !PORTBbits.RB1;
    }
    else
        asm("NOP");
}

void __attribute__ ((interrupt, shadow, auto_psv)) _T4Interrupt(void)
{
    if (PORTAbits.RA2)
    {
        IFS1bits.T4IF = 0;
        PORTBbits.RB2 = !PORTBbits.RB2;
    }
    else
        asm("NOP");
}

void __attribute__ ((interrupt, shadow, auto_psv)) _T5Interrupt(void)
{
    if (PORTAbits.RA3)
    {
        IFS1bits.T5IF = 0;
        PORTBbits.RB3 = !PORTBbits.RB3;
    }
    else
        asm("NOP");
}
  
