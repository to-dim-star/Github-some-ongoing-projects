// Project(...������...).cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<easyx.h>

char board_data[3][3] = { '-' };
char current_piece = 'o';

//���ָ������Ƿ��ʤ
bool CheckWin(char c){
	int win=0;
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			if(board_data[j][i]==c){
				win++;
			}
		}
		if(win==3){
			return true;
		}else{
			win=0;
		}
	}win=0;int win1=0;
	for(i=0;i<3;i++){
		if(board_data[i][i]==c){
			win++;
		}if(board_data[i][2-i]==c){
			win1++;
		}
	}if(win==3 || win1==3){
		return true;
	}
	return false;
}

//����Ƿ����ƽ��
bool CheckDraw(){
	int flag=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board_data[i][j]=='-'){
				return false;
			}
		}
	}
	}return false;
}

//�����������
void DrawBoard(){
	line(0,200,600,200);
	line(0,400,600,400);
	line(0200,0,200,600);
	line(400,0,400,600);
}

//��������
void DrawPiece(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			switch(board_data[i][j])
			{
				case"o":
					circle(200*j+100,200*i+100,100);
					break;
				case"x":
					line(200*j,200*i,200*(j+1),200*(i+1));
					line(200*(j+1),200*i,200*j,200*(i+1));
					break;
				case"-":
					break;
				default:
					break;
			}
		}
	}
}

//������ʾ��Ϣ
void DrawTipText(){

}


int _tmain(int argc, _TCHAR* argv[])
{

	initgraph(1980, 720);

	bool running = true;

	BeginBatchDraw();

	ExMessage msg;

	while (running){
		while (peekmessage(&msg))
		{
			//���������������Ϣ
			if (msg.message == WM_LBUTTONDOWN){
				//������λ��

			}
		}
		if (CheckWin('x'))
		{
			MessageBox(GetHWnd(), _T("x ��һ�ʤ"), _T("Game Over"), MB_OK);
			running = false;
		}
		else if (CheckWin('o'))
		{
			MessageBox(GetHWnd(), _T("o ��һ�ʤ"), _T("Game Over"), MB_OK);
			running = false;
		}
		else if (CheckDraw())
		{
			MessageBox(GetHWnd(), _T("ƽ��,6"), _T("Game Over"), MB_OK);
			running = false;
		}

		cleardevice();

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();

	}EndBatchDraw();

	return 0;
}

