#include<stdio.h>
#include<easyx.h>

int a;
char board_data[3][3] = { { '-', '-', '-' }, { '-', '-', '-' }, { '-', '-', '-' } };
char current_piece = 'o';

//���ָ������Ƿ��ʤ
bool CheckWin(char c){
	int win=0,winl=0;
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			if(board_data[j][i]==c){//��ʤ��
				win++;
			}
			if (board_data[i][j] == c){//��ʤ��
				winl++;
			}
		}
		if(win==3 || winl==3){
			return true;
		}else{
			win = 0; winl = 0;
		}
	}win=0;int win1=0;
	for(int i=0;i<3;i++){//����бʤ��
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
	
	}return true;
}

//�����������
void DrawBoard(){
	line(0,200,600,200);
	line(0,400,600,400);
	line(200,0,200,600);
	line(400,0,400,600);
}

//��������
void DrawPiece(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			switch(board_data[i][j])
			{
				case'o':
					circle(200*j+100,200*i+100,100);
					break;
				case'x':
					line(200*j,200*i,200*(j+1),200*(i+1));
					line(200*(j+1),200*i,200*j,200*(i+1));
					break;
				case'-':
					break;
				default:
					break;
			}
		}
	}
}

//������ʾ��Ϣ
void DrawTipText(){
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰҪ��������Ϊ:%c"), current_piece);//����
	settextcolor(RGB(225, 175, 45));
	outtextxy(0, 0, str);
}


int _tmain(int argc, _TCHAR* argv[])
{
	again:
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			board_data[i][j] = '-';
		}
	}
	initgraph(600, 600);
	
	bool running = true;

	ExMessage msg;
	
	BeginBatchDraw();

	while (running){
		DWORD start_time = GetTickCount();
		while (peekmessage(&msg))
		{
			//���������������Ϣ
			if (msg.message == WM_LBUTTONDOWN){
				//������λ��
				int x = msg.x;
				int y = msg.y;

				int index_x = x / 200;
				int index_y = y / 200;
				//��������
				if (board_data[index_y][index_x] == '-'){
					board_data[index_y][index_x] = current_piece;
					//�л���������
					if (current_piece == 'o'){
						current_piece = 'x';
					}
					else current_piece = 'o';
				}
			}
		}

		cleardevice();

		DrawBoard();
		DrawPiece();
		DrawTipText();

		FlushBatchDraw();


		if (CheckWin('x'))
		{
			
			a = MessageBox(GetHWnd(), _T("x ��һ�ʤ Again ?"), _T("Game Over!"), MB_OKCANCEL | MB_SYSTEMMODAL);
			if (a == IDOK)
			{
				goto again;  // ��Ϸ���³�ʼ��
			}
			else if (a == IDCANCEL)
			{
				exit(0);
			}
		}
		else if (CheckWin('o'))
		{
			a = MessageBox(GetHWnd(), _T("o ��һ�ʤ Again ?"), _T("Game Over!"), MB_OKCANCEL | MB_SYSTEMMODAL);
			if (a == IDOK)
			{
				goto again;  // ��Ϸ���³�ʼ��
			}
			else if (a == IDCANCEL)
			{
				exit(0);
			}
		}
		else if (CheckDraw())
		{
			a = MessageBox(GetHWnd(), _T("ƽ��,6 Again ?"), _T("Game Over!"), MB_OKCANCEL | MB_SYSTEMMODAL);
			if (a == IDOK)
			{
				goto again;  // ��Ϸ���³�ʼ��
			}
			else if (a == IDCANCEL)
			{
				exit(0);
			}
		}

		DWORD end_time = GetTickCount();
		DWORD cha_time = end_time - start_time;

		if (cha_time < 1000 / 60){
			Sleep(1000 / 60 - cha_time);
		}

	}EndBatchDraw();

	return 0;
}

