/**********************************************************************************************************/
/********************  Auther: Andrew Ashraf      *********************************************************/
/********************  File : Main of Calculator  *********************************************************/
/********************  Date : 1/10/2022           *********************************************************/
/********************  Version : Second version    ********************************************************/
/********************  Describtion: Simple Calculator *****************************************************/
/**********************************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include"LCD_interface.h"
#include"DIO_interface.h"
#include "KEYPAD_interface.h"
#include "avr/delay.h"

#define KPD_PORT B    /* Port Connected to Keypad */

void welcome(void);
u8 IsNum(u8 Copy_U8X);
u8 IsOperand(u8 Copy_U8X);

void main (void)
{
	LCD_VidInitialize();
	KEYPAD_vidInitialize(KPD_PORT);
	welcome();
	u8 LOC_U8Inp=0,LOC_U8Y=0, LOC_U8X=0, LOC_U8End=0, LOC_U8P=0,LOC_U8Com=0;
	u8 LOC_U8NumFlag=0,LOC_U8EqualFlag=0,LOC_U8OperandFlag=0;
	u8 LOC_U8ClearFlag=0,LOC_U8ResetFlag=0,LOC_U8CalcFlag=0;
	f32 LOC_F32Res=0;
	f32 LOC_F32Equation[30]={0};
	f32 LOC_F32Inputs[30]={0};
	u8 LOC_U8Z=0,LOC_U8Count=0,LOC_U8NegNO=0;
	while(1)
	{
/**********************************************RESET*****************************************************/
		if(LOC_U8ResetFlag==1)
		{
			/* Reset all values (return to 0)*/
    		for(u8 LOC_U8i=0;LOC_U8i<=LOC_U8Z;LOC_U8i++)
    		{
     			LOC_F32Inputs[LOC_U8i]=0;
     			LOC_F32Equation[LOC_U8i]=0;
		  	}
    		LOC_U8Z=0,LOC_U8Count=0,LOC_U8Com=0, LOC_U8P=0;
    		LOC_U8NumFlag=0,LOC_U8EqualFlag=0,LOC_U8OperandFlag=0;
    		LOC_U8ClearFlag=0,LOC_U8ResetFlag=0,LOC_U8CalcFlag=0;
    		LCD_VidSetDataLocation();
		}
		/* Get value or order entered by user as input*/
		LOC_U8Inp=KEYPAD_U8GetPressedKey(KPD_PORT);
		if(LOC_U8Inp ==127){continue;} /*means no input by user*/
/***************************************INPUT NUMBER****************************************************/
		if(IsNum(LOC_U8Inp))
		{
			/* if input is number ,number flag opens*/
			LOC_U8NumFlag=1;
		}
/***************************************INPUT OPERAND***************************************************/
		else if(IsOperand(LOC_U8Inp))
		{
			/* if input is operand ,operand flag opens*/
			LOC_U8OperandFlag=1;
		}
/***************************************INPUT CLEAR*****************************************************/
		else if(LOC_U8Inp==' ')
		{
			/* if input order is clear ,clear flag opens*/
			LOC_U8ClearFlag=1;
		}
/***************************************INPUT EQUAL*****************************************************/
		else if(LOC_U8Inp=='=')
		{
			/* if input order is equal ,equal flag opens*/
			LOC_U8EqualFlag=1;
		}
/************************************** TESTCASE *******************************************************/
		if(LOC_U8NumFlag==1 && LOC_U8EqualFlag==1)
		{
			/*When result on LCD,and user enter number-> Don't do anything */
			LOC_U8NumFlag=0;
			continue;
		}
/***************************************FLAG NUMBER*****************************************************/
		else if(LOC_U8NumFlag==1 )
		{
			/*if number flag opened,display this number on LCD and
			 store it in array of inputs by its ASCII value */
			LOC_U8NumFlag=0;
			LCD_VidSendData(LOC_U8Inp);
			LOC_U8Count++;
			LOC_F32Inputs[LOC_U8Z++]=LOC_U8Inp;
		}
/***************************************FLAG CLEAR AFTER RESULT****************************************/
		else if(LOC_U8EqualFlag==1 && LOC_U8ClearFlag==1)
		{
			/*if User enter Clear order after display result,
			 reset all values and clear screen */
    		LOC_U8ResetFlag=1;
    		LCD_VidClearData();
    		LCD_VidSetDataLocation();
		}
/***************************************FLAG OPERAND AFTER RESULT***************************************/
		else if(LOC_U8EqualFlag==1 && LOC_U8OperandFlag==1)
		{
			/*if User enter operand after display result(complete operations by using result),
			 clear screen,display result and operand entered by user
			 reset values except array of equation(result stored in it)  */
    		LOC_U8EqualFlag=0;      /*begin new operation*/
    		LOC_U8OperandFlag=0;
    		LCD_VidClearData();
    		LCD_VidSetDataLocation();
    		LCD_VidSendDataFloat(LOC_F32Res);  /*display last result*/
    		LCD_VidSendData(LOC_U8Inp);        /*display operand entered by user*/
    		for(u8 LOC_U8i=0;LOC_U8i<LOC_U8Z;LOC_U8i++)
    		{
     			LOC_F32Inputs[LOC_U8i]=0;
     			LOC_F32Equation[LOC_U8i]=0;
		  	}
    		LOC_F32Equation[0]=LOC_F32Res;
    		/*Calculate count to know number of elements on LCD  */
    		LOC_U8Count=1;
    		if(LOC_F32Res<0.0)
    			LOC_U8Count++;
    		if(LOC_F32Res!=(s32)LOC_F32Res)
    		{
    			LOC_U8Count+=4;
    		}
    		while((u32)LOC_F32Res !=0)
    		{
    			LOC_F32Res/=10;
    			LOC_U8Count++;
    		}
    		LOC_U8Com=1;   /*complete operation by last result  */
    		LOC_U8Z=0;
    		LOC_F32Inputs[LOC_U8Z++]=LOC_U8Inp;
		}
/***************************************FLAG OPERAND ***********************************************/
		else if(LOC_U8OperandFlag==1)
		{
			/*if operand flag opened,display this operand on LCD and
			 store it in array of inputs by its ASCII value */
			LOC_U8OperandFlag=0;
			LCD_VidSendData(LOC_U8Inp);
			LOC_U8Count++;
			LOC_F32Inputs[LOC_U8Z++]=LOC_U8Inp;
		}
/***************************************FLAG CLEAR *************************************************/
		else if(LOC_U8ClearFlag==1)
		{
			/*if User enter Clear order before display result,
			 Clear last element in array of inputs and on screen*/
			LOC_U8ClearFlag=0;
			if(LOC_U8Count==16)
				LCD_VidGoToLocation(0,16);
			if(LOC_U8Z==0 && LOC_U8Com==1)
			{
				/*if User enter Clear order (case on screen result of previous operation only ),
				 Clear this result and reset all values */
				LOC_U8ResetFlag=1;
				LCD_VidClearData();
				LCD_VidSetDataLocation();
			}
			if(LOC_U8Z==0)
				continue;
			/*shift cursor left then clear*/
			LCD_VidCursorShiftLeft();
			LCD_VidSendData(' ');
			LOC_U8Z--;
			LOC_F32Inputs[LOC_U8Z]=0;
			LCD_VidCursorShiftLeft();
			LOC_U8Count--;
		}
/***************************************FLAG EQUAL *************************************************/
		else if(LOC_U8EqualFlag==1)
		{
			/*if User press equal button (result needed),
			 Display equal , check some TestCases,
			 convert input numbers from ASCII to decimal and store it in array of equation,
			 operands store as ASCII and opens calculation flag */
			if(LOC_U8Z==0)   /*if user enter equal sign in first of operation ->Don't do anything*/
				{
				LOC_U8EqualFlag=0;
				continue;
				}
			LCD_VidSendData(LOC_U8Inp);  /*Display equal sign on LCD*/
			LOC_U8Count++;
/************************************** TESTCASE *******************************************************/
			if(LOC_F32Inputs[0]=='-'&& IsNum(LOC_F32Inputs[1]) && LOC_U8Com==0)
			{
				/* if user enter negative sign then number means negative number at first operation*/
				for(u8 LOC_U8j=0;LOC_U8j<LOC_U8Z;LOC_U8j++)
				{
					LOC_F32Inputs[LOC_U8j]=LOC_F32Inputs[LOC_U8j+1]; /*shift all array elements  by one to left */
				}
				LOC_U8NegNO=1;  /*negative number flag opens*/
				LOC_U8Z--,LOC_U8Count--;
			}
/************************************** TESTCASE *******************************************************/
			if(IsOperand(LOC_F32Inputs[0]) && LOC_U8Com==0)
			{
				/* if user enter operand in first , Display error and reset	 */
				LCD_VidGoToLocation(1,11);
				LCD_VidSendDatastring("ERROR");
				_delay_ms(1000);
				LCD_VidClearData();
				LCD_VidSetDataLocation();
				LOC_U8ResetFlag=1;
				continue;
			}
			LOC_U8CalcFlag=1; /*Calculation Flag opens*/
			if(LOC_U8Com==1)
			{
				LOC_U8Com=0,LOC_U8P=0;
			}
			for(u8 LOC_U8i=0;LOC_U8i<LOC_U8Z;LOC_U8i++)
			{
				if(IsNum(LOC_F32Inputs[LOC_U8i]))
				{
					/*change numbers from ASCII to decimal, do concatenation to all numbers before operands	 */
					LOC_F32Inputs[LOC_U8i]-='0';
					LOC_F32Equation[LOC_U8P]=LOC_F32Equation[LOC_U8P]*10+LOC_F32Inputs[LOC_U8i];
				}
				else if(IsOperand(LOC_F32Inputs[LOC_U8i]))
				{
					/* store ASCII values of operands in array of equation */
					if(LOC_U8NegNO==1)
					{
						LOC_U8NegNO=0;
						LOC_F32Equation[LOC_U8P]*=(-1.0); /*if negative flag opened ->Add negative sign to this number*/
					}
					LOC_U8P++;
					LOC_F32Equation[LOC_U8P]=LOC_F32Inputs[LOC_U8i];
					LOC_U8P++;
				}
	/************************************** TESTCASE *******************************************************/
				if(IsOperand(LOC_F32Inputs[LOC_U8i]) && LOC_F32Inputs[LOC_U8i+1]=='-'&& IsNum(LOC_F32Inputs[LOC_U8i+2])  )
				{
					/* if user enter two operand in sequence and second one is negative sign then entered number
					 ->Add negative sign to this number*/
					for(u8 LOC_U8j=LOC_U8i+1;LOC_U8j<LOC_U8Z;LOC_U8j++)
					{
						LOC_F32Inputs[LOC_U8j]=LOC_F32Inputs[LOC_U8j+1];
					}
					LOC_U8NegNO=1;
					LOC_U8Z--,LOC_U8Count--;
				}
/************************************** TESTCASE *******************************************************/
				else if(IsOperand(LOC_F32Inputs[LOC_U8i]) && IsOperand(LOC_F32Inputs[LOC_U8i+1]))
				{
					/* if user enter two operand in sequence without numbers in between, Display error and reset*/
					LCD_VidGoToLocation(1,11);
					LCD_VidSendDatastring("ERROR");
					_delay_ms(1000);
					LCD_VidClearData();
					LCD_VidSetDataLocation();
					LOC_U8ResetFlag=1;
					LOC_U8CalcFlag=0;
					break;
				}
/************************************** TESTCASE *******************************************************/
				if(IsOperand(LOC_F32Inputs[LOC_U8i]) && !IsOperand(LOC_F32Inputs[LOC_U8i+1]) && !IsNum(LOC_F32Inputs[LOC_U8i+1]))
				{
					/* if user enter operand at end then press equal, Display error and reset*/
					LCD_VidGoToLocation(1,11);
					LCD_VidSendDatastring("ERROR");
					_delay_ms(1000);
					LCD_VidClearData();
					LCD_VidSetDataLocation();
					LOC_U8ResetFlag=1;
					LOC_U8CalcFlag=0;
					break;
				}
			}
			if(LOC_U8NegNO==1)
			{
				LOC_U8NegNO=0;
				LOC_F32Equation[LOC_U8P]*=(-1.0);/*if negative flag opened ->Add negative sign to this number*/
			}
		}
/************************************** CALCULATION FLAG *****************************************************/
		if(LOC_U8CalcFlag==1)
		{
			/* if calculation flag open, calculate result by
			doing all multiply and divide operations (HIGH priority)
			doing all addition and subtraction operations (LOW priority)
			Display result*/
			LOC_U8CalcFlag=0;
			LOC_U8Y=LOC_U8P/2; /* number of operations needed */
			while(LOC_U8Y)
			{
			for(u8 LOC_U8i=0;LOC_U8i<=LOC_U8P;LOC_U8i++)
			{
				if( LOC_F32Equation[LOC_U8i]=='*' && LOC_U8i%2 !=0)
				{
					LOC_F32Equation[LOC_U8i-1]*=LOC_F32Equation[LOC_U8i+1];
					for(u8 LOC_U8j=LOC_U8i;LOC_U8j<=LOC_U8P;LOC_U8j++)
					{
						/*
						 * Shift remaining elements in array in space area
						 ex: 32 + 5 * 12 + 3
						     32 + 60     + 3
						     32 + 60 + 3
						*/
						LOC_F32Equation[LOC_U8j]=LOC_F32Equation[LOC_U8j+2];
					}
					LOC_U8Y--;
					LOC_U8X=1;
					/* to prevent entering second for loop (in which addition and subtraction)
					until all multiply and divide operations end  so it continues in while loop*/
					break;
				}
				else if(LOC_F32Equation[LOC_U8i]=='/' && LOC_U8i%2 !=0)
				{
/************************************** TESTCASE *******************************************************/
					if(LOC_F32Equation[LOC_U8i+1]==0)
					{
						/* Give Error to user and reset when divide on zero(No Meaning) */
						LCD_VidGoToLocation(1,11);
						LCD_VidSendDatastring("ERROR");
						_delay_ms(1000);
						LCD_VidClearData();
						LCD_VidSetDataLocation();
						LOC_U8ResetFlag=1;
						LOC_U8End=1; /* to end while loop  */
						break;
					}
					LOC_F32Equation[LOC_U8i-1]/=LOC_F32Equation[LOC_U8i+1];
					for(u8 LOC_U8j=LOC_U8i;LOC_U8j<=LOC_U8P;LOC_U8j++)
					{
						/*
						 * Shift remaining elements in array in space area
						 ex: 32 + 60 / 12 + 3
						     32 + 5     + 3
						     32 + 5 + 3
						*/
						LOC_F32Equation[LOC_U8j]=LOC_F32Equation[LOC_U8j+2];
					}
					LOC_U8Y--;
					LOC_U8X=1;
					/* to prevent entering second for loop (in which addition and subtraction)
					until all multiply and divide operations end  so it continues in while loop*/
					break;
				}
			}
			if(LOC_U8End==1){LOC_U8End=0; break;}
			if(LOC_U8X==1){LOC_U8X=0; continue;}
			for(u8 LOC_U8i=0;LOC_U8i<=LOC_U8P;LOC_U8i++)
			{
				if(LOC_F32Equation[LOC_U8i]=='+' && LOC_U8i%2 !=0)
				{
					LOC_F32Equation[LOC_U8i-1]+=LOC_F32Equation[LOC_U8i+1];
					for(u8 LOC_U8j=LOC_U8i;LOC_U8j<=LOC_U8P;LOC_U8j++)
					{
						/*
						 * Shift remaining elements in array in space area
						 ex: 32 + 12 + 3
						     44      + 3
						     44 + 3
						*/
						LOC_F32Equation[LOC_U8j]=LOC_F32Equation[LOC_U8j+2];
					}
					LOC_U8Y--;
					break;
				}
				else if(LOC_F32Equation[LOC_U8i]=='-' && LOC_U8i%2 !=0)
				{
					LOC_F32Equation[LOC_U8i-1]-=LOC_F32Equation[LOC_U8i+1];
					for(u8 LOC_U8j=LOC_U8i;LOC_U8j<=LOC_U8P;LOC_U8j++)
					{
						/*
						 * Shift remaining elements in array in space area
						 ex: 32 - 12 + 3
						     20      + 3
						     20 + 3
						*/
						LOC_F32Equation[LOC_U8j]=LOC_F32Equation[LOC_U8j+2];
					}
					LOC_U8Y--;
					break;
				}
			}
			}
			if(LOC_U8ResetFlag==0)
			{
				if(LOC_U8Count>9 && LOC_U8Count<=16)
				{
					LCD_VidGoToLocation(1,0);
				}
				LOC_F32Res=LOC_F32Equation[0];
				LCD_VidSendDataFloat(LOC_F32Res); /* store result and display it  */
				_delay_ms(500);
			}
		}
		if(LOC_U8Count==16 && LOC_U8EqualFlag==0)
		{
			/* to go to second line if first line completed */
			LCD_VidGoToLocation(1,0);
		}
/************************************** TESTCASE *******************************************************/
		else if(LOC_U8Count==29)
		{
			/* Display Overflow error if two Lines Completed and reset */
			LCD_VidClearData();
			LCD_VidSetDataLocation();
			LCD_VidSendDatastring("OVERFLOW");
			_delay_ms(500);
			LCD_VidClearData();
			LCD_VidSetDataLocation();
		}
	}
}

/*
 * Description : Check if this input is number or not.
 * Arguments   : input entered by user
 * return      : 0 -> if input is not (from ASCII of 0 to ASCII of 9)
                 1 -> if input is number (This check in ASCII)
 */
u8 IsNum(u8 Copy_U8X)
{
	/* Check if input is number */
	if(Copy_U8X>='0' && Copy_U8X<='9')
		return 1;
	else
		return 0;
}
/*
 * Description : Check if this input is operand or not.
 * Arguments   : input entered by user
 * return      : 0 -> if input is not operand
                 1 -> if input is operand (This check in ASCII)
 */
u8 IsOperand(u8 Copy_U8X)
{
	/* Check if input is operand (+,-,*,/) */
	if(Copy_U8X=='+' || Copy_U8X=='-' || Copy_U8X=='*' || Copy_U8X=='/')
		return 1;
	else
		return 0;
}
/*
 * Description : Display welcome message
 * Arguments   : void
 * return      : void
 */
void welcome(void)
{
	LCD_VidSendDatastring("SimpleCalculator");
	LCD_VidGoToLocation(1,2);
	LCD_VidSendDatastring("By Andrew");
	_delay_ms(1000);
	LCD_VidClearData();
	LCD_VidSetDataLocation();
}

