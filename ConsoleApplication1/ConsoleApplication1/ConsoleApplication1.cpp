// 编译环境：Visual C++ 6.0，EasyX 2018春分版
// http://www.easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <GUI.h>
#include <img.h>


int main()
{	
	POINT p0;
	initgraph(WIDTH, HEIGHT);			// 创建绘图窗口
	showimageALL(0,0,WIDTH,HEIGHT,gImage_1);
	//按任意键退出
	while (!kbhit())
	{
		
	}

	closegraph();					// 关闭绘图窗口
}