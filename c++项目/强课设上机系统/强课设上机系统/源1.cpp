#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  

struct zhanghao {
	char yonghu[20];
	char mima[20];
};

struct record {
	int shangji_hour;
	int shangji_minute;
	int xiaji_hour;
	int xiaji_minute;
	double money;
};

void shangxian() {
	char z1[20] = { 0 };
	char z2[20] = { 0 }; // ���ڴ洢����  
	FILE* fp_account = NULL;
	
	errno_t err = fopen_s(&fp_account, "zhanghao.txt", "r+");
	

	if (fp_account == NULL ) {
		printf("Error opening file.\n");
		system("pause");
		return;
	}

	struct zhanghao account;
	

	while (fscanf_s(fp_account, "%19s", account.yonghu) != EOF) {
		fscanf_s(fp_account, "%19s",account.mima);

		printf("�������û���: ");
		scanf_s("%19s", z1, sizeof(z1));
		printf("����������: ");
		scanf_s("%19s", z2, sizeof(z2));

		if (strcmp(account.yonghu, z1) == 0 && strcmp(account.mima, z2) == 0) {
			printf("��¼�ɹ���\n");
			// ��¼�ϻ�ʱ�䣬��ת�����˵�����������  
			break;
		}
		else{ printf("�˺Ż��������������!\n"); }
	}

	fclose(fp_account);
	
}

void xiaji() {
	// ʵ���»����ܣ���¼�»�ʱ�䲢�������  
}

void Introduction() {
	// ʵ�ֹ��ܽ���  
}

void checkRecord() {
	// ʵ�ֲ鿴�ϻ���¼����  
}
void beginViewer_01() {

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

}

int main() {
	int choice;

	do {
		beginViewer_01();
		scanf_s("%d", &choice);
		switch (choice) {
		case 1:
			shangxian();
			break;
		case 2:
			Introduction();
			break;
		case 3:
			checkRecord();
			break;
		case 4:
			printf("�˳�ϵͳ��\n");
			break;
		default:
			printf("��Чѡ�����������롣\n");
		}
	} while (choice != 4);

	return 0;
}

