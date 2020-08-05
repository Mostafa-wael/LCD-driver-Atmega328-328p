#ifndef DIO_def
#define DIO_def
#include "data_types_def.h"
// from Atmega32 data sheet --> register summary P.299

// ports' registers //
// Port A
#define PORTA_reg  *((volatile u8*) 0x3B)
#define DDRA_reg   *((volatile u8*) 0x3A)
#define PINA_reg   *((volatile u8*) 0x39)

// Port B
#define PORTB_reg  *((volatile u8*) 0x38)
#define DDRB_reg   *((volatile u8*) 0x37)
#define PINB_reg   *((volatile u8*) 0x36)

// Port C
#define PORTC_reg  *((volatile u8*) 0x35)
#define DDRC_reg   *((volatile u8*) 0x34)
#define PINC_reg   *((volatile u8*) 0x33)

// Port D
#define PORTD_reg  *((volatile u8*) 0x32)
#define DDRD_reg   *((volatile u8*) 0x31)
#define PIND_reg   *((volatile u8*) 0x30)

// more definitions for the operations //
//Ports
#define PORTA 1
#define PORTB 2
#define PORTC 3
#define PORTD 4

#define A 1
#define B 2
#define C 3
#define D 4
//Pins
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
//Mode
#define INPUT 0
#define OUTPUT 1

#define I 0
#define O 1
//values
#define HIGH 1
#define LOW 0

#define H 1
#define L 0
// status
#define ENABLE 1
#define DISABLE 0

#define EN 1
#define DS 0


#endif