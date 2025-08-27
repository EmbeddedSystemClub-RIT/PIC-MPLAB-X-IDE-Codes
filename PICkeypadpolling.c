#include <xc.h>
#include <string.h>


#pragma config OSC = INTIO67
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor disabled
#pragma config IESO = OFF       // Oscillator Switchover mode disabled
#pragma config PWRT = ON        // power up timer enabled
#pragma config BOREN= OFF   // Brown-out Reset enabled in hardware only (SBOREN is disabled) 
#pragma config WDT  = OFF       // WDT disabled
//#pragma config WDTPS =32768
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
#pragma config CCP2MX=PORTBE


#define C1 PORTBbits.RB0
#define C2 PORTBbits.RB1
#define C3 PORTBbits.RB2

#define en PORTCbits.RC3
#define rs PORTCbits.RC1
#define rw1 PORTCbits.RC2

#define R1 PORTBbits.RB4
#define R2 PORTBbits.RB5
#define R3 PORTBbits.RB6
#define R4 PORTBbits.RB7



void lcd_string(unsigned char *Spointer);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);

#define _XTAL_FREQ 4000000

//////////////////////////////////////////////////////////////////////

void lcd_string(unsigned char *Spointer)
{
	while(*Spointer)
    {
    	lcddata(*Spointer);
		Spointer++;
   }
}
////////////////////////////////////////////////////////////////
void lcdcmd(unsigned char command)       //To write LCD Commands
{
	PORTD=command;
	rs=0;
	en=1;
	__delay_ms(1);
	en=0;
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lcddata(unsigned char data)  // To write one byte ASCII data to LCD
{
	PORTD=data;
	rs=1;
	en=1;
	__delay_ms(1);
	en=0;
}
////////////////////////////////////////////////////
void lcdinit(void)          //LCD initialization Function
{
	lcdcmd(0x01);
	__delay_ms(80);
	lcdcmd(0x38);
	__delay_ms(10);
         lcdcmd(0x0C);
	__delay_ms(10);
	lcdcmd(0x06);
	__delay_ms(10);
	lcdcmd(0x80);
}
////////////////////////////////////////////////////////
////////////////////////////////////////////////////
void main(void)
{
   
OSCCON=0xEF; //EF 4 MHz
ADCON1=0X0F;
TRISD=0X00;
TRISB=0X0F;
TRISC=0X00;
PORTD=0X00;
PORTC=0X00;
rw1=0;
 

lcdinit();
lcdcmd(0xC0);
lcd_string("RIT WELCOMES YOU");
while(1)
{
//scan row1
R1=0;
R2=1;
R3=1;
R4=1;
   
if(C1==0)
{
    lcdcmd(0x80);
    lcddata('1');
  
}
 if(C2==0)
{
     lcdcmd(0x80);
    lcddata('2');
  
}    
     if(C3==0)
{
         lcdcmd(0x80);
    lcddata('3');
  
}
/////////////////////////////////////////////////
//scan row2
R1=1;
R2=0;
R3=1;
R4=1;
   
if(C1==0)
{
    lcdcmd(0x80);
    lcddata('4');
   
}
 if(C2==0)
{
     lcdcmd(0x80);
    lcddata('5');
   
}    
     if(C3==0)
{
         lcdcmd(0x80);
    lcddata('6');
 
}
/////////////////////////////////////////////////
//scan row3
R1=1;
R2=1;
R3=0;
R4=1;
   
if(C1==0)
{
    lcdcmd(0x80);
    lcddata('7');
  
}
 if(C2==0)
{
     lcdcmd(0x80);
    lcddata('8');
  
}    
     if(C3==0)
{
         lcdcmd(0x80);
    lcddata('9');
  
}
/////////////////////////////////////////////////
//scan row4
R1=1;
R2=1;
R3=1;
R4=0;
   
if(C1==0)
{
    lcdcmd(0x80);
    lcddata('*');
  
}
 if(C2==0)
{
     lcdcmd(0x80);
    lcddata('0');
   // break;
}    
     if(C3==0)
{
         lcdcmd(0x80);
    lcddata('#');
  
}

__delay_ms(300);
}

}