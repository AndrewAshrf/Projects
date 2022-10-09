/**************************************************************************************************************/
/********************Auther: Andrew Ashraf      ***************************************************************/
/********************File : INTERFACE of KEYPAD ***************************************************************/
/********************Date : 3/9/2022            ***************************************************************/
/********************Version : First version    ***************************************************************/
/**************************************************************************************************************/



#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/*
 * Description : initialize keypad at a given port
 * Arguments   : void
 * Return      : void
 */
void KEYPAD_vidInitialize(u8 Copy_U8Port);

/*
 * Description : return ASCII value of pressed Key
 * Arguments   : void
 * Return      : u8
 */
u8 KEYPAD_U8GetPressedKey(u8 Copy_U8Port);


#endif 
