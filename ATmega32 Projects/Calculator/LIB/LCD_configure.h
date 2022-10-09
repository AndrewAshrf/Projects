/***********************************************************************************************************/
/********************Auther: Andrew Ashraf      ************************************************************/
/********************File : CONFIGURE of LCD      **********************************************************/
/********************Date : 3/9/2022            ************************************************************/
/********************Version : First version    ************************************************************/
/***********************************************************************************************************/
#ifndef LCD_CONFIGURE_H_
#define LCD_CONFIGURE_H_

/*
 * DATA AND CONTROL ports
 * written as:
 * A or 0
 * B or 1
 * C or 2
 * D or 3
 */
#define DATA_PORT    C
#define CONTROL_PORT D

/*
 * write pins of control port from 0 to 7
 */
#define Rs           0
#define Rw           1
#define En           2

/*
 * ON or 1 to enable display/cursor/cursor blinking
 * OFF or 0 to disable display/cursor/cursor blinking
 * NOTE : when display is off cursor and cursor blinking will be off
 */
#define DISPLAY      ON
#define CURSOR       ON
#define CURSOR_BLINK ON

/*
 * lines number choose:
 * TWO_LINES or 1
 * ONE_LINE or 0
 *
 * Interface data length choose:
 * FOUR_BITS or 0
 * EIGHT_BITS or 1
 */
#define LINES_NO        TWO_LINES
#define INTERFACE_LEN   EIGHT_BITS

/*
 * this to choose pins ""in case of four bits only""
 */
#define P0  4
#define P1  5
#define P2  6
#define P3  7


#endif 
