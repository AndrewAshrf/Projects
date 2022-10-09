/*********************************************************************************************************/
/********************Auther: Andrew Ashraf      **********************************************************/
/********************File : PRIVATE of LCD      **********************************************************/
/********************Date : 3/9/2022            **********************************************************/
/********************Version : First version    **********************************************************/
/*********************************************************************************************************/
#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_
/* Private Macros*/
#define OFF 0
#define ON  1

#define FOUR_BITS   0
#define EIGHT_BITS  1

#define TWO_LINES  1
#define ONE_LINE   0

#define NULL      '\0'

#define LCD_SHIFTLEFT        0b00011000
#define LCD_SHIFTRIGHT       0b00011100
#define LCD_CURSOR_LEFT      0b00010000
#define LCD_CURSOR_RIGHT     0b00010100

 #define LCD_ADD_1LINE		  0b10000000
 #define LCD_ADD_2LINE		  0b11000000

#define  BIT7     7
#define  BIT6     6
#define  BIT5     5
#define  BIT4     4
#define  BIT3     3
#define  BIT2     2
#define  BIT1     1
#define  BIT0     0
       
#define DISPLAY_CLR  0b00000001
#define RESET_DATA   0b00000010

#if INTERFACE_LEN == EIGHT_BITS

#if LINES_NO == TWO_LINES
#define FUNC_SET     0b00111000  /*  8 bits and 2 lines selected*/
#elif LINES_NO == ONE_LINE
#define FUNC_SET     0b00110000   /*  8 bits and 1 line selected*/
#endif

#elif INTERFACE_LEN == FOUR_BITS

#if LINES_NO == TWO_LINES
#define FUNC_SET     0b00101000   /*  4 bits and 2 lines selected*/
#elif LINES_NO == ONE_LINE
#define FUNC_SET     0b00100000    /*  4 bits and 1 line selected*/
#endif
#endif

#if DISPLAY  == ON
#if CURSOR  == ON
#if CURSOR_BLINK == ON
#define LCD_DISPLAY  0b00001111   /* Display on, Cursor on ,Cursor Blink on*/
#elif CURSOR_BLINK == OFF
#define LCD_DISPLAY  0b00001110   /* Display on, Cursor on ,Cursor Blink off*/
#endif
#elif CURSOR  == OFF
#if CURSOR_BLINK == ON
#define LCD_DISPLAY  0b00001101    /* Display on, Cursor off ,Cursor Blink on*/
#elif CURSOR_BLINK == OFF
#define LCD_DISPLAY  0b00001100    /* Display on, Cursor off ,Cursor Blink off*/
#endif
#endif
#elif DISPLAY  == OFF             /* Display off, Cursor off ,Cursor Blink off*/
#define LCD_DISPLAY  0b00001000
#endif




#endif 
