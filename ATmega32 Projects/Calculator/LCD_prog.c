/********************************************************************************************************/
/********************Auther: Andrew Ashraf      *********************************************************/
/********************File : PROGRAM of LCD      *********************************************************/
/********************Date : 3/9/2022            *********************************************************/
/********************Version : First version    *********************************************************/
/********************************************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "LCD_configure.h"
#include "LCD_interface.h"
#include "LCD_private.h"
#include "DIO_interface.h"
#include "avr/delay.h"

 /*
  * Description : Initialize LCD , Mode used,Number of lines and Cursor
  * Arguments   : void
  * return      : void
  */
void LCD_VidInitialize(void)
{
	/*Set Data register Pins as output*/
	#if INTERFACE_LEN == EIGHT_BITS
	DIO_VidSetPortDirection(DATA_PORT,0xFF);
	#elif INTERFACE_LEN == FOUR_BITS
	DIO_VidSetPinDirection(DATA_PORT,P0,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,P1,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,P2,HIGH);
	DIO_VidSetPinDirection(DATA_PORT,P3,HIGH);
	#endif
	DIO_VidSetPinDirection(CONTROL_PORT,Rs,HIGH);/*Set Rs Pin output*/
	DIO_VidSetPinDirection(CONTROL_PORT,Rw,HIGH);/*Set Rw Pin output*/
	DIO_VidSetPinDirection(CONTROL_PORT,En,HIGH);/*Set En Pin output*/
	_delay_ms(35);
	LCD_VidSendCommand(RESET_DATA);
	LCD_VidSendCommand(FUNC_SET);
	_delay_ms(1);
	LCD_VidSendCommand(LCD_DISPLAY);
	_delay_ms(1);
	LCD_VidSendCommand(DISPLAY_CLR);
	_delay_ms(2);
}

#if INTERFACE_LEN == EIGHT_BITS
/*
 * Description : Send data (in ASCII) to data register stores it to be displayed on the LCD
 * Arguments   : Data
 * return      : void
 */
void LCD_VidSendData(u8 Copy_U8Data)
{
	DIO_VidSetPinValue(CONTROL_PORT,Rs,HIGH);/*Set RS pin 1 (Data register selected)*/
	DIO_VidSetPinValue(CONTROL_PORT,Rw,LOW);/*Set RW pin 0 (Write Mode selected)*/
	DIO_VidSetPortValue(DATA_PORT,Copy_U8Data);
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH);/*Set EN pin 1 */
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW);/*Set EN pin 0 */
	_delay_ms(2);
}
/*
 * Description : Send to command register that stores the command instructions given to the LCD
 * Arguments   : Command
 * return      : void
 */
void LCD_VidSendCommand(u8 Copy_U8Command)
{
	DIO_VidSetPinValue(CONTROL_PORT,Rs,LOW); /*Set RS pin 0 (Instruction register selected)*/
	DIO_VidSetPinValue(CONTROL_PORT,Rw,LOW);/*Set RW pin 0 (Write Mode selected)*/
	DIO_VidSetPortValue(DATA_PORT,Copy_U8Command);
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH);/*Set EN pin 1 */
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW);/*Set EN pin 0 */
	_delay_ms(2);
}
#elif INTERFACE_LEN == FOUR_BITS
/*
 * Description : Send data (in ASCII) to data register stores it to be displayed on the LCD
 * Arguments   : Data
 * return      : void
 */
void LCD_VidSendData(u8 Copy_U8Data)
{
	DIO_VidSetPinValue(CONTROL_PORT,Rs,HIGH);/*Set RS pin 1 (Data register selected)*/
	DIO_VidSetPinValue(CONTROL_PORT,Rw,LOW);/*Set RW pin 0 (Write Mode selected)*/
	DIO_VidSetPinValue(DATA_PORT,P3,GET_BIT(Copy_U8Data,BIT7));
	DIO_VidSetPinValue(DATA_PORT,P2,GET_BIT(Copy_U8Data,BIT6));
	DIO_VidSetPinValue(DATA_PORT,P1,GET_BIT(Copy_U8Data,BIT5));
	DIO_VidSetPinValue(DATA_PORT,P0,GET_BIT(Copy_U8Data,BIT4));
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH); /*Set EN pin 1 */
	_delay_ms(1);                                       
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW); /*Set EN pin 0 */
	_delay_ms(2);                                       
	DIO_VidSetPinValue(DATA_PORT,P3,GET_BIT(Copy_U8Data,BIT3));
	DIO_VidSetPinValue(DATA_PORT,P2,GET_BIT(Copy_U8Data,BIT2));
	DIO_VidSetPinValue(DATA_PORT,P1,GET_BIT(Copy_U8Data,BIT1));
	DIO_VidSetPinValue(DATA_PORT,P0,GET_BIT(Copy_U8Data,BIT0));
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH);/*Set EN pin 1 */
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW);/*Set EN pin 0 */
	_delay_ms(2);
}
/*
 * Description : Send to command register that stores the command instructions given to the LCD
 * Arguments   : Command
 * return      : void
 */
