#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "I2c_Lcd.h"

void Init_LCD();
void display(char Buffer[]);

#ifdef __cplusplus
}
#endif

#endif