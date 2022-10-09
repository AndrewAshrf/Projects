/***************************************************************************************************/
/********************Auther: Andrew Ashraf      ****************************************************/
/********************File : INTERFACE of DIO    ****************************************************/
/********************Date : 3/9/2022            ****************************************************/
/********************Version : First version    ****************************************************/
/***************************************************************************************************/



#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/*
 * Description : Set direction of certain Pin in this Port
 * Arguments   : Port , Pin , Value
 * return      : void
 */
void DIO_VidSetPinDirection(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Dir);
/*
 * Description : Set value of Pin in this Port
 * Arguments   : Port ,Pin ,Value
 * return      : void
 */
void DIO_VidSetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin,u8 Copy_U8Value);
/*
 * Description : Gets value of certain Pin in this Port
 * Arguments   : Port ,Pin
 * return      : u8(1 or 0)
 */
u8 DIO_U8GetPinValue(u8 Copy_U8Port,u8 Copy_U8Pin);
/*
 * Description : Toggles value of Pin in this Port
 * Arguments   : Port ,Pin
 * return      : void
 */
void DIO_vidTogglePinValue(u8 Copy_U8Port,u8 Copy_U8Pin);
/*
 * Description : Set value of the whole register
 * Arguments   : Port ,Value
 * return      : void
 */
void DIO_VidSetPortValue(u8 Copy_U8Port,u8 Copy_U8Value);
/*
 * Description : Set direction of the whole register
 * Arguments   : Port , Value
 * return      : void
 */
void DIO_VidSetPortDirection(u8 Copy_U8Port,u8 Copy_U8Dir);



#endif 
