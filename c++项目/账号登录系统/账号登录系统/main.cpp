#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<string>

using namespace std;

struct player_account{
	string number;//�˺�
	string account_key;//�˺�����
	string name;//�ǳ�
	size_t Player_uid;
	struct player_account* next=NULL;
};
typedef struct player_account* List;
List L=NULL, last=NULL, newNode=NULL;


int show_account(List a, int visited);
int show_allaccount();

void showMenu()
{
	printf("*** ��ӭ�����˺ŵ�¼ϵͳ***\n");
	cout << "---\t1.��¼�˺�\t---" << endl;
	//��������,��¼���޸�����,�޸��ǳ�****
	cout << "---\t2.ע���˺�\t---" << endl;
	//�ܱ�����**
	cout << "---\t3.��ʾ�����˺�\t---" << endl;
	//����Ա��̨*
	cout << "---\t0.�˳�ϵͳ\t---" << endl;
	printf("***************************\n");
}
void false_into(){
	printf("Plase check your into\nlet we again\n"); system("pause");
}
void showinit()
{
	system("cls");      
	cout << "---\t�˺�ע��\t---" << endl;
	    
	cout << "---\t-----------\t---" << endl;
}

int init_account()
{	again:
	system("cls");
	cout << "---\t�˺�ע��\t---" << endl;
	cout << "\t1.��ʼע��" << endl;
	//cout << "\t2.�����˺�����" << endl;
	//cout << "\t3.�����˺��ǳ�" << endl;
	cout << "\t[0].������ҳ��" << endl;
	cout << "---\t-----------\t---" << endl;
	char ch=getchar();
	switch (ch)
	{
	case '1':{
				 showinit();

				 newNode = new player_account;//����malloc����Ϊ�ṹ����string�࣬malloc/free�޷����㶯̬�����Ҫ��newNode = (player_account*)malloc(sizeof(struct player_account));
				 //==========================================================================================������Ϊ�����ڴ�����ͬʱ��Ҫ�Զ�ִ�й��캯��������������֮ǰҪ�Զ�ִ����������,���ʹ��malloc/free��Ҫ�ֶ������Щ;
				 //===ɾ���˺�ʱ�ǵ���delete;

				 if (newNode == NULL){ printf("newNodeδ��ȷ����"); return -1; }
				 string t;
				 cout << "ע���˺�/�ֻ��ţ�";//==��ʱû�в���
				 cin >> t; newNode->number = t;
				 printf("\n");
				 cout << "�����˺����룺";
				 cin >> t; newNode->account_key=t;
				 printf("\n");
				 cout << "�����˺��ǳƣ�";
				 cin >> t;newNode->name=t;

				 if (L == NULL){
					 L = last = newNode;
					 newNode->Player_uid = 100000000;
				 }
				 else{
					 newNode->Player_uid = last->Player_uid+1;
					 last->next = newNode;
					 last = newNode;
					 
				 }printf("ע��ɹ�!\n�������uid:%d\n��[0]ǰ����������,��1ֱ�ӷ��ص�¼����!", newNode->Player_uid);
				 int ttt;cin>>ttt;
				 if(ttt==1) return 2;//������2�ӵ���¼����;
				 else if (ttt == 0) show_account(newNode,1);
				 break;
	}
	 
	case '0':return 0;
	case '\n':goto again;
	default:{false_into(); cerr << "��Ч�����룬����������" << endl; goto again; }
	}
	return -1;//�⺯������-1.0.2,0����ҳ��,2ȥ��¼��-1����
}

int Are_you_sure(){
	printf("��ȷ����? Are you sure?\n1.Yes \t2.NO\n");
	int a;
	cin >> a;
	if (a == 1)return 1;
	else return 0;
}

void showregist(){
	system("cls");
	cout << "---\t�˺ŵ�¼\t---" << endl;

	cout << "---\t-----------\t---" << endl;
}

int show_account(List a,int visited){//visited�жϿ���������,1��,0����,Ĭ��0
	again:
	system("cls");
	cout << "---\t��������\t---" << endl;
	cout << "UID:" << a->Player_uid << endl;
	cout << "�ǳƣ�" << a->name <<'\n'<< endl;
	cout << "�˺ţ�" << a->number << endl;
	if (!visited){
		int t = a->account_key.size();
		cout << "�˺�����:";
		while (t--) printf("*"); printf("\n");
		cout << "�鿴�����밴1,��0������ҳ�沢�˳��˺�" << endl;
		cin >> t;
		if (t == 1)show_account(a, 1);
		if (t == 0)return 0;
	}
	else{ cout << "�˺����룺" << a->account_key << endl;
	cout << "��0������ҳ�棬���˳���������" << endl;
	char t; cin>>t; if (t == '0')return 0;
	else goto again;//ֻҪ��Ĳ���0��������ʾ;
	}
	return -1;//==return 0;����regist��0��main��ҳ��;
}

