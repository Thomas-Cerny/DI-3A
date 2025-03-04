// 2. ULOHA: BINARNI SCITACKA PRO DVE 5BITOVA CISLA

#include <p33EV32GM002.h>

_FOSCSEL( FNOSC_FRC )
_FOSC( OSCIOFNC_ON & IOL1WAY_OFF)
_FWDT( FWDTEN_OFF )

int main()
{
    ANSELA = ANSELB = 0;
    TRISA = 0xFFFF;
    TRISB = 0x001F;
    CNPDA = 0x001F;
    CNPDB = 0x001F;

    int prvniCislo, druheCislo;

    while (1)
    {
        prvniCislo = PORTA & 0x001F;
        druheCislo = PORTB & 0x001F;
        PORTB = (prvniCislo + druheCislo) << 5;
        
        asm("NOP");
    }
}