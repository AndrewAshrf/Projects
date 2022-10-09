/**************************************************************************************************************/
/********************Auther: Andrew Ashraf      ***************************************************************/
/********************File : BIT MATH            ***************************************************************/
/********************Date : 3/9/2022            ***************************************************************/
/********************Version : First version    ***************************************************************/
/**************************************************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var,bit) var= var|(1<<bit)
#define CLR_BIT(var,bit) var= var&(~(1<<bit))
#define GET_BIT(var,bit) (var>>(bit))&1
#define TOGGLE_BIT(var,bit) var= var^(1<<bit)

#endif
