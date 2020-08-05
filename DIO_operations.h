#ifndef DIO_operations
#define DIO_operations
#include "data_types_def.h"
#include "bit_operations.h"
#include "DIO_def.h"

//operations on ports
// the value passed to these functions is the value of every single bit in the PORT as 0b01011110 or 0x2F...
void DIO_setPortMode(u8 PORT, u8 value)
{
	// switching over the PORT and setting it to the specified value
	switch (PORT)
	{
		case PORTA : DDRA_reg = value; break;
		case PORTB : DDRB_reg = value; break;
		case PORTC : DDRC_reg = value; break;
		case PORTD : DDRD_reg = value; break;
		default: // exit (EXIT_FAILURE);
		break;
	}
}
void DIO_setPortVal(u8 PORT, u8 value) 
{
		// switching over the PORT and setting it to the specified value
		switch (PORT)
		{
			case PORTA : PORTA_reg = value; break;
			case PORTB : PORTB_reg = value; break;
			case PORTC : PORTC_reg = value; break;
			case PORTD : PORTD_reg = value; break;
			default: // exit (EXIT_FAILURE);
			 break;
		}
}
void DIO_setPortPullUp(u8 PORT,u8 value)
{
	// to enable the pull-up resistance, the pin must be input and we enable it by writing high on the port register
	DIO_setPortMode(PORT, INPUT);
	DIO_setPortVal(PORT, value);
}
u8 DIO_getPortVal(u8 PORT)
{
	
	if (PORT<PORTA || PORT> PORTD) // we could eliminate this line and use 'default' in the 'switch...case' but, using this line is cheaper
	return 0xff; // returning a false value 
	
	//Notice that : we could use a temp variable to store the data but, using the return statement directly is a way more cheaper
	switch (PORT)
	{
		// we left the break statement for the sake of readability
		case PORTA: return (PINA_reg); break;
		case PORTB: return (PINB_reg); break;
		case PORTC: return (PINC_reg); break;
		case PORTD: return (PIND_reg); break;
	}
	return 0xff; // returning a false value "this line is useless I put it here to avoid some annoying warnings"

}


//operations on pins
void DIO_setPinMode(u8 PORT, u8 PIN, u8 value)
{
	if (PIN < PIN0 || PIN > PIN7) // wrong value for the pin !
		return;
	if (PORT<PORTA || PORT> PORTD) // we could eliminate this line and use 'default' in the 'switch...case' but, using this line is cheaper
		return;
		
		if (value == INPUT)
		{
			switch (PORT)
			{
				case PORTA: clr_bit(DDRA_reg,PIN); break;
				case PORTB: clr_bit(DDRB_reg,PIN); break;
				case PORTC: clr_bit(DDRC_reg,PIN); break;
				case PORTD: clr_bit(DDRD_reg,PIN); break;
				//default: // exit (EXIT_FAILURE); break;
			}
		} 
		else // if any other value is passed then, use it as OUTPUT, you can edit this line using else if (OUTPUT)
		{
			switch (PORT)
			{
				case PORTA: set_bit(DDRA_reg,PIN); break;
				case PORTB: set_bit(DDRB_reg,PIN); break;
				case PORTC: set_bit(DDRC_reg,PIN); break;
				case PORTD: set_bit(DDRD_reg,PIN); break;
				//default: // exit (EXIT_FAILURE); break;
			}
		}
}
void DIO_setPinVal(u8 PORT, u8 PIN, u8 value)
{
	if (PIN < PIN0 || PIN > PIN7) // wrong value for the pin !
	return;
	if (PORT<PORTA || PORT> PORTD) // we could eliminate this line and use 'default' in the 'switch...case' but, using this line is cheaper
	return;
	
	if (value == LOW)
	{
		switch (PORT)
		{
			case PORTA: clr_bit(PORTA_reg,PIN); break;
			case PORTB: clr_bit(PORTB_reg,PIN); break;
			case PORTC: clr_bit(PORTC_reg,PIN); break;
			case PORTD: clr_bit(PORTD_reg,PIN); break;
			//default: // exit (EXIT_FAILURE); break;
		}
	}
	else // if any other value is passed then, use it as HIGH ! you can edit this line using else if (HIGH)
	{
		switch (PORT)
		{
			case PORTA: set_bit(PORTA_reg,PIN); break;
			case PORTB: set_bit(PORTB_reg,PIN); break;
			case PORTC: set_bit(PORTC_reg,PIN); break;
			case PORTD: set_bit(PORTD_reg,PIN); break;
			//default: // exit (EXIT_FAILURE); break;
		}
	}
}
void DIO_setPinPullUp(u8 PORT, u8 PIN, u8 status)
{
	// to enable the pull-up resistance, the pin must be input and we enable it by writing high on the port register
	DIO_setPinMode(PORT, PIN, INPUT);
	DIO_setPinVal(PORT, PIN, status);  // HIGH if ENABLE , LOW if DISABLE
}
u8 DIO_getPinVal(u8 PORT, u8 PIN)
{
	// PINx --> Port INput register, PIN --> a DIO pin of the ports of the MCU 
	
	if (PIN < PIN0 || PIN > PIN7) // wrong value for the pin !
	return 0xff; // returning a false value as a single pin can't hold 0xff !
	
	if (PORT<PORTA || PORT> PORTD) // we could eliminate this line and use 'default' in the 'switch...case' but, using this line is cheaper
	return 0xff; // returning a false value as a single pin can't hold 0xff !
	//Notice that : we could use a temp variable to store the data but, using the return statement directly is a way more cheaper
	switch (PORT)
	{
		// we left the break statement for the sake of readability 
		case PORTA: return (get_bit(PINA_reg,PIN)); break;
		case PORTB: return (get_bit(PINB_reg,PIN)); break;
		case PORTC: return (get_bit(PINC_reg,PIN)); break;
		case PORTD: return (get_bit(PIND_reg,PIN)); break;
	}
	return 0xff; // returning a false value "this line is useless I put it here to avoid some annoying warnings"
}


#endif