void LCD_VidSendCommand(u8 Copy_U8Command)
{
	DIO_VidSetPinValue(CONTROL_PORT,Rs,LOW); /*Set RS pin 0 (Instruction register selected)*/
	DIO_VidSetPinValue(CONTROL_PORT,Rw,LOW);/*Set RW pin 0 (Write Mode selected)*/
	DIO_VidSetPinValue(DATA_PORT,P3,GET_BIT(Copy_U8Command,BIT7));
	DIO_VidSetPinValue(DATA_PORT,P2,GET_BIT(Copy_U8Command,BIT6));
	DIO_VidSetPinValue(DATA_PORT,P1,GET_BIT(Copy_U8Command,BIT5));
	DIO_VidSetPinValue(DATA_PORT,P0,GET_BIT(Copy_U8Command,BIT4));
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH);  /*Set EN pin 1 */
	_delay_ms(1);                                         
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW);  /*Set EN pin 0 */
	_delay_ms(2);                                         
	DIO_VidSetPinValue(DATA_PORT,P3,GET_BIT(Copy_U8Command,BIT3));
	DIO_VidSetPinValue(DATA_PORT,P2,GET_BIT(Copy_U8Command,BIT2));
	DIO_VidSetPinValue(DATA_PORT,P1,GET_BIT(Copy_U8Command,BIT1));
	DIO_VidSetPinValue(DATA_PORT,P0,GET_BIT(Copy_U8Command,BIT0));
	DIO_VidSetPinValue(CONTROL_PORT,En,HIGH);/*Set EN pin 1 */
	_delay_ms(1);
	DIO_VidSetPinValue(CONTROL_PORT,En,LOW);/*Set EN pin 0 */
	_delay_ms(2);
}
#endif

/*
 * Description : Output String to LCD at current cursor position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidSendDatastring(u8* Copy_U8Data)
{
	for(u8 LOC_U8i=0 ;Copy_U8Data[LOC_U8i] != NULL ;LOC_U8i++)
	{
		LCD_VidSendData(Copy_U8Data[LOC_U8i]);
	}
}
/*
 * Description : Output number to LCD at current cursor position
 * Arguments   : Data as number
 * return      : void
 */
void LCD_VidSendDataInteger(s32 Copy_U8Data)
{
	if(Copy_U8Data<0)   /*if number is negative, Display negative sign and calculate 2nd complement*/
	{
		LCD_VidSendData('-');
		Copy_U8Data=(~Copy_U8Data)+1;
	}
	if(Copy_U8Data==0)
	{
		LCD_VidSendData('0');
	}
	u8 LOC_U8Rem,LOC_U8i=0;
	u8 LOC_U8arr[10];
	while(Copy_U8Data>0)
	{
		LOC_U8Rem=Copy_U8Data%10;
		LOC_U8arr[LOC_U8i++]=LOC_U8Rem;  /* store remainder in array*/
		Copy_U8Data/=10;
	}
	while(LOC_U8i>0)   /*change array elements to ASCII and Display in reverse order  */
	{
		LOC_U8i--;
		LCD_VidSendData(LOC_U8arr[LOC_U8i]+'0');
	}
}
/*
 * Description : Output number (with decimal part) to LCD at current cursor position
 * Arguments   : Data as number
 * return      : void
 */
