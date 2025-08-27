#include <xc.h>

#define _XTAL_FREQ 4000000  // Define crystal frequency for __delay_ms()

// Function Prototypes
void PWM_Init(void);
void PWM_SetDutyCycle(unsigned int duty);

// Main function
void main(void) {
    OSCCON = 0XEF;
    // Initialize peripherals
    TRISCbits.TRISC2 = 0;  // Set RC2 as output (PWM signal for ULN2003)
    
    PWM_Init(); // Initialize PWM

    while (1) {
        PWM_SetDutyCycle(0);     // 0% Duty Cycle
        __delay_ms(3000);        // Wait 2 seconds

        PWM_SetDutyCycle(512);   // 50% Duty Cycle
        __delay_ms(3000);        // Wait 2 seconds

        PWM_SetDutyCycle(716);   // 70% Duty Cycle
        __delay_ms(3000);        // Wait 2 seconds

        PWM_SetDutyCycle(1023);  // 100% Duty Cycle
        __delay_ms(3000);        // Wait 2 seconds
    }
}

// Initialize PWM on CCP1 (RC2)
void PWM_Init(void) {
    TRISCbits.TRISC2 = 0; // Set RC2 as output (CCP1 pin)

    PR2 = 255; // Set PWM period for 10-bit resolution
    CCP1CON = 0x0C; // Configure CCP1 for PWM mode
    
    CCPR1L = 0x00; // Initial duty cycle (0%)
    T2CON = 0x03; // Enable Timer2 with prescaler = 16
    
    TMR2ON = 1; // Start Timer2
}

// Set PWM duty cycle (10-bit)
void PWM_SetDutyCycle(unsigned int duty) {
    if (duty > 1023) duty = 1023; // Limit duty cycle to 10 bits

    CCPR1L = (unsigned char)(duty >> 2);  // Upper 8 bits
    CCP1CONbits.DC1B = (unsigned char)(duty & 0x03); // Lower 2 bits
}
