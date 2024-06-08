#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int map[19][19];

int flag;

void init();

int isWin(int x, int y);

int playerMove(int x, int y);

void menuView();

void gameView_ShowMap();

void winView();

void gameView();
// -------------------- view --------------------
int main()
{
	int testflag = 0;
	//init���Դ���
	
	init();
	if (flag != 0) {
	printf("init()����");
	exit(0);
	}
	for (int i = 0; i < 19; i++) {
	for (int j = 0; j < 19; j++) {
	if (map[i][j]) {
	printf("init()����");
	exit(0);
	}
	}
	}
	printf("init()���Գɹ�\n");
	testflag++;
	
	//playerMove���Դ���
	
	int result = 1;
	result &= playerMove(2, 2);
	result &= playerMove(2, 3);
	result &= playerMove(2, 4);
	result &= playerMove(2, 5);
	if (result != 1 || (map[2][2] && map[2][3] && map[2][4] && map[2][5]) != 1)
	{
	printf("playerMove()����");
	exit(0);
	}
	flag = 1;
	result &= playerMove(2, 5);
	if (result != 0 || map[2][5] != 1) {
	printf("playerMove()����");
	exit(0);
	}
	printf("playerMove()���Գɹ�\n");
	testflag++;
	
	//isWin���Դ���
	
	playerMove(2, 1);
	if (isWin(2, 1)) {
	printf("isWin()����");
	exit(0);
	}
	playerMove(1, 0);
	playerMove(3, 2);
	playerMove(4, 3);
	playerMove(5, 4);
	if (isWin(1, 0) != 2) {
	printf("isWin()����");
	exit(0);
	}
	printf("isWin()���Գɹ�\n");
	testflag++;
	
	if (testflag == 3) {
		printf("service������Գɹ�\n");
	}getchar();
	menuView();
	system("pause");
	return 0;
}
// -------------------- service --------------------
/*
�����̵�ֵ��ʼ��Ϊ0
��ǰ�غ���Ϊ����(flag��Ϊ0)
*/
void init(){
	memset(map, 0, sizeof(map));
	flag = 0;
}
/*
����: ���ݴ��������(map��Ӧλ��)��flagֵ �ж������Ƿ��ʤ
����ֵ:
0��ʾû�л�ʤ
1��ʾ����ʤ��
2��ʾ����ʤ��
*/
int isWin(int x, int y){
	/*int i, j,k,q,p;
	int lag;
	for (i = 0; i < 19; i++){
		for (j = 0; j < 19; j++){
			//�������ж�
			if (map[i][j] == 1){//�ϰ���(1)
				lag = 1;//�ҵ���һ����
				for (k = j + 1; k<j+5 && k<19; k++){//����4���ǲ��Ƕ���1;
					if (map[i][k] != 1){
						//lag = 1;//����ʡ�ˣ�Ҳ�����ٶำֵһ���˷���ÿ���ҵ����µĿ�ͷ����lag=1��
						
						break;//�����и����Ǿ���
					}
					else lag++;//�Ǿ�+1����ʵ��
				}if (lag == 5)return 1;//����ʤ
			}
			if (map[i][j] == 2){//�Ϻ���(2)
				lag = 1;
				for (k = j + 1; k<j + 5 && k<19; k++){//ͬ��
					if (map[i][k] != 2){
						//lag = 1;
						break;
					}
					else lag++;
				}if (lag == 5)return 2;//����ʤ
			}
			//�������ж�
			if (map[j][i] == 1 ){//�ϰ���
				lag = 1; 
				for (k = j + 1; k < j + 5 && k < 19; k++){
					if (map[k][i] != 1){
						break;
					}
					else lag++;
				}if (lag == 5)return 1;//����ʤ
			}
			if (map[j][i] == 2){//�Ϻ���
				lag = 1;
				for (k = j + 1; k < j + 5 && k < 19; k++){
					if (map[k][i] != 2){
						//lag = 1;
						break;
					}
					else lag++;
				}if (lag == 5)return 2;//����ʤ
			}
		}
	}
	//�ж���б
	for (i = 0; i < 19 - 5; i++){//������5�в�����,�ղ���5��λ�ӳ�һ��
		
		for (j = i,k=0; j < 19 && k<(19-i); j++,k++){//���Ի�ͼ������˶Խ���������19���,����б���ߵ��ľͳ������
			if (map[j][k] == 1){//��
				lag = 1;
				for (q = j + 1, p = k + 1; q < 19 && p < (19 - i); q++, p++){
					if (map[q][p] != 1)break;
					else lag++;
				}if (lag == 5)return 1;
			}

			if (map[j][k] == 2){//��
				lag = 1;
				for (q = j + 1, p = k + 1; q < 19 && p < (19 - i); q++, p++){
					if (map[q][p] != 2)break;
					else lag++;
				}if (lag == 5)return 2;
			}

			if (map[k][j] == 1){
			lag = 1;
				for (q = j + 1, p = k + 1; q < 19 && p < (19 - i); q++, p++){
					if (map[p][q] != 1)break;
					else lag++;
				}if (lag == 5)return 1;
			}

			if (map[k][j] == 2){
				lag = 1;
				for (q = j + 1, p = k + 1; q < 19 && p < (19 - i); q++, p++){
					if (map[p][q] != 2)break;
					else lag++;
				}if (lag == 5)return 2;
			}//�Խ��߶�����һ��  1.Ҫ�����ʼ�ͰѶԽ��߸���
		}
	}
	//�ж���б
	//for
	*/
	//int m = 0, n = 0;//m��ʾ���ӣ�n��ʾ���ӣ�1��Ӯ,0��ûӮ
	int count1 = 0;
	int count2 = 0;
	int i, j;
	//�������һ�����ӱ������ж�...666666666
	if (flag % 2 == 0) {
		for (j = 0; j < 19; j++) {
			if (map[x][j] == 1) {
				count1++;
			}
		}if (count1 == 5) {
			return 1;

		}
	}if (flag % 2 == 1) {
		for (j = 0; j < 19; j++) {
			if (map[x][j] == 2) {
				count2++;
			}
		}if (count2 == 5) {
			return 2;
		}
	}
	//�������һ�����ӱ������ж�
	count1 = 0; count2 = 0;//�ǵ�����
	if (flag % 2 == 0) {
		for (i = 0; i < 19; i++) {
			if (map[i][y] == 1) {
				count1++;
			}
		}if (count1 == 5) {
			return 1;

		}
	}if (flag % 2 == 1) {
		for (i = 0; i < 19; i++) {
			if (map[i][y] == 2) {
				count2++;
			}
		}if (count2 == 5) {
			return 2;
		}
	}
	//��б�ж�...
	/*if (x - 4 >= 0 && x + 4 < 19){
		count1 = 0; count2 = 0;
		for (i = x - 4,j = y-4; i < x + 4&&j<y+4; i++,j++){
			if (map[i][j] == 1){
				count1++;
			}
			else if (map[i][j] == 2){
				count2++;
			}
		}if (count1 == 5){
			return 1;
		}
		else if (count2 == 5){
			return 2;
		}
	}
	if (x - 4 < 0){
		count1 = 0; count2 = 0;
		for (i = 0, j = y - 4; i < x + 4 && j<y + 4; i++, j++){
			if (map[i][j] == 1){
				count1++;
			}
			else if (map[i][j] == 2){
				count2++;
			}
		}if (count1 == 5){
			return 1;
		}
		else if (count2 == 5){
			return 2;
		}
	}*/
	int yy = y, xx = x;
	while (yy >= 1 && xx >= 1){
		xx--; yy--;
	}count1 = 0; count2 = 0;

	for (i = xx, j = yy; i < 19 && j < 19; i++, j++){
		if (map[i][j] == 1)count1++; //count2 = 0;
		else break;//count2++; count1 = 0; 
	}if (count1 == 5)return 1;

	for (i = xx, j = yy; i < 19 && j < 19; i++, j++){
		if (map[i][j] == 2)count2++; 
		else break;
	}if (count2 == 5)return 2;

	//��б�ж�
	yy = y, xx = x;
	while (yy >= 1 && xx < 18){
		xx++; yy--;
	}count1 = 0; count2 = 0;
	for (i = xx, j = yy; i >0 && j < 19; i--, j++){
		if (map[i][j] == 1)count1++;
		else break;
	}if (count1 == 5)return 1;
	for (i = xx, j = yy; i >0 && j < 19; i--, j++){
		if (map[i][j] == 2)count2++;
		else break;
	}if (count2 == 5)return 2;
	return 0;//ûʤ�� 
}
/*��ָ��λ�����ӣ����map[x][y]�ǿյأ��͸�Ϊ��Ӧ��ɫ
xΪ��ǰ�غ����ӵ�x���꣬yΪ��ǰ�غ����ӵ�y����
����ֵ��0��ʾ����ʧ�ܣ��Ѿ����ӣ���1��ʾ���ӳɹ�*/
int playerMove(int x, int y){
	if (map[x][y] == 0 && flag % 2 == 0) {
		map[x][y] = 1; return 1;
	}
	else if (map[x][y] == 0 && flag % 2 == 1) {
		map[x][y] = 2; return 1;
	}
	else { return 0; }
}
/*
����: չʾѡ��, ��ҿ���������ѡ�������Ϸ, �������û��˳���Ϸ
������Ϸ: ������Ϸ���溯��gameView();
��������: �����ڴ�...
�˳���Ϸ: ����exit(0);
*/
void menuView(){
	
	int m;//����m==0���ǽ�����Ϸ��m==1�������ã�m==2�˳���Ϸ
	printf("����0������Ϸ\n����1��������\n����2�˳���Ϸ");
	scanf_s("%d", &m);//============================================================14:00��Ӵ˴�
	if (m == 0) {
		gameView();//=============================================================14:16��Ӵ˴�
		/*printf("���������꣨x��y��");
		scanf("%d %d", &x, &y);//=================================================14:11��Ӵ˴�
		playerMove(x, y);*/
	}
	else if (m == 1) {
		printf("���ù���δ����,�����ڴ�\n");//=======================================13:50��Ӵ˴�
	}
	else { printf("��Ϸ���˳�\n"); exit(0); };
}
/*
������: ����
����: ����map���� ��ӡ��Ϸ����
����: void
����ֵ: void
*/
void gameView_ShowMap(){
	int i, j;
	for (i = 0; i < 19; i++){
		for (j = 0; j < 19; j++){//=======�������
			printf("%d ", map[i][j]);
		}printf("\n");
	}if (flag % 2 == 0)printf("�������Ǻ�������\n");//===��ʾ������;
	else{ printf("�������ǰ�������\n"); }
}
/*
������: ����
����: ����flag��ֵ ��ӡ��Ϸʤ������ �û����԰�������ص����˵�
����: void
����ֵ: void
*/
void winView(){
	//int count;//=============================================================14:44�޸�
	if (flag % 2 != 0 ) {
		printf("��ϲ����Ӯ��\n");
	}
	else if (flag % 2 == 0) { printf("��ϲ����Ӯ��\n"); }
	printf("��������ص����˵�");
	getchar();//�������
	menuView();//�ص����˵�
	return;
}
/*
*�ѵ�2
������: ����
����: ��Ϸ��������
��ʼ����Ϸ����(���ú���init())
while(1){
��ӡ��Ϸ����(���ú���gameView_ShowMap())
���������������
����(�������Ӻ���playerMove())
(�������ʧ�� ���¿�ʼѭ��)
�ж���Ϸ�Ƿ�ʤ��(����ʤ���жϺ���isWin())
(�����Ϸʤ�� ����ʤ�����溯�� Ȼ�������ǰ����)
�л����(�޸�flagֵ)
}
����: void
����ֵ: void
*/
void gameView(){//============================================================14:21��ʼ��д
	int x, y;
	init();
	while (1){
		system("cls");
		gameView_ShowMap();
		printf("�������������꣨x��y��");
		scanf_s("%d %d", &x, &y);//���������������
		if (playerMove(x, y) == 0){
			printf("����ʧ��,����������\n"); system("pause"); continue;//(�������ʧ�� ���¿�ʼѭ��)
		}
		if (isWin(x, y) > 0){//�ж���Ϸ�Ƿ�ʤ��(����ʤ���жϺ���isWin())(�����Ϸʤ�� ����ʤ�����溯�� Ȼ�������ǰ����)
			winView();
		}
		else{
			++flag;//�л����(�޸�flagֵ)
		}
		
	}
}
