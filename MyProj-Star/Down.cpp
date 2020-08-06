// 编译环境：Visual C++ 6.0，EasyX 2018春分版
// http://www.easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define MAXSTAR 200	// 星星总数
#define WIDTH 200	//屏幕长
#define HEIGHT 200	// 星星总数
struct STAR
{
	double	x;
	double	y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];

// 初始化星星
void InitStar(int i)
{
	star[i].x = rand() % WIDTH;
	star[i].y = rand() % HEIGHT;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	// 速度越快，颜色越亮
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}

// 移动星星
void MoveStar(int i,int L)
{

	double k;
	k = star[i].y;
	if(k>L)
	k -= L;
	 
	//for (int i = 0; i < 6; i++)
	//{
	//	putpixel(int(star[i].x), int(k+i), 0);
	//	putpixel(int(star[i].x), int(k-i), 0);
	//}
	putpixel(star[i].x, k + 0, 0);
	putpixel(star[i].x, k - 0, 0);
	putpixel(star[i].x, k + 1, 0);
	putpixel(star[i].x, k - 1, 0);
	putpixel(star[i].x, k + 2, 0);
	putpixel(star[i].x, k - 2, 0);
	putpixel(star[i].x, k + 3, 0);
	putpixel(star[i].x, k - 3, 0);
	putpixel(star[i].x, k + 4, 0);
	putpixel(star[i].x, k - 4, 0);

	// 计算新位置

	star[i].y += star[i].step;
	if (star[i].y > HEIGHT+(double)L)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
	//putpixel((int)star[i].x+1, star[i].y, star[i].color);
	//putpixel((int)star[i].x, star[i].y+1, star[i].color);
	//putpixel((int)star[i].x+1, star[i].y+1, star[i].color);
}
void MoveStar2(int i)
{

	double k;
	k = star[i].y;

	// 擦掉原来的星星
	putpixel( star[i].x,(int)k, 0);
	
	// 计算新位置

	star[i].y += star[i].step;
	if (star[i].y > HEIGHT)	InitStar(i);

	// 画新星星
	putpixel((int)star[i].x, star[i].y, star[i].color);
	//putpixel((int)star[i].x+1, star[i].y, star[i].color);
	//putpixel((int)star[i].x, star[i].y+1, star[i].color);
	//putpixel((int)star[i].x+1, star[i].y+1, star[i].color);
}


// 主函数
int main()
{
	int j;
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(WIDTH, HEIGHT);			// 创建绘图窗口
	
	// 初始化所有星星
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
	}

	// 绘制星空，按任意键退出
	while (!kbhit())
	{
		for (j = 0; j < MAXSTAR; j+=4)
		{
			
			
				MoveStar(j,20);
				MoveStar(j+1, 40);
				MoveStar(j+2, 10);
				MoveStar2(j+3);
			//CloseStar(j);
		}
		Sleep(20);
	
	}

	closegraph();					// 关闭绘图窗口
}