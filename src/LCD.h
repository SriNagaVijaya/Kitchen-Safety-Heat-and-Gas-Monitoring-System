//LCD.h
#include "types.h"
void WRITE_LCD_CMD(u8 cmd);
void Init_LCD(void);
void WRITE_LCD_DATA(u8 ascii);
void StrLCD(s8* str);
void U32LCD(u32 n);
void S32LCD(s32 n);
void F32LCD(f32 fn, u8 nDP);
void BuildCGRAM(u8* p, u8 nb);


