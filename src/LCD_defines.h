//LCD_defines.h

//LCD pin defines
#define LCD_DATA 8
#define LCD_RS 16
#define LCD_RW 17
#define LCD_EN 18

//LCD commands
#define CLEAR_LCD 0X01
#define RETURN_CUR_HOME 0X02
#define MODE_8BIT_1LINE 0X30
#define MODE_8BIT_2LINE 0X38
#define MODE_4BIT_1LINE 0X20
#define MODE_4BIT_2LINE 0X28
#define DISP_OFF 0X08
#define DISP_ON_CUR_OFF 0X0C
#define DISP_ON_CUR_ON 0X0E
#define DISP_ON_CUR_BLINK 0X0F
#define SHIFT_CUR_RIGHT 0X06 //entry mode
#define GOTO_LINE1_POS0 0X80
#define GOTO_LINE2_POS0 0XC0
#define GOTO_LINE3_POS0 0X90
#define GOTO_LINE4_POS0 0XD4
#define GOTO_CGRAM 0X40

