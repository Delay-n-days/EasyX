#include <GUI.h>


void GUI_DrawPoint(int x, int y,uint color)
{
    int r,g,b;
    DWORD COLOR;
    r=(color&63488)>>8;
    g=(color&2016)>>3;
    b=(color&31)<<3;
    COLOR=RGB(b,g,r);//bgr 记住了，他妈的EasyX的颜色是bgr 罗马车的马屁股
	putpixel(x, y, COLOR);
}
void showimageALL(int x0,int y0, int W,int H,const unsigned char *p) //显示完整图片
{
	int i,x,y;
	unsigned char picH, picL;
	uint fc;
	for (i = 0; i < W * H; i++)
	{
        y=i/W;
        x=i-y*W;
		picL = *(p + i * 2); //数据低位在前
		picH = *(p + i * 2 + 1);
        fc=picH*256+picH;
		GUI_DrawPoint(x+x0,y+y0,fc);
	}
}
void Lcd_clear(uint color)
{
    int x,y;
for (int i = 0; i<WIDTH*HEIGHT;i++)
	{
        y=i/WIDTH;
        x=i-y*WIDTH;
		GUI_DrawPoint(x,y,color);
	}
}