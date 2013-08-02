#include <stdio.h>
#include <stdlib.h>
#include <p24FJ64GB002.h>

#define DELAY 3000

#define DS_low()  LATB &=~0x8000
#define DS_high()  LATB |=0x8000

#define ST_CP_low() LATB &=~0x4000
#define ST_CP_high() LATB |=0x4000

#define SH_CP_low() LATB &=~0x2000
#define SH_CP_high() LATB |=0x2000

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#define DIG1 0x8000
#define DIG2 0x4000
#define DIG3 0x2000
#define DIG4 0x1000

#define ZERO 0x0003
#define ONE 0x009F
#define TWO 0x0025
#define THREE 0x000D
#define FOUR 0x0099
#define FIVE 0x0049
#define SIX 0x00C1
#define SEVEN 0x001F
#define EIGHT 0x0001
#define NINE 0x0019
#define DECIMAL 0x00FE
#define APOSTROPHE 0x0200
#define COLON 0x0800
#define CLEAR 0x0000

unsigned int characters[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned int punctuation[] = {DECIMAL, APOSTROPHE, COLON};

void setLEDs(unsigned int pattern);
void selfTest();
void iterateAllDigits(unsigned int dig1Pattern, unsigned int dig2Pattern, unsigned int dig3Pattern, unsigned int dig4Pattern, unsigned int punctuation);

/*
 *
 */
int main(int argc, char** argv) {

    TRISB = 0x0000;
    T1CON = 0x8030;

    // reset everything
    LATB = 0x0000;
    while (1) {
        selfTest();
    } // main loop
    return (EXIT_SUCCESS);
}

void selfTest() {
    int i;
    for (i = 0; i < 10; i++) {
        iterateAllDigits(characters[i], characters[i], characters[i], characters[i], punctuation[i / 3]);
    }
    iterateAllDigits(CLEAR, CLEAR, CLEAR, CLEAR, CLEAR);
}

void iterateAllDigits(unsigned int dig1Pattern, unsigned int dig2Pattern, unsigned int dig3Pattern, unsigned int dig4Pattern, unsigned int punctuation) {
    TMR1 = 0;
    while (TMR1 < DELAY) {
        setLEDs(DIG1 | dig1Pattern);
        setLEDs(DIG2 | dig2Pattern);
        setLEDs(DIG3 | dig3Pattern);
        setLEDs(DIG4 | dig4Pattern);
        setLEDs(punctuation);
    }
}

void setLEDs(unsigned int pattern) {
    ST_CP_low();
    SH_CP_low();
    int i;
    for (i = 0; i < 16; i++) {
        if (CHECK_BIT(pattern, i))
            DS_high();
        else
            DS_low();

        SH_CP_high();
        SH_CP_low();
    }
    ST_CP_high();
}


