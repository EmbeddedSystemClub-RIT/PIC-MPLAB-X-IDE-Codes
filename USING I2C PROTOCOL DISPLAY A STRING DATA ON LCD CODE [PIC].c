
// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <string.h>

#define _XTAL_FREQ 4000000


void lcd_string(unsigned char *S);   // To display ASCII string on LCD
void lcdinit(void);                             //LCD initialization Function
void lcdcmd(unsigned char data);   //To write LCD Commands
void lcddata(unsigned char data);   //To write one byte ASCII data to LCD
void I2C_Init(const unsigned long c);
void I2C_Wait(void);
void I2C_Start();
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_Write(unsigned d);
unsigned short I2C_Read(void);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// I2C code for interfacing PCF8575 chip.
// Data pins of LCD connected  to P0 port of PCF8575
// Rs pin of LCD connected  to P11 port port pin of PCF8575
// EN pin of LCD connected  to P10 port port pin of PCF8575
// Slave address 0x40 for write and 0x41 for read.

//////////////////////////////////////////////////////////////////////////
void I2C_Init(const unsigned long c)
{
  SSPCON1 = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISCbits.TRISC3 = 1	;	//INPUT DIR OF RC3
  TRISCbits.TRISC4 = 1	;	//INPUT DIR OF RC4
}
///////////////////////////////////////////////////////////
void I2C_Wait()
{
  while ((SSPSTATbits.R==1) | (SSPCON2 & 0x0C)); 
}
/////////////////////////////////////////////////////////////////
void I2C_Start()
{
  I2C_Wait();
  SSPCON2bits.SEN=1;
}
/////////////////////////////////////////////////////////////
void I2C_RepeatedStart()
{
  I2C_Wait();
 SSPCON2bits.RSEN=1;
 }
/////////////////////////////////////////////////////////////
void I2C_Stop()
{
  I2C_Wait();
	SSPCON2bits.PEN=1;
}
////////////////////////////////////////////////////////////////
void I2C_Write(unsigned d)
{
  I2C_Wait();
  SSPBUF = d;
}

///////////////////////////////////////////////////////////////////
unsigned short I2C_Read(void)
{
  unsigned short temp;
  I2C_Wait();
  SSPCON2bits.RCEN = 1;
  I2C_Wait();
  temp = SSPBUF;
  I2C_Wait();
	
  SSPCON2bits.ACKEN = 1;
  return temp;
}
//////////////////////////////////////////////////////
void lcd_string(unsigned char *S)   // To display ASCII string on LCD
{
	while(*S)
    {
    	lcddata(*S);
		S++;
    }
}
////////////////////////////////////////////////////////////////
void lcdcmd(unsigned char command)       //To write LCD Commands
{
I2C_Start();  //Start condition
I2C_Write(0x40);//7 bit slave address + Write in next cycle
I2C_Write(command);    // Write to PORT 0 of slave device
I2C_Write(0b00000000); //  Write to PORT 1 of slave device

I2C_Write(command);  // Write to PORT 0 of slave device
I2C_Write(0x0b00000001); // Write to PORT 1 of slave device

I2C_Write(command);   // Write to PORT 0 of slave device
I2C_Write(0b00000000); // Write to PORT 1 of slave device

I2C_Stop(); 

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void lcddata(unsigned char data)  // To write one byte ASCII data to LCD
{
 
I2C_Start();  //Start condition
I2C_Write(0x40);  //7 bit slave address + Write in next cycle
I2C_Write(data);     // Write to PORT 0 of slave device
I2C_Write(0b00000010);   // Write to PORT 1 of slave device
__delay_ms(70);

I2C_Write(data);    // Write to PORT 0 of slave device
I2C_Write(0b00000011);    // Write to PORT 1 of slave device
__delay_ms(70);

I2C_Write(data);    // Write to PORT 0 of slave device
I2C_Write(0b00000010);   // Write to PORT 1 of slave device
__delay_ms(70);

I2C_Stop(); 
    
}
////////////////////////////////////////////////////
void lcdinit(void)          //LCD initialization Function
{
	lcdcmd(0x01);
	__delay_ms(70);
	lcdcmd(0x38);
	__delay_ms(100);
    lcdcmd(0x0C);
	__delay_ms(100);
	lcdcmd(0x06);
	__delay_ms(100);
	lcdcmd(0x80);
    __delay_ms(100);
}


//////////////////////////////////////////////////////////////////

void main(void)
{
   
OSCCON=0xEF; //EF 4 MHz

TRISC=0x00;

TRISBbits.TRISB0 = 0;

__delay_ms(500);

I2C_Init(100000); 

lcdinit();
lcd_string("YASH KAKA KE JAY");
  __delay_ms(100); // Delay for better visibility

    // Move to Second Row
    lcdcmd(0xC0);  // Set cursor to 2nd row

lcd_string("2455004");

while(1)
{

   LATBbits.LATB0 = 1;
            __delay_ms(500);
            LATBbits.LATB0 = 0;
            __delay_ms(500);
   
}        
    
}


