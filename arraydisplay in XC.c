
#include <xc.h>
#include <stdio.h>
#include <string.h>

float data;
unsigned char array[16];


#define en PORTCbits.RC3
#define rs PORTCbits.RC1

#define _XTAL_FREQ 4000000


void lcd_string(unsigned char *S);
void lcdinit(void);
void lcdcmd(unsigned char data);
void lcddata(unsigned char data);

///////////////////////////////////////////////////////////////////////////////////

void lcd_string(unsigned char *S)
{
	while(*S)
    {
    	lcddata(*S);
		S++;
		}
}
//////////////////////////////////

////////////////////////////
void lcdcmd(unsigned char data)
{
	PORTD=data;
	rs=0;
    __delay_ms(1);
	en=1;
	__delay_ms(1);
	en=0;
	
}

////////////////////////////////////////////////////
void lcddata(unsigned char data)
{
	PORTD=data;
	rs=1;
    __delay_ms(1);
	en=1;
	__delay_ms(1);
	en=0;
}
////////////////////////////////////////////////////
void lcdinit(void)
{
	lcdcmd(0x01);
	__delay_ms(40);
	lcdcmd(0x38);
	lcdcmd(0x0C);
  	lcdcmd(0x06);
    lcdcmd(0x80);

}

//////////////////////////////////////////////////////////////////

void main(void)
{
OSCCON=0xEF; //EF 4 MHz


TRISB=0X00;
TRISC=0x00;
TRISD=0x00;
en=0;

__delay_ms(10);

lcdinit();
lcdcmd(0x81);
lcd_string("RIT WELCOMES");
lcdcmd(0xC1);
lcd_string("YOU");
__delay_ms(500);


data=563.563;

sprintf(array,"%.2f",data); 
strcat(array," V");

lcdcmd(0x01);
lcd_string(array);

while(1)
{
  

}        
    
}

