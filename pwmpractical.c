#include<XC.h>
//#include<xlcd.h>

#pragma config OSC = INTIO67
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Oscillator Switchover mode disabled
#pragma config PWRT = ON        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
#pragma config MCLRE= OFF  
#pragma config LVP  = OFF 
#pragma config PBADEN  = OFF 
#pragma config EBTR0   = OFF 
#pragma config EBTR1   = OFF 
#pragma config EBTR2   = OFF
#pragma config EBTR3   = OFF
#pragma config EBTRB   = OFF 
#pragma config WRTD    = OFF 
#pragma config CPD = ON
#pragma config DEBUG = OFF 
#pragma config CP0 = ON 
#pragma config CP1 = ON 
#pragma config CP2 = ON 
#pragma config CP3 = ON 
#pragma config CPB = ON 


void main(void)
{
OSCCON=0xEF; //EF 4 MHz
ADCON1=0X0F;
TRISB=0X0F;
TRISC=0X00;

CCP1CON=0x2C;
CCPR1L=0x5E;
PR2=124;
T2CON=0x03;
TMR2ON=1;


//CCP1CON=0x1C;
//CCPR1L=12;
//PR2=34;
//T2CON=0x00;
//TMR2ON=1;

/////////////////////////////////////****************************
while(1)
{
  
     
   
}  // end of while 1 
		
} //end of main