void LCD_VidSendDataFloat(f32 Copy_U8Data)
{
	if(Copy_U8Data<0.0 && Copy_U8Data>-1.0)
	{
		LCD_VidSendData('-');
	}
	f32 LOC_U8Data= Copy_U8Data-(s32)Copy_U8Data;  /*Decimal part of the number */
	LCD_VidSendDataInteger((s32)Copy_U8Data);    /*Display real part of the number */
	if(LOC_U8Data == 0.0)
	{
		return;    /*End if Decimal part is zero*/
	}
	LCD_VidSendData('.');  /* Display Decimal character*/
	s32 LOC_U8X=(u32)(LOC_U8Data*1000.0);  /*Accuracy up to 3 Decimal Digits */
	if(LOC_U8X < 0)
	{
		LOC_U8X=~(LOC_U8X)+1;    /*2nd Complement to print positive number after decimal in case number is negative*/
	}
	u32 LOC_U8Y=LOC_U8X;
	u8 LOC_U8Digit=0;
	while(LOC_U8X != 0)  /*Calculate Number of Digits after Decimal (if zero after '.' direct won't be calculated)*/
	{
		LOC_U8Digit++;
		LOC_U8X/=10;
	}
	for(u8 LOC_U8i=3;LOC_U8i>LOC_U8Digit;LOC_U8i--)  /* Display zeros after'.' direct */
	{
		LCD_VidSendDataInteger(0);
	}
	LCD_VidSendDataInteger(LOC_U8Y); /*Display Decimal number*/
}

/*
 * Description : Shift all display left one step
 * Arguments   : void
 * return      : void
 */
void LCD_VidDataShiftLeft()
{
	LCD_VidSendCommand(LCD_SHIFTLEFT);
}
/*
 * Description : Clear entire display and sets DDRaM address to 0x00
 * Arguments   : void
 * return      : void
 */
void LCD_VidClearData()
{
	LCD_VidSendCommand(DISPLAY_CLR);
}
/*
 * Description : Sets DDRaM address to 0x00 and return shifted display to original position
 * Arguments   : void
 * return      : void
 */
void LCD_VidSetDataLocation()
{
	LCD_VidSendCommand(RESET_DATA);
}
/*
 * Description : Shift all display right one step
 * Arguments   : void
 * return      : void
 */
void LCD_VidDataShiftRight()
{
	LCD_VidSendCommand(LCD_SHIFTRIGHT);
}
/*
* Description : shift cursor position one right step
* Arguments   : void
* return      : void
*/
void LCD_VidCursorShiftRight(void)
{
	LCD_VidSendCommand(LCD_CURSOR_RIGHT);
}
/*
* Description : shift cursor position one Left step
* Arguments   : void
* return      : void
*/
void LCD_VidCursorShiftLeft(void)
{
	LCD_VidSendCommand(LCD_CURSOR_LEFT);
}
/*
 * Description : Set Cursor to certain position
 * Arguments   : number of row and column
 * return      : void
 */
