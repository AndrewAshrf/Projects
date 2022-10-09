/****************************************************************************************************/
/********************Auther: Andrew Ashraf      *****************************************************/
/********************File : PROGRAM of DIO      *****************************************************/
/********************Date : 3/9/2022            *****************************************************/
/********************Version : First version    *****************************************************/
/****************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_private.h"

/*
 * Description : Set direction of certain Pin in this Port
 * Arguments   : Port , Pin , Value
 * return      : void
 */
void DIO_VidSetPinDirection(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Dir)
{
	if(1== Copy_U8Dir)
	{
		switch(Copy_U8Port)
		{
			case 0:  SET_BIT(DDRA_REG,Copy_U8Pin);  break;
			case 1:  SET_BIT(DDRB_REG,Copy_U8Pin);  break;
			case 2:  SET_BIT(DDRC_REG,Copy_U8Pin);  break;
			case 3:  SET_BIT(DDRD_REG,Copy_U8Pin);  break;
		}
	}
	else if(0== Copy_U8Dir)
	{
		switch(Copy_U8Port)
		{
			case 0:  CLR_BIT(DDRA_REG,Copy_U8Pin);  break;
			case 1:  CLR_BIT(DDRB_REG,Copy_U8Pin);  break;
			case 2:  CLR_BIT(DDRC_REG,Copy_U8Pin);  break;
			case 3:  CLR_BIT(DDRD_REG,Copy_U8Pin);  break;
		}
	}
}
/*
 * Description : Set value of Pin in this Port
 * Arguments   : Port ,Pin ,Value
 * return      : void
 */
void DIO_VidSetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Value)
{
	if(1== Copy_U8Value)
	{
		switch(Copy_U8Port)
		{
			case 0:  SET_BIT(PORTA_REG,Copy_U8Pin);  break;
			case 1:  SET_BIT(PORTB_REG,Copy_U8Pin);  break;
			case 2:  SET_BIT(PORTC_REG,Copy_U8Pin);  break;
			case 3:  SET_BIT(PORTD_REG,Copy_U8Pin);  break;
		}
	}
	else if(0== Copy_U8Value)
	{
		switch(Copy_U8Port)
		{
			case 0:  CLR_BIT(PORTA_REG,Copy_U8Pin);  break;
			case 1:  CLR_BIT(PORTB_REG,Copy_U8Pin);  break;
			case 2:  CLR_BIT(PORTC_REG,Copy_U8Pin);  break;
			case 3:  CLR_BIT(PORTD_REG,Copy_U8Pin);  break;
		}
	}
}
/*
 * Description : Gets value of certain Pin in this Port
 * Arguments   : Port ,Pin
 * return      : u8(1 or 0)
 */
u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin)
{
	u8 LOC_U8x;
	switch(Copy_U8Port)
		{
			case 0:  LOC_U8x=GET_BIT(PINA_REG,Copy_U8Pin);  break;
			case 1:  LOC_U8x=GET_BIT(PINB_REG,Copy_U8Pin);  break;
			case 2:  LOC_U8x=GET_BIT(PINC_REG,Copy_U8Pin);  break;
			case 3:  LOC_U8x=GET_BIT(PIND_REG,Copy_U8Pin);  break;
		}
	return LOC_U8x;
}
/*
 * Description : Toggles value of Pin in this Port
 * Arguments   : Port ,Pin
 * return      : void
 */
void DIO_vidTogglePinValue(u8 Copy_U8Port,u8 Copy_U8Pin)
{
	switch(Copy_U8Port)
		{
			case 0:  TOGGLE_BIT(PORTA_REG,Copy_U8Pin);  break;
			case 1:  TOGGLE_BIT(PORTB_REG,Copy_U8Pin);  break;
			case 2:  TOGGLE_BIT(PORTC_REG,Copy_U8Pin);  break;
			case 3:  TOGGLE_BIT(PORTD_REG,Copy_U8Pin);  break;
		}
}
/*
 * Description : Set value of the whole register
 * Arguments   : Port ,Value
 * return      : void
 */
void DIO_VidSetPortValue(u8 Copy_U8Port,u8 Copy_U8Value)
{
	switch(Copy_U8Port)
	{
		case 0:  PORTA_REG=Copy_U8Value;  break;
		case 1:  PORTB_REG=Copy_U8Value;  break;
		case 2:  PORTC_REG=Copy_U8Value;  break;
		case 3:  PORTD_REG=Copy_U8Value;  break;
	}
}
/*
 * Description : Set direction of the whole register
 * Arguments   : Port , Value
 * return      : void
 */
void DIO_VidSetPortDirection(u8 Copy_U8Port,u8 Copy_U8Dir)
{
	switch(Copy_U8Port)
	{
		case 0:  DDRA_REG=Copy_U8Dir;  break;
		case 1:  DDRB_REG=Copy_U8Dir;  break;
		case 2:  DDRC_REG=Copy_U8Dir;  break;
		case 3:  DDRD_REG=Copy_U8Dir;  break;
	}
}


 
