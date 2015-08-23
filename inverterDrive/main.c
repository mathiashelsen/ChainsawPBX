#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char LUT_index;

static volatile char LUT[256] = {
0X4F,  0X4F,  0X50,  0X51,  
0X52,  0X53,  0X54,  0X55,  
0X56,  0X57,  0X58,  0X59,  
0X5A,  0X5B,  0X5C,  0X5D,  
0X5E,  0X5F,  0X5F,  0X60,  
0X61,  0X62,  0X63,  0X64,  
0X64,  0X65,  0X66,  0X67,  
0X68,  0X68,  0X69,  0X6A,  
0X6A,  0X6B,  0X6C,  0X6C,  
0X6D,  0X6E,  0X6E,  0X6F,  
0X6F,  0X70,  0X70,  0X71,  
0X71,  0X72,  0X72,  0X73,  
0X73,  0X73,  0X74,  0X74,  
0X74,  0X75,  0X75,  0X75,  
0X75,  0X75,  0X76,  0X76,  
0X76,  0X76,  0X76,  0X76,  
0X76,  0X76,  0X76,  0X76,  
0X76,  0X76,  0X76,  0X75,  
0X75,  0X75,  0X75,  0X75,  
0X74,  0X74,  0X74,  0X73,  
0X73,  0X73,  0X72,  0X72,  
0X71,  0X71,  0X70,  0X70,  
0X6F,  0X6F,  0X6E,  0X6E,  
0X6D,  0X6C,  0X6C,  0X6B,  
0X6A,  0X6A,  0X69,  0X68,  
0X68,  0X67,  0X66,  0X65,  
0X64,  0X64,  0X63,  0X62,  
0X61,  0X60,  0X5F,  0X5F,  
0X5E,  0X5D,  0X5C,  0X5B,  
0X5A,  0X59,  0X58,  0X57,  
0X56,  0X55,  0X54,  0X53,  
0X52,  0X51,  0X50,  0X4F,  
0X4F,  0X4E,  0X4D,  0X4C,  
0X4B,  0X4A,  0X49,  0X48,  
0X47,  0X46,  0X45,  0X44,  
0X43,  0X42,  0X41,  0X40,  
0X3F,  0X3E,  0X3E,  0X3D,  
0X3C,  0X3B,  0X3A,  0X39,  
0X39,  0X38,  0X37,  0X36,  
0X35,  0X35,  0X34,  0X33,  
0X33,  0X32,  0X31,  0X31,  
0X30,  0X2F,  0X2F,  0X2E,  
0X2E,  0X2D,  0X2D,  0X2C,  
0X2C,  0X2B,  0X2B,  0X2A,  
0X2A,  0X2A,  0X29,  0X29,  
0X29,  0X28,  0X28,  0X28,  
0X28,  0X28,  0X27,  0X27,  
0X27,  0X27,  0X27,  0X27,  
0X27,  0X27,  0X27,  0X27,  
0X27,  0X27,  0X27,  0X28,  
0X28,  0X28,  0X28,  0X28,  
0X29,  0X29,  0X29,  0X2A,  
0X2A,  0X2A,  0X2B,  0X2B,  
0X2C,  0X2C,  0X2D,  0X2D,  
0X2E,  0X2E,  0X2F,  0X2F,  
0X30,  0X31,  0X31,  0X32,  
0X33,  0X33,  0X34,  0X35,  
0X35,  0X36,  0X37,  0X38,  
0X39,  0X39,  0X3A,  0X3B,  
0X3C,  0X3D,  0X3E,  0X3E,  
0X3F,  0X40,  0X41,  0X42,  
0X43,  0X44,  0X45,  0X46,  
0X47,  0X48,  0X49,  0X4A,  
0X4B,  0X4C,  0X4D,  0X4E,  
};


ISR( TIM0_COMPA_vect )
{
    LUT_index += 1;
    OCR1A = LUT[LUT_index];
}

int main(void)
{
    LUT_index = 0;
    PLLCSR |= (1 << PLLE);
    PLLCSR |= (1 << PCKE);

    DDRB = 0x07;

    // Setup of the PWM generator
    // Timer1 with PWM, output A (100kHz rate)
    TCCR1 = ( 1 << PWM1A) | (1 << COM1A0); 
    OCR1C = 0x77;
    OCR1A = 0x4f;
    TCCR1 |= (1 << CS11) | (1 << CS10);

    TCCR0A = (1 << WGM01);
    OCR0A = 0xff;
    TIMSK = (1 << OCIE0A);
    TCCR0B = (1 << CS00);

    sei();

    while (1) {
    }
}
