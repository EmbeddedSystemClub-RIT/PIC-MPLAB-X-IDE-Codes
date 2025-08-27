#include <xc.h>
#pragma config OSC = INTIO67
#pragma config PWRT = ON        // 1 = PWRT disabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
#pragma config MCLRE= OFF  //1 = MCLR pin disabled; RE3 input pin disabled
#pragma config LVP  = OFF //0 = Single-Supply ICSP disabled
#pragma config PBADEN  = OFF //PORTB A/D Enable bit 0 = PORTB<4:0> pins are configured as digital I/O on Reset
#pragma config CPD = ON //1 = Data EEPROM not code-protected
#pragma config DEBUG = OFF //0 = Background debugger enabled, RB6 and RB7 are dedicated to In-Circuit Debug
#pragma config CP0 = ON //Block 0 (000800-001FFFh) not code-protected
#pragma config CP1 = ON //Block 1 (002000-003FFFh) not code-protected
#pragma config CP2 = ON //Block 2 (004000-005FFFh) not code-protected
#pragma config CP3 = ON //Block 3 (006000-007FFFh) not code-protected
#pragma config CPB = ON //Boot block (000000-0007FFh) not code-protected

#define LED PORTBbits.RB0

void TMR2_delay(void);

void main(void)
{

OSCCON=0XEF;
TRISB=0x00;
PR2=200;
T2CON=0x00;
TRISDbits.RD6=0;

while(1)
{
LED=1;
TMR2_delay();
LED=0;
TMR2_delay();
}

}  // End of Main function

//////////////////////////////////////////
void TMR2_delay()
{
    TMR2=0;
    TMR2IF=0;
    TMR2ON=1;
    while(TMR2IF==0);
    TMR2ON=0;
    TMR2IF=0;    
}

