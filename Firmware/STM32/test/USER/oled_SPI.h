//////////////////////////////////////////////////////////////////////////////////
//?????????,??????,??????????
//?????
//????:http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  ? ? ?   : main.c
//  ? ? ?   : v2.0
//  ?    ?   : HuangKai
//  ????   : 2014-0101
//  ????   :
//  ????   : OLED 4??????(51??)
//              ??:
//              ----------------------------------------------------------------
//              GND    ???
//              VCC  ?5V?3.3v??
//              D0   ?PA5(SCL)
//              D1   ?PA7(SDA)
//              RES  ?PB0
//              DC   ?PB1
//              CS   ?PA4
//              ----------------------------------------------------------------
// ????   :
// ?    ?   :
// ?    ?   : HuangKai
// ????   : ????
//????,?????
//Copyright(C) ?????2014/3/16
//All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H
#include "stm32f10x.h"
#include "stdlib.h"
//OLED????
//0:4?????
//1:??8080??
#define OLED_MODE 0
#define SIZE 16
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64

//-----------------OLED????----------------

#define OLED_SCLK_Clr() GPIOB->ODR &= ~(0x01 << 12); //CLK
#define OLED_SCLK_Set() GPIOB->ODR |= (0x01 << 12);

#define OLED_SDIN_Clr() GPIOB->ODR &= ~(0x01 << 5) //DIN
#define OLED_SDIN_Set() GPIOB->ODR |= (0x01 << 5)

#define OLED_RST_Clr() GPIOB->ODR &= ~(0x01 << 13); //RES
#define OLED_RST_Set() GPIOB->ODR |= (0x01 << 13);

#define OLED_DC_Clr() GPIOB->ODR &= ~(0x01 << 0) //DC
#define OLED_DC_Set() GPIOB->ODR |= (0x01 << 0)

#define OLED_CS_Clr() GPIOB->ODR &= ~(0x01 << 7); //CS
#define OLED_CS_Set() GPIOB->ODR |= (0x01 << 7);

#define OLED_CMD 0  //???
#define OLED_DATA 1 //???

//OLED?????
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr);
void OLED_ShowNum(uint8_t x, uint8_t y, u32 num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
#endif
