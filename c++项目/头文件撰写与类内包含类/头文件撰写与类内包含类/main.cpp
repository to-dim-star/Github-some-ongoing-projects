#include<iostream>
using namespace std;
#include"circle+point.h"
#include<time.h>


int main(){
	clock_t start_time = clock();

	point cen;cen .setXY(0, 0);
	circle oo; oo.setR(1); oo.setcenter(cen);
	point op;op .setXY(1, 1);
	double R = oo.getR();
	double D = (op.getX() - oo.getcenter().getX())*(op.getX() - oo.getcenter().getX()) + (op.getY() - oo.getcenter().getY())*(op.getY() - oo.getcenter().getY());
	if (R*R>D)//����֮����빫ʽ:sqrt((x1-x2)^2+(y1-y2)^2);
	{
		printf("op��Բoo��\n");
	}
	else if (R*R == D)printf("��Сop��Բoo��\n");
	else printf("�üһ�,Сop��Բoo��\n");
	clock_t end_time = clock();
	printf("������%.10fms", (end_time - start_time)*1.0); /// CLOCKS_PER_SEC);
	system("pause");
	return 0;
}