#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

void beginViewer_01();
void xiaji();
int shangxian();
//long time1();
//char* time2();
double MoneyUsing(long int t_compare);
void Introduction();
void Record();

struct zhanghao {   //�����˺Žṹ�壨�û������룩,����������Ϊ�˺ţ�ż����Ϊ����
	char yonghu[30];
	char mima[30];
};

struct record {
	struct zhanghao zhanghao;
	char shangji[30];   //�ϻ�ʱ��
	char xiaji[30];    //�»�ʱ��
	double money;
};
struct record student;

void xiaji(time_t t_start) {
	int num = 0;
	double h = 0;
	printf("\n�������ӣ��������ϻ�\n");
	do {
		printf("��6�»������������棬������:");
		scanf("%d", &num);
		if (num == 6) {
			//long t1 = time1();
			//char t2[100] = time2();
			//t1 /= 3600;
			time_t t;
			time(&t);
			struct tm* tmp_time = localtime(&t);
			char s[100];
			strftime(s, sizeof(s), "%Y.%m.%d %H:%M:%S", tmp_time);
			long int t_compare = (long)(t - t_start);
			printf("\n---�»�ʱ��Ϊ:%s---\n---��ʹ��:%d��---\n", s, t_compare);
			//student.xiaji[0] = s;
			strcpy(student.xiaji, s);

			double money1 = MoneyUsing(t_compare);
			printf("�˴��ϻ�����Ϊ��%.2lfԪ��", money1);
			student.money = money1;
			//strcpy(student.money,money1);
			//system("pause");
			FILE* fp2 = fopen("record.txt", "a");
			if (fp2 == NULL) {
				perror("�ļ���ʧ�ܣ�");
				return;
			}
			/*fputs(student.zhanghao.yonghu, fp2);
			fputs(student.zhanghao.mima, fp2);
			fputs(student.shangji, fp2);
			fputs(student.xiaji, fp2);*/
			fprintf(fp2,"�˺�%s :", student.zhanghao.yonghu);
			fprintf(fp2,"�ϻ�ʱ�䣺%s ", student.shangji);
			fprintf(fp2, "�»�ʱ�䣺%s \n", student.xiaji);

			fclose(fp2);
			
			system("pause");
			beginViewer_01();
		}
		else {
			printf("��������ȷ����");
		}
	} while (num != 6);
}
int shangxian() {   //�����ϻ���¼�ĺ���
	//˼·������һ�飬����ѭ������һ��ѭ���������û����Ƿ��¼��
	//ϵͳ�ڣ�������Ҫ�������롣�ڶ���ѭ���������������û��

	char z1[20] = { 0 };   //z1Ϊ�û�������
	FILE* fp1 = fopen("zhanghao.txt", "r");
	char c1[20] = { 0 };
	int flag = 0, flag1 = 1;
	while (flag1) {
		printf("---�˺ŵ�¼---\n");
		printf("�������û���:\n");
		scanf("%s", z1);   //�����û���
		do {
			if (fgets(c1, sizeof(c1), fp1) == NULL) {
				break;
			}
			c1[strlen(c1) - 1] = '\0';
			if (strcmp(c1, z1) == 0) {
				flag = 1;
				//student.zhanghao.yonghu[20] = c1;
				strcpy(student.zhanghao.yonghu, c1);
				break;
			}
		} while (fgets(c1, sizeof(c1), fp1) != NULL);
		if (flag == 0) {
			rewind(fp1);
			printf("�û������ڣ�����������\n��1��������,��0����������\n");//׼���˳�ͨ��
			int a;
			scanf("%d", &a);
			if (a == 0) {
				return 0;
			}
		}
		else flag1 = 0;
	}
	char z2[20] = { 0 };   //z2Ϊ��������
	char c2[20] = { 0 };
	fgets(c2, sizeof(c2), fp1);
	c2[strlen(c2) - 1] = '\0';
	fclose(fp1);
	flag1 = 1;
	while (flag1) {
		system("cls");//����
		printf("---�˺ŵ�¼---\n");
		printf("�û�:%s\n", c1);
		printf("����������\n");
		scanf("%s", z2);
		if (strcmp(c2, z2) == 0) {
			flag1 = 0;
			//student.zhanghao.mima = c2;//����char�����ǲ���ֱ�Ӹ�ֵ��,string����
			strcpy(student.zhanghao.mima, c2);
			printf("---��¼�ɹ�,��ӭʹ��---\n");
			printf("��6��ʼ�ϻ�\n");
			int num;
			scanf("%d", &num);
			if (num == 6) {
				//long t1 = time1();
				//char t2[100] = time2();
				time_t t;
				time(&t);
				struct tm* tmp_time = localtime(&t);
				char s[100];
				strftime(s, sizeof(s), "%Y.%m.%d %H:%M:%S", tmp_time);
				printf("---�˴���%sʱ���ϻ�---", s);
				//student.shangji = s;
				strcpy(student.shangji, s);
				long int t_start = t;
				xiaji(t_start);
			}
			else {
				printf("�������������");//��0������ҳ��
				system("pause");
			}
		}
		
	}
}
//long time1(){   //���������ĺ���
//	time_t t;
//	time(&t);
//	struct tm* tmp_time = localtime(&t);
//	char s[100];
//	strftime(s, sizeof(s), "%Y.%m.%d %H:%M:%S", tmp_time);
//    printf("%ld: %s\n", t, s);
//	return t;
//}
//char* time2() {   //����ʱ����ĺ���
//	time_t t;
//	time(&t);
//	struct tm* tmp_time = localtime(&t);
//	char s[100];
//	strftime(s, sizeof(s), "%Y.%m.%d %H:%M:%S", tmp_time);
//	printf("%ld: %s\n", t, s);
//	return s;
//}
double MoneyUsing(long int t_compare){//���ڼ�����õĺ���
	double money;
	long int t_hour;
	if (t_compare > 0 && t_compare <= 3600) {
		return 1;
	}
	t_hour = t_compare / 3600;  //����һСʱ��һСʱ��
	if (t_hour % 3600 != 0) {
		t_hour++;
	};
	money = t_hour * 1;
	return money;
}
void Introduction() {   //���ܽ��ܺ���
	printf("��ȷ�����û���������󣬿��Խ����ϻ�\n");
	printf("���»�ʱ,�����뵱ǰʱ�䣬���ڷ��ü�¼\n");
	printf("����ΪÿСʱһԪ������һСʱ,��һСʱ��\n");
	system("pause");
	beginViewer_01();
	return;
}
void beginViewer_01() {   //�����溯��
	int flag = 1;
	while (flag) {
		system("cls");
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
		case 1:if (shangxian() != 0)flag = 0; break;
		case 2:Introduction(); break;
		case 3:Record(); break;
		case 4:exit(0); break;
		default:printf("��������ȷ����������\n");
			//system("pause");
		printf("��ô�ָ���С���ҵ�©����...��һ����ղŵĲ�������������߰�\n");
		}
		system("pause");
	}
}
void Record() {
	char c1;
	FILE* fp2 = fopen("record.txt", "r+");
	while ((c1 = fgetc(fp2)) != EOF) {
		printf("%c", c1);
	}fclose(fp2);
	return;
}
int main()
{
	//FILE* fp = fopen("�˻�.txt", "r");
	beginViewer_01();
	//fclose(fp);
	return 0;
}
