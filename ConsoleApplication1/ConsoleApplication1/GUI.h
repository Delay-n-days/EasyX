#include <graphics.h>

#define WIDTH 123	// 宽
#define HEIGHT 175	// 高

#define uRED 0x0015
#define uGREEN 0x07e0
#define uBLUE 0xA800
#define uWHITE 0xffff
#define uBLACK 0x0000
#define uYELLOW 0x57ff
#define uGRAY0 0xEF7D //灰色0 3165 00110 001011 00101
#define uGRAY1 0x8410 //灰色1      00000 000000 00000
#define uGRAY2 0x4208 //灰色2  1111111111011111
typedef unsigned int        uint;
void GUI_DrawPoint(int x, int y,uint color);
void showimageALL(int x0,int y0, int W,int H,const unsigned char *p);
void Lcd_clear(uint color);