int show_allaccount(){
	List temp = L;
	system("cls");
	cout << "---\t����Ա�˺ź�̨\t---" << endl;
	while (temp != NULL){
		cout << "UID:" << temp->Player_uid << endl;
		cout << "�ǳƣ�" << temp->name <<endl;
		cout << "�˺ţ�" << temp->number << endl;
		cout << "�˺����룺" << temp->account_key << endl;
		printf("\n"); temp = temp->next;
	}system("pause"); return 0;
}

int regist(){
again:
	system("cls");
	cout << "---\t�˺ŵ�¼\t---" << endl;
	cout << "\t1.��ʼ��¼" << endl;
	//cout << "\t2.�����˺�����" << endl;
	//cout << "\t3.�����˺��ǳ�" << endl;
	cout << "\t[0].������ҳ��" << endl;
	cout << "---\t-----------\t---" << endl;
	char ch = getchar();
	switch (ch)
	{
	case '1':{
				 showregist();
				 string tnumber;
				 cout << "��¼�˺�/�ֻ��ţ�";//==��ʱû�в���
				 cin >> tnumber;
				 //printf("\n");
				 List temp = L; int a = 0;
				 while (temp != NULL){
					 if (temp->number != tnumber){ temp = temp->next; }//printf("temp->number != tnumber\n"); }
					 else break;//cao,��Ȼ������else�˳�
				 }if (temp == NULL){
					 FILE* fp = NULL;
					 errno_t err = fopen_s(&fp, "zhanghao.txt", "r+");  

					 if (fp == NULL) {
						 printf("error\n");
						 perror("open file failed:");
					 }char c1[100]; int flag = 0;//flag�ж��Ƿ��ҵ��˺� 

					 do{// char *fgets(char *str, int n, FILE *stream);
						 printf("1\n");
						 if (fgets(c1, sizeof(c1), fp) == NULL) break;//��������ж���NULL���ǵ��ļ�ĩβ�ˣ�������
						 c1[sizeof(c1)-1] = '\0';
						 if (strcmp(c1, tnumber.c_str()) == 0){
							 flag = 1; printf("ky\n"); break;
						 }

					 } while (fgets(c1, sizeof(c1), fp) != NULL);
					 cout << "���޴˺�,���������\n��1���ԣ���2ǰ��ע��,����(0)�򷵻���ҳ��" << endl;
					 int t; scanf_s("%d", &t);
					 if (t == 1){ goto again; }
					 else if (t == 2){ return 2; }
					 else return 0;
				 }
				 cout << "�����˺����룺";
				 cin >> tnumber;
				 if (tnumber != temp->account_key){
					 cout << "������������˺Ż������Ƿ�����\n������󷵻ص�¼ҳ��" << endl;
					 system("pause"); goto again;//==û�б����˺��������빦��
				 }
				 else{
					 if (show_account(temp, 0) == 0) return 0;//������ҳ�洫����;����
					 else  return -1;//��else��show_account��������
				 }
				 break;
	}

	case '0':return 0;
	case'\n':goto again;
	default:{false_into(); goto again; }
	}
	return -1;//����
}


int main()
{
	bool running=true;

	while (running){
		again:
		system("cls");
		showMenu();//չʾ�˵�
		int chose = 0;
		scanf_s("%d", &chose);
		switch (chose)
		{
		case 1:{getchar(); init_to_regist:
		int tt = regist();//����һ�µ�¼����2����0
		if (!tt)break;// goto again;//0������
		else if (tt == 2)goto regist_to_init;//2��ǰ��ע��;
		break;
		}
		case 2:{getchar(); regist_to_init:
		int tt = init_account();
		if (!tt)break;// goto again;
		else if (tt == 2)goto init_to_regist;
		break;
		}
		case 3:{show_allaccount(); //goto again;
			break;
		}
		case 0:{if (!Are_you_sure())break;//goto again;
			   else { cout << "\n�ټ���See you next time!" << endl; running = false; }
			   break;
		}
		default:{
					false_into(); goto again;
		}
		}
	}

	system("pause");
	return 0;
}
