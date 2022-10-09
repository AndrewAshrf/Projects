/********************************************************************************************************/
/********************Auther: Andrew Ashraf      *********************************************************/
/********************File : INTERFACE of LCD    *********************************************************/
/********************Date : 3/9/2022            *********************************************************/
/********************Version : First version    *********************************************************/
/********************************************************************************************************/



#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

 /*
  * Description : Initialize LCD , Mode used,Number of lines and Cursor
  * Arguments   : void
  * return      : void
  */
void LCD_VidInitialize(void);
/*
 * Description : Send to command register that stores the command instructions given to the LCD
 * Arguments   : Command
 * return      : void
 */
void LCD_VidSendCommand(u8 Copy_U8Command);
/*
 * Description : Send data (in ASCII) to data register stores it to be displayed on the LCD
 * Arguments   : Data
 * return      : void
 */
void LCD_VidSendData(u8 Copy_U8Data);
/*
 * Description : Output String to LCD at current cursor position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidSendDatastring(u8* Copy_U8Data);
/*
 * Description : Output number to LCD at current cursor position
 * Arguments   : Data as number
 * return      : void
 */
void LCD_VidSendDataInteger(s32 Copy_U8Data);
/*
 * Description : Output number (with decimal part) to LCD at current cursor position
 * Arguments   : Data as number
 * return      : void
 */
void LCD_VidSendDataFloat(f32 Copy_U8Data);
/*
 * Description : Shift all display left one step
 * Arguments   : void
 * return      : void
 */
void LCD_VidDataShiftLeft(void);
/*
 * Description : Shift all display right one step
 * Arguments   : void
 * return      : void
 */
void LCD_VidDataShiftRight(void);
/*
 * Description : Clear entire display and sets DDRaM address to 0x00
 * Arguments   : void
 * return      : void
 */
void LCD_VidClearData(void);
/*
 * Description : Sets DDRaM address to 0x00 and return shifted display to original position
 * Arguments   : void
 * return      : void
 */
void LCD_VidSetDataLocation(void);
/*
 * Description : Set Cursor to certain position
 * Arguments   : number of row and column
 * return      : void
 */
void LCD_VidGoToLocation(u8 LOC_U8Row,u8 LOC_U8Column);
/*
 * Description : Display data,shift it to right until first line ended then second line then return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteRotateRight(u8* Copy_U8Data);
/*
 * Description : Display data,shift it to  left until second line ended then first line then return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteRotateLeft(u8* Copy_U8Data);
/*
 * Description : Display data in form of wave until it return to original position
 * Arguments   : Pointer to Array of data characters
 * return      : void
 */
void LCD_VidConpleteSinsuoidalRotate(u8* Copy_U8Data);
/*
* Description : shift cursor position one right step
* Arguments   : void
* return      : void
*/
void LCD_VidCursorShiftRight(void);
/*
* Description : shift cursor position one Left step
* Arguments   : void
* return      : void
*/
void LCD_VidCursorShiftLeft(void);



#endif 
