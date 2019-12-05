/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _LCD_H_
#define _LCD_H_

void LCD_Init(void);
void LCD_Clear(void);
void LCD_ControlDisplay(void);
void LCD_4Bits(void);
void LCD_IncrementarCursor(void);
void LCD_Linea1(void);
void LCD_Linea2 (void);
void LCD_CursorON(void);
void LCD_Write(unsigned char character);
void LCD_Escribe(unsigned char dato, unsigned char tipo_dato);
void CCWRPS(void);
void LCD_FIN(void);


#endif
/* [] END OF FILE */
