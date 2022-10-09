/****************************************************************************************************************/
/********************Auther: Andrew Ashraf      *****************************************************************/
/********************File : PRIVATE of KEYPAD   *****************************************************************/
/********************Date : 3/9/2022            *****************************************************************/
/********************Version : First version    *****************************************************************/
/****************************************************************************************************************/
#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

/*private macros*/
#define CALC_KEYPAD    0
#define LETTER_KEYPAD  1
#define NUMBER_KEYPAD  2

#define KPD_INIT_VALUE  127
#define KPD_DELAY       8


/*
 * Initialize number of rows and columns
 * Define Array of inputs
 */
#if KEYPAD_TYPE == CALC_KEYPAD

#define ROWS_NO 4
#define COLUMNS_NO 4
u8 keypad[ROWS_NO][COLUMNS_NO]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{' ','0','=','+'}
};

#elif KEYPAD_TYPE == LETTER_KEYPAD

#define ROWS_NO 4
#define COLUMNS_NO 4
u8 keypad[ROWS_NO][COLUMNS_NO]=
{
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
#elif KEYPAD_TYPE == NUMBER_KEYPAD

#define ROWS_NO 4
#define COLUMNS_NO 3
u8 keypad[ROWS_NO][COLUMNS_NO]=
{
	{'1','2','3'},
	{'4','5','6'},
	{'7','8','9'},
	{'*','0','#'}
};
#else
#error "WRONG KEYPAD SELECTION"
#endif

#endif 
 
