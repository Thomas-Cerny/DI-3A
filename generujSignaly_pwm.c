/*
* 6. ULOHA: PWM:
* 1) GENERUJ PWM 1KHZ, STRIDA 3:1
* 2) GENERUJ PWM 1KHZ, STRIDA 3:1, 1:1, 1:3
*/

// PWM1 -> RB10, PWM2 -> RB12, PWM3 -> RB14

#include <p33EV32GM002.h>

_FOSCSEL( FNOSC_FRC )
_FOSC( OSCIOFNC_ON &  IOL1WAY_OFF)
_FWDT( FWDTEN_OFF )

int main()
{
    TRISB = 0;
    PORTB = 0;
    ANSELB = 0;

    /* Konfigurace PWM vystupu - povoleni signalu na vystupnich portech */
    IOCON1 = IOCON2 = IOCON3 = 0xC000;      // Nastaveni vystupniho rezimu PWM - pouze PWMxH aktivni

    /* Nastaveni parametru PWM */
    PTPER = 460;                            // Nastavuje frekvenci 1kHz
    PDC1 = 345;                             // 3:1 - 75% PTPER
    PDC2 = 230;                             // 1:1 - 50% PTPER
    PDC3 = 115;                             // 1:3 - 25% PTPER
    PHASE1 = PHASE2 = PHASE3 = 0;           // Nastavuje fazovy posun

    /* Nastaveni rezimu generovani PWM signalu */
    PWMCON1 = PWMCON2 = PWMCON3 = 0x0008;   // Independent mode - kazdy vystup bezi samostatne

    /* Konfigurace generovani PWM */
    PTCON2 = 0x0004;        // Nastavuje delicku 1:4
    PTCON = 0x8000;         // Aktivace PWM modulu

    while (1)
    {
        asm("NOP");
    }
}