void LCD_VidGoToLocation(u8 LOC_U8Row,u8 LOC_U8Column)
{
	switch(LOC_U8Row)
	{
		case 0: LCD_VidSendCommand(LOC_U8Column + LCD_ADD_1LINE); break;
		case 1: LCD_VidSendCommand(LOC_U8Column + LCD_ADD_2LINE); break;
	}
}
/*
 * Description : Display data,shift it to right until first line ended then second line then return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteRotateRight(u8* Copy_U8Data)
{
	u8 LOC_U8Len=0;
		while(Copy_U8Data[LOC_U8Len]!='\0')  /*Store length of string*/
		{
			LOC_U8Len++;
		}
		u8 LOC_U8X=1,LOC_U8Y=1,LOC_U8Z=0;
		for(u8 LOC_U8i=0;LOC_U8i<16;LOC_U8i++)  /*to display data in  first line*/
		{
			LCD_VidClearData();
			LCD_VidGoToLocation(0,LOC_U8i);   /* shift display */
			LCD_VidSendDatastring(Copy_U8Data);
			if(LOC_U8i>16-LOC_U8Len)   /*to display remaining part of string in second line(not all word in same line)*/
			{
				LOC_U8X=LOC_U8Y;
				LOC_U8Z=0;
				while(LOC_U8X)
				{
					LOC_U8X--;
					LCD_VidGoToLocation(1,LOC_U8Z);
					LCD_VidSendData(Copy_U8Data[LOC_U8Len-1-LOC_U8X]);
					LOC_U8Z++;
				}
				LOC_U8Y++;
			}
			_delay_ms(50);
		}
		LOC_U8X=1,LOC_U8Y=1,LOC_U8Z=0;
		for(u8 LOC_U8i=0;LOC_U8i<16;LOC_U8i++) /*to display data in second line*/
		{
			LCD_VidClearData();
			LCD_VidGoToLocation(1,LOC_U8i);   /* shift display */
			LCD_VidSendDatastring(Copy_U8Data);
			if(LOC_U8i>16-LOC_U8Len) /*to display remaining part of string in first line(not all word in same line)*/
				{
				LOC_U8X=LOC_U8Y;
				LOC_U8Z=0;
				while(LOC_U8X)
					{
					LOC_U8X--;
					LCD_VidGoToLocation(0,LOC_U8Z);
					LCD_VidSendData(Copy_U8Data[LOC_U8Len-1-LOC_U8X]);
					LOC_U8Z++;
					}
					LOC_U8Y++;
				}
			_delay_ms(50);
		}
}
/*
 * Description : Display data,shift it to  left until second line ended then first line then return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteRotateLeft(u8* Copy_U8Data)
{
	u8 LOC_U8Len=0;
		while(Copy_U8Data[LOC_U8Len]!='\0') /*Store length of string*/
		{
			LOC_U8Len++;
		}
		LCD_VidSendDatastring(Copy_U8Data);
		_delay_ms(50);
		u8 LOC_U8X=LOC_U8Len-1,LOC_U8Y=LOC_U8Len-1,LOC_U8Z=0;
		for(s8 LOC_U8i=15;LOC_U8i>=0;LOC_U8i--)
		{
			LCD_VidClearData();
			LCD_VidGoToLocation(1,LOC_U8i);  /* shift display */
			LCD_VidSendDatastring(Copy_U8Data);
			if(LOC_U8i>16-LOC_U8Len)/*to display remaining part of string in second line(not all word in same line)*/
				{
				LOC_U8X=LOC_U8Y;
				LOC_U8Z=0;
				while(LOC_U8X)
					{
					LOC_U8X--;
					LCD_VidGoToLocation(0,LOC_U8Z);
					LCD_VidSendData(Copy_U8Data[LOC_U8Len-1-LOC_U8X]);
					LOC_U8Z++;
					}
					LOC_U8Y--;
				}
			_delay_ms(50);
		}
		LOC_U8X=LOC_U8Len-1,LOC_U8Y=LOC_U8Len-1,LOC_U8Z=0;
		for(s8 LOC_U8i=15;LOC_U8i>=0;LOC_U8i--)
		{
			LCD_VidClearData();
			LCD_VidGoToLocation(0,LOC_U8i);  /* shift display */
			LCD_VidSendDatastring(Copy_U8Data);
			if(LOC_U8i>16-LOC_U8Len)/*to display remaining part of string in first line(not all word in same line)*/
			{
				LOC_U8X=LOC_U8Y;
				LOC_U8Z=0;
				while(LOC_U8X)
				{
					LOC_U8X--;
					LCD_VidGoToLocation(1,LOC_U8Z);
					LCD_VidSendData(Copy_U8Data[LOC_U8Len-1-LOC_U8X]);
					LOC_U8Z++;
				}
				LOC_U8Y--;
			}
			_delay_ms(50);
		}
}
/*
 * Description : Display data in form of wave until it return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteSinsuoidalRotate(u8* Copy_U8Data)
{
	u8 LOC_U8Len=0;
	while(Copy_U8Data[LOC_U8Len]!='\0') /*Store length of string*/
	{
		LOC_U8Len++;
	}
	u8 LOC_U8Y=1,LOC_U8Z=0,LOC_U8C=0,LOC_U8X=0;
	for(u8 LOC_U8i=0;LOC_U8i<16;LOC_U8i++)
	{
		LCD_VidClearData();
		LCD_VidGoToLocation(LOC_U8X,LOC_U8i);  /* shift display(make wave form) */
		LCD_VidSendDatastring(Copy_U8Data);
		if(LOC_U8i>16-LOC_U8Len)/*to display remaining part of string in reverse line(not all word in same line)*/
		{
			TOGGLE_BIT(LOC_U8X,0);
			LOC_U8Z=LOC_U8Y;
			LOC_U8C=0;
			while(LOC_U8Z)
			{
				LOC_U8Z--;
				LCD_VidGoToLocation(LOC_U8X,LOC_U8C);
				LCD_VidSendData(Copy_U8Data[LOC_U8Len-1-LOC_U8Z]);
				LOC_U8C++;
			}
			LOC_U8Y++;
			TOGGLE_BIT(LOC_U8X,0);
		}
		_delay_ms(50);
		TOGGLE_BIT(LOC_U8X,0);
	}
}
