/*��Ŀ54�������ϻ�ģ��ϵͳ
��˵����Ҫ��
�����û�������˺ź����룬�ж��û��Ƿ�Ϸ�������ǺϷ��û����¼�û����˺š��ϻ�ʱ�䣬
���Ϊ�Ƿ��û�����ʾ�˺Ż�������������ԡ�
�û��ϻ������󣬼�¼�û����»�ʱ�䣬��������ã���ÿСʱʱ�����Ϊ1Ԫ����
����ʾ��
��1���������ļ��ֱ����û��˺ţ��û��˺š����룩���ϻ���¼���˺š��ϻ�ʱ�䡢�»�ʱ�䡢���ã���
��2�����������ṹ��ֱ��ʾ�û��˺ź��ϻ���¼��
��3����д�����ֱ�ʵ���ϻ����»����ܣ�*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct zhanghao {   //�����˺Žṹ�壨�û������룩,����������Ϊ�˺ţ�ż����Ϊ����
	char yonghu[20];
	char mima[20];
};
/*struct zhanghao student1 = { "jisuaunji2301", "jianzhudaxue0912" };
struct zhanghao student2 = { "jiusuanji2302", "jianzhudaxue0707" };
struct zhanghao student3 = { "dashuju2301", "jisuanji0424" };*/
struct record {
	int shangji_hour;
	int shangji_minute;   //�ϻ�ʱ�䣨ʱ,�֣�
	int xiaji_hour;
	int xiaji_minute;   //�»�ʱ��(ʱ,��)
	double money;
};
struct record student;

void shangxian() {   //�����ϻ���¼�ĺ���
	//˼·������һ�飬����ѭ������һ��ѭ���������û����Ƿ��¼��
	//ϵͳ�ڣ�������Ҫ�������롣�ڶ���ѭ���������������û��

	char z1[20] ;   //z1Ϊ�û�������
	//int shu;   //shuΪ�����»�������
	printf("�������û���:\n");
	scanf_s("%19s",z1);   //�����û���
	
	FILE* fp=fopen( "zhanghao.txt", "r+");
	
	if (fp == NULL) {
		printf("error\n");
		perror("open file failed:");
		return;
	}
	char c1[100]; int flag = 0;//flag�ж��Ƿ��ҵ��˺� 
	
	do{// char *fgets(char *str, int n, FILE *stream);
		printf("1\n");
		if (fgets(c1, sizeof(c1), fp) == NULL) break;//��������ж���NULL���ǵ��ļ�ĩβ�ˣ�������
		c1[sizeof(c1)-1] = '\0'; 
		if (strcmp(c1, z1)==0){
			flag = 1; printf("ky\n"); break;
		}

	} while (fgets(c1, sizeof(c1), fp) != NULL);//������һ�ε�����fgets�������ż����������
	/*char z2[20] = { 0 };   //z2Ϊ��������
	if (strcmp(c1, z1) == 0) {
		printf("����������");
		scanf("%s", &z2);
		char c2[20] = { 0 };
		while (c2[20] = fgets(c2[0], sizeof(c2[0]), fp) != EOF) {
			c2[20] = fgets(c2[0], sizeof(c2[0]), fp);       //��ô�������û�����ȷ������±Ƚ��Ǹ�������룿
		}
		if (strcmp(c2, z2) == 0) {
			printf("��¼�ɹ�,��ӭʹ��");
			printf("�������ϻ�ʱ��:");
			scanf("%d %d", &student.shangji_hour, &student.shangji_minute);
		}
		else {
			printf("�������������");
		}*/
		printf("����000�����»�����");
	}

	/*void xiaxian() {
	printf("�������»�ʱ��");
	scanf("%d %d", );
	}*/
	int MoneyUsing(int begin_hour, int end_hour, int begin_minute, int end_minute)
	{//���ڼ�����õĺ���
		double money;
		int time = end_hour - begin_hour;
		if ((end_minute - begin_minute) > 0)   //����һСʱ��һСʱ��
			time++;
		else if ((end_minute - begin_minute) < 0) {
			time--;
		}
		money = time * 1;
		return money;
	}
	void Introduction() {
		printf("��ȷ�����û���������󣬿��Խ����ϻ�\n");
		printf("���»�ʱ,�����뵱ǰʱ�䣬���ڷ��ü�¼\n");
		printf("����ΪÿСʱһԪ������һСʱ,��һСʱ��\n");
		return;
	}
	void beginViewer_01() {
		int num1 = 0;
		printf("**************************\n");
		printf("*   �����ϻ�ģ��ϵͳ     *\n");
		printf("*                        *\n");
		printf("*      1.�û���¼        *\n");
		printf("*      2.���ܽ���        *\n");
		printf("*      3.�ϻ���¼        *\n");
		printf("*      4.�˳�ϵͳ        *\n");
		printf("*                        *\n");
		printf("*     (!��лʹ�ã�)      *\n");
		printf("**************************\n");
		printf("�����룺");
		scanf_s("%d", &num1);
		switch (num1) {
			case 1:shangxian(); break;
			case 2:Introduction(); break;
			//case 3:��
			case 4:exit(0); break;
		}
	}
	void Viewer_02() {
		int num2 = 0;
		printf("**************************\n");
		printf("*                        *\n");
		printf("*        �����ϻ�        *\n");
		printf("*        �»�����        *\n");
		printf("*                        *\n");
		printf("**************************\n");

		return;
	}
	int main() {
		
		/*if(fp == NULL) {
		perror("open file failed:");
		return -1;
		}*/
		
		beginViewer_01();
		/*double money = MoneyUsing(student.shangji_hour,student.xiaji_hour, student.shangji_minute, student.xiaji_minute);
		printf("�˴��ϻ�����Ϊ��%lf", money);*/
		return 0;
	}
	