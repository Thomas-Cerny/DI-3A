#include "p33EV32GM002.h"

_FOSCSEL(FNOSC_FRC)
_FOSC(OSCIOFNC_ON & IOL1WAY_OFF)
_FWDT(FWDTEN_OFF)


void send_to_SPI(unsigned int value);

/*
 * 
 */
int main() {





    TRISA = 0x0;



    TRISB = 0x00;
    PORTB = 0;
    PORTA = 0;

    ANSELB = 0;
    ANSELA = 0;

    PR2 = 14467;
    T2CON = 0x8030;

    
    SPI1STAT = 0x0000;      //  modul zatim nechavame vzpnuty
   
    SPI1CON1 = 0x0520;      // 0000 0101 0010 0000
    
    SPI1CON2 = 0 ;
    
    SPI1STATbits.SPIROV = 0;     // 3. Clear the SPIROV bit (SPIxSTAT<6>).
    SPI1STATbits.SPIEN  = 1;     // 4. Enable SPI operation by setting the SPIEN bit (SPIxSTAT<15>).

    /*  povoluji preruseni  od citace  */
    IEC0bits.T2IE = 1;
    IEC0bits.SPI1IE=1;      //povoleni preruseni od SPI1

    
    
    /*  globalni povoleni preruseni, tohle se musi povolit, 
     * jinak nebude zadne preruseni krome TRAP   */
    INTCON2bits.GIE = 1;

    while (1) {

        asm(" btg PORTA, #0 ");
        asm(" btg PORTA, #1 ");
        asm(" btg PORTA, #2 ");

    }

    return 0;
}





void __attribute__((interrupt, auto_psv)) _T2Interrupt(void)  {
      IFS0bits.T2IF = 0;
      
      send_to_SPI(0x1234);
}






void __attribute__((interrupt, auto_psv)) _SPI1Interrupt(void)  {
      IFS0bits.SPI1IF = 0;
      /* a tady dal vsechno to, co se ma udelat po odvysilani znaku po SPI   */
      
}





void send_to_SPI(unsigned int value){
    unsigned int a,cteni;
    a=value;      
    cteni=SPI1BUF;      //prectem at muzem vysiliat
    SPI1BUF=a;          // 5. Write the data to be transmitted to the SPIxBUF register
}
