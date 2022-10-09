/****************************************************************************************************************/
/********************Auther: Andrew Ashraf      *****************************************************************/
/********************File : PROGRAM of KEYPAD   *****************************************************************/
/********************Date : 3/9/2022            *****************************************************************/
/********************Version : First version    *****************************************************************/
/****************************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "KEYPAD_configure.h"
#include "KEYPAD_private.h"
#include "DIO_interface.h"
#include"avr/delay.h"

/*
 * Description : initialize keypad at a given port
 * Arguments   : void
 * Return      : void
 */
void KEYPAD_vidInitialize(u8 Copy_U8Port)
{
	/*
	 * Port Direction:
	 * Initialize columns as output
	 * Initialize rows as input
	 */
	DIO_VidSetPortDirection(Copy_U8Port,0XF0);
	/*
	 * Port values:
	 * Initialize all values in port to one  "rows to Enable PULL-UP resistor"
	 */
	DIO_VidSetPortValue(Copy_U8Port,0XFF);
}

/*
 * Description : return ASCII value of pressed Key
 * Arguments   : void
 * Return      : u8
 */
u8 KEYPAD_U8GetPressedKey(u8 Copy_U8Port)
{
	u8 LOC_U8Key=KPD_INIT_VALUE;  /*Value that if returned means no pressed key*/
	u8 LOC_U8Pressed=HIGH;
	for(u8 LOC_U8C=0;LOC_U8C<COLUMNS_NO;LOC_U8C++ )
	{
		DIO_VidSetPinValue(Copy_U8Port,LOC_U8C+ROWS_NO,LOW); /*Set current column to LOW and check rows*/
		for(u8 LOC_U8R=0;LOC_U8R<ROWS_NO;LOC_U8R++)
		{
			LOC_U8Pressed=DIO_U8GetPinValue(Copy_U8Port,LOC_U8R);  /*Store state of each row of current column*/
			if(LOW==LOC_U8Pressed)    /*if state of one row of current column is pressed*/
			{
				LOC_U8Key=keypad[LOC_U8R][LOC_U8C];  /*Value by current row and column to be returned*/
				while(LOW==LOC_U8Pressed)   /*Stay in loop until button be not pressed*/
				{
					LOC_U8Pressed=DIO_U8GetPinValue(Copy_U8Port,LOC_U8R);
				}
				_delay_ms(KPD_DELAY);
			}
		}
		DIO_VidSetPinValue(Copy_U8Port,LOC_U8C+ROWS_NO,HIGH); /*Return current column to HIGH*/
	}
	return LOC_U8Key;  /*Return Pressed value or KPD_INIT_VALUE if not pressed*/
}

 
