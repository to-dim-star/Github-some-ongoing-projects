// ConsoleApplication1(test��Ϸ).cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<easyx.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int _tmain(int argc, _TCHAR* argv[])
{
	int x, y,i;
	initgraph(800, 600);//���崰�����ش�С
	setorigin(400, 300);//��ѡ����ϵԭ��
	setaspectratio(1.5, -1.5);//�ɱ�����������
	circle(0, 0, 250);//Բ����(���ĵ�x,y,�뾶r)
	for (i = 0; i < 1000; i++){
		//srand(time(NULL));
		x = rand() % (800 + 1) - 400;
		y = rand() % (600 + 1) - 300;
		putpixel(x, y, RED);
	}
	/*putpixel(0, 0, RED);
	putpixel(200, 200, YELLOW);
	putpixel(200, -200, BLUE);
	putpixel(200, -210, CYAN);
	putpixel(-200, 200, GREEN);
	putpixel(-200, -200, WHITE);*/
	getchar();
	closegraph();//�رմ���;
	return 0;
}

