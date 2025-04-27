#ifndef I2C_LCD_H
#define I2C_LCD_H

#include <stdint.h>
#include "i2c_dma_midderware.h"

/**
 * @brief Initializes the LCD.
 * @param lcd: Pointer to the LCD handle
 */
void lcd_init();

/**
 * @brief Sends a command to the LCD.
 * @param lcd: Pointer to the LCD handle
 * @param cmd: Command byte to send
 */
void lcd_send_cmd(char cmd);

/**
 * @brief Sends data (character) to the LCD.
 * @param lcd: Pointer to the LCD handle
 * @param data: Data byte to send
 */
void lcd_send_data(char data);

/**
 * @brief Sends a single character to the LCD.
 * @param lcd: Pointer to the LCD handle
 * @param ch: Character to send
 */
void lcd_putchar(char ch);

/**
 * @brief Sends a string to the LCD.
 * @param lcd: Pointer to the LCD handle
 * @param str: Null-terminated string to send
 */
void lcd_puts(char *str);

/**
 * @brief Moves the cursor to a specific position on the LCD.
 * @param lcd: Pointer to the LCD handle
 * @param col: Column number (0-15)
 * @param row: Row number (0 or 1)
 */
void lcd_gotoxy(int col, int row);

/**
 * @brief Clears the LCD display.
 * @param lcd: Pointer to the LCD handle
 */
void lcd_clear();

#endif /* I2C_LCD_H */