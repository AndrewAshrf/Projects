/****************************************************************************************************/
/********************Auther: Andrew Ashraf      *****************************************************/
/********************File : PRIVATE of DIO      *****************************************************/
/********************Date : 3/9/2022            *****************************************************/
/********************Version : First version    *****************************************************/
/****************************************************************************************************/
#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

/*PORT Macro Definition*/
#define PORTA_REG   *((u8*)0x3B)
#define PORTB_REG   *((u8*)0x38)
#define PORTC_REG   *((u8*)0x35)
#define PORTD_REG   *((u8*)0x32)

/*DDR  Macro Definition*/
#define DDRA_REG    *((u8*)0x3A)
#define DDRB_REG    *((u8*)0x37)
#define DDRC_REG    *((u8*)0x34)
#define DDRD_REG    *((u8*)0x31)

/*PIN  Macro Definition*/
#define PINA_REG    *((volatile u8*)0x39)
#define PINB_REG    *((volatile u8*)0x36)
#define PINC_REG    *((volatile u8*)0x33)
#define PIND_REG    *((volatile u8*)0x30)



#endif 
