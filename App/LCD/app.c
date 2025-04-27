#include "app.h"

void Init_LCD()
{
  /* timer initialize */
    if (SysTick_Config(SystemCoreClock / 1000))
    { 
      /* Capture error */ 
      while (1);
    }
    I2c_Midderware_Init();
    lcd_init();
}
void display(char Buffer[])
{
  lcd_gotoxy(1, 1);
  lcd_puts(Buffer);
}