/*
 * @Author: Jingqing3948 2351290287@qq.com
 * @Date: 2023-02-08 01:35:28
 * @LastEditors: Jingqing3948 2351290287@qq.com
 * @LastEditTime: 2023-03-26 23:13:24
 * @Description: use LCD to display char, string, pow num, num, etc.
 *
 * Copyright (c) 2023 by Jingqing3948 2351290287@qq.com, All Rights Reserved.
 */
#include "LCD1602.H"

/**
 * @brief a delay function for LCD.
 * @return {*}
 */
void LCD_Delay()
{
	unsigned char i, j;

	i = 2;
	j = 239;
	do
	{
		while (--j)
			;
	} while (--i);
}

/**
 * @brief  write a command to LCD1602.
 * @param  {unsigned char} Command the command needs to be written.
 * @return {*}
 */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS = 0;
	LCD_RW = 0;
	LCD_DataPort = Command;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
 * @brief write a data to LCD1602.
 * @param {unsigned char} Data the data needs to be written.
 * @return {*}
 */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS = 1;
	LCD_RW = 0;
	LCD_DataPort = Data;
	LCD_EN = 1;
	LCD_Delay();
	LCD_EN = 0;
	LCD_Delay();
}

/**
 * @brief set cursor location
 * @param {unsigned char} Line (1~2)
 * @param {unsigned char} Column (1~16)
 * @return {*}
 */
void LCD_SetCursor(unsigned char Line, unsigned char Column)
{
	if (Line == 1)
	{
		LCD_WriteCommand(0x80 | (Column - 1));
	}
	else if (Line == 2)
	{
		LCD_WriteCommand(0x80 | (Column - 1 + 0x40));
	}
}

/**
 * @brief  LCD1602 init function
 * @return {*}
 */
void LCD_Init()
{
	LCD_WriteCommand(0x38); // 8 bit data interface, displays in 2 line, 5*7 lattice
	LCD_WriteCommand(0x0c); // enable display, close cursor, close flicker
	LCD_WriteCommand(0x06); // after read or write, cursor++ without moving screen
	LCD_WriteCommand(0x01); // reset cursor location and clear the screen
}

/**
 * @brief show a char on LCD at given location
 * @param {unsigned char} Line: display on line 1 or 2
 * @param {unsigned char} Column: display on which  (1~16)
 * @param {char} Char: the char character to be displayed
 * @return {*}
 */
void LCD_ShowChar(unsigned char Line, unsigned char Column, char Char)
{
	LCD_SetCursor(Line, Column);
	LCD_WriteData(Char);
}

/**
 * @brief show a string on LCD at given location
 * @param {unsigned char} Line: display on line 1 or 2
 * @param {unsigned char} Column: display on which  (1~16)
 * @param {char} *String: the string to be displayed
 * @return {*}
 */
void LCD_ShowString(unsigned char Line, unsigned char Column, char *String)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = 0; String[i] != '\0'; i++)
	{
		LCD_WriteData(String[i]);
	}
}

/**
 * @brief return X^Y
 * @param {int} X
 * @param {int} Y
 * @return {*}
 */
int LCD_Pow(int X, int Y)
{
	unsigned char i;
	int Result = 1;
	for (i = 0; i < Y; i++)
	{
		Result *= X;
	}
	return Result;
}

/**
 * @brief show a number on LCD at given location
 * @param {unsigned char} Line
 * @param {unsigned char} Column
 * @param {unsigned int} Number
 * @param {unsigned char} Length: the length of given number
 * @return {*}
 */
void LCD_ShowNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief show a number on LCD at given location
 * @param {unsigned char} Line
 * @param {unsigned char} Column
 * @param {int} Number
 * @param {unsigned char} Length
 * @return {*}
 */
void LCD_ShowSignedNum(unsigned char Line, unsigned char Column, int Number, unsigned char Length)
{
	unsigned char i;
	unsigned int Number1;
	LCD_SetCursor(Line, Column);
	if (Number >= 0)
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;
	}
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number1 / LCD_Pow(10, i - 1) % 10 + '0');
	}
}

/**
 * @brief show a hex number on LCD at given location
 * @param {unsigned char} Line
 * @param {unsigned char} Column
 * @param {unsigned int} Number
 * @param {unsigned char} Length
 * @return {*}
 */
void LCD_ShowHexNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i, SingleNumber;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		SingleNumber = Number / LCD_Pow(16, i - 1) % 16;
		if (SingleNumber < 10)
		{
			LCD_WriteData(SingleNumber + '0');
		}
		else
		{
			LCD_WriteData(SingleNumber - 10 + 'A');
		}
	}
}

/**
 * @brief show a bin number on LCD at given location
 * @param {unsigned char} Line
 * @param {unsigned char} Column
 * @param {unsigned int} Number
 * @param {unsigned char} Length
 * @return {*}
 */
void LCD_ShowBinNum(unsigned char Line, unsigned char Column, unsigned int Number, unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line, Column);
	for (i = Length; i > 0; i--)
	{
		LCD_WriteData(Number / LCD_Pow(2, i - 1) % 2 + '0');
	}
}