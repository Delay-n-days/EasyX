#include <GUI.h>


void GUI_DrawPoint(int x, int y,uint color)
{
    int r,g,b;
    DWORD COLOR;
    r=(color&63488)>>8;
    g=(color&2016)>>3;
    b=(color&31)<<3;
    COLOR=RGB(b,g,r);//bgr ��ס�ˣ������EasyX����ɫ��bgr ��������ƨ��
	putpixel(x, y, COLOR);
}
void showimageALL(int x0,int y0, int W,int H,const unsigned char *p) //��ʾ����ͼƬ
{
	int i,x,y;
	unsigned char picH, picL;
	uint fc;
	for (i = 0; i < W * H; i++)
	{
        y=i/W;
        x=i-y*W;
		picL = *(p + i * 2); //���ݵ�λ��ǰ
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