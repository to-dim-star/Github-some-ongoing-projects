#include<iostream>

using namespace std;//  �������أ������ú�������ͬ����߸�����
//����:1.ͬһ������   2.��������ͬ
//     3.�������Ͳ�ͬ���������ͬ����˳��ͬ 
//     ps:�������Ͳ�ͬ������Ϊ�������� 

void func() {
	cout << "func" << endl;
}
/*
void func(int a){//         ������ͬ 
	cout << "int a->func" << endl;
}
*/
void func(int b, double c) {//       ��Ҫ���صĺ�����ò�Ҫ��Ĭ�ϲ�������Ϊ��һ����ռ�����������,���� double c=10){ ������һ��������ͻ�ж����� 
	cout << "int b,int c->func" << endl;
}
//
void func(double b, int c){ cout << "ɶ?" << endl; }//  ˳��ͬ 

void func(double a){//       ���Ͳ�ͬ 
	cout << "double a��" << endl;
}


//      �������ص�ע������: 1.����Ҳ�ܵ����Ͳ�ͬ?   ò��dev��int a��int &aһ������ 

void func(int &a) {
	cout << ++a << endl;
}
void func(const int &a){
	cout << "const int " << a << endl;//    const int &a ��int &a���ܱ� int a ���;����int &a �� const int &a ���ǲ�һ����
}

int main(){
	int a = 8;
	func(a);
	func(8);
	printf("main�е�a��%d", a);
	system("pause");
	return 0;
}