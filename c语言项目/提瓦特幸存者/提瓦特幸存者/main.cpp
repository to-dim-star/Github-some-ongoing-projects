#include<graphics.h>

#include<iostream>
#include<string>
#include<vector>

int idx_current_anim = 0;//֡����

const int PLAYER_ANIM_NUM = 6;//֡����



const int WINDOW_WIDTH = 1280;   //���ڿ��
const int WINDOW_HEIGHT = 720; //���ڸ߶�

/*IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];ʵ�������ͼ������*/

class PNT{
public:
	int x, y;
	PNT(int xx, int yy){
		x = xx; y = yy;
	}
};

//���ӿ�
#pragma comment(lib,"winmm.lib")  //����windows�������ֿ�
#pragma comment(lib,"MSIMG32.LIB") 

//GDI+�ӿ�
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}//GDI+һֱ���⴦��͸��ͨ��


class Animation//  ������
{
public://  ���ض���
	Animation(LPCTSTR path, int num, int interval)//LPCTSTR:LP����ָ��,C�����ɸı�,T��������Ƿ���UNICODE����ֱ�defineΪchar��wchar_t,STR�����ַ�����
	{
		interval_ms = interval;//ÿ��ʵ�����֡������Զ���

		TCHAR path_file[256];//==��ͼƬ��ַ?
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);//�ݲ�֪������ĺ���,��ʽ�����

			IMAGE* frame = new IMAGE();//�����ڴ��ͼƬ
			loadimage(frame, path_file);//��exayx����ͼƬ��������loadimage(&IMAGE ͼƬָ��,c_str ͼƬ��ַ�ַ�);
			frame_list.push_back(frame);//ֻ��push_back�����Զ������ڴ�?�ԡ�  //��Ļ:��vector��ԭʼָ���Ѿ��Ǻ�Σ�յ������ˣ����������������ô��?
		}
	}
	~Animation()//delete ͼƬnew���ڴ�
	{
		for (size_t i = 0; i < frame_list.size(); i++){
			delete frame_list[i];
		}
	}
	//  �滭
	void Play(int x,int y,int delta)//��ʱ�����л滭
	{
		timer += delta;
		if (timer >= interval_ms){
			idx_frame = (idx_frame + 1) % frame_list.size();
			timer = 0;
		}

		putimage_alpha(x, y, frame_list[idx_frame]);
	}

private:
	int timer = 0;     //������ʱ��
	int idx_frame = 0; //����֡����
	int interval_ms = 0;//֡interval���
	std::vector<IMAGE*>frame_list;//������ȡ����?�ԡ�
};

class Bullet//  �ӵ���
{
public:
	PNT position = { 0, 0 };
public:
	Bullet() = default;
	~Bullet() = default;

	void Draw()const
	{
		setlinecolor(RGB(255, 155, 50));
		setfillcolor(BLUE);// RGB(200,75,10)
		fillcircle(position.x, position.y, RADIUS);
	}

private:
	const int RADIUS = 10;//�ӵ��뾶

};
 

class Player//  ������
{
public:
	Player() :player_pos(500,500)
	{// ���ض�����
		loadimage(&img_shadow, _T("img/shadow_player.png"));// ���������Ӱͼ
		anim_left = new Animation(_T("img/player_left_%d.png"), 6, 45);//������ҽ�ɫ���������ҵĶ���
		anim_right = new Animation(_T("img/player_right_%d.png"), 6, 45);
	}

	~Player()
	{
		delete anim_left;
		delete anim_right;
	}

	void ProcessEvent(const ExMessage& msg)//  ���������Ϣ
	{
		switch(msg.message)
		{
		case WM_KEYDOWN:
			switch (msg.vkcode)
			{
			case  0x57:
				is_move_up = true;
				//player_pos.y -= PLAYER_SPEED;
				break;

			case 0x53:
				is_move_down = true;
				//player_pos.y += PLAYER_SPEED;
				break;
			case 0x41:
				is_move_left = true;
				//player_pos.x -= PLAYER_SPEED;
				break;
			case 0x44:
				is_move_right = true;
				//player_pos.x += PLAYER_SPEED;
				break;
			}
			break;
		
		case WM_KEYUP:
			switch (msg.vkcode)
			{
			case 0x57:
				is_move_up = false;
				//player_pos.y += PLAYER_SPEED;
				break;

			case 0x53:
				is_move_down = false;
				//player_pos.y += PLAYER_SPEED;
				break;
			case 0x41:
				is_move_left = false;
				//player_pos.x -= PLAYER_SPEED;
				break;
			case 0x44:
				is_move_right = false;
				//player_pos.x += PLAYER_SPEED;
				break;
			}
			break;
		}
	}

	void Move()
	{
		int dir_x = is_move_right - is_move_left;
		int dir_y = is_move_down - is_move_up;
		double len_dir = sqrt(dir_x*dir_x + dir_y*dir_y);
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			player_pos.x += (int)(PLAYER_SPEED * normalized_x);
			player_pos.y += (int)(PLAYER_SPEED * normalized_y);
		}

		if (player_pos.x < 0) player_pos.x = 0;
		if (player_pos.y < 0) player_pos.y = 0;
		if (player_pos.x + PLAYER_WIDTH > WINDOW_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
		if (player_pos.y + PLAYER_HEIGHT > WINDOW_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
	}

	void Draw(int delta)
	{
		int pos_shadow_x = player_pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
		int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;      //8?
		putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

		static bool facing_left = false;
		int dir_x = is_move_right - is_move_left;// 
		if (dir_x < 0)
			facing_left = true;
		else if (dir_x>0)
			facing_left = false;

		if (facing_left)
			anim_left->Play(player_pos.x, player_pos.y, delta);
		else
			anim_right->Play(player_pos.x, player_pos.y, delta);
	}

	const PNT& GetPosition() const
	{
		return player_pos;
	}
	const int GetPLAYER_WIDTH() const
	{
		return PLAYER_WIDTH;
	}
	const int GetPLAYER_HEIGHT() const
	{
		return PLAYER_HEIGHT;
	}

private:
	const int PLAYER_SPEED = 3;//   ����ƶ��ٶ�
	const int PLAYER_WIDTH = 80;    //��ҿ��
	const int PLAYER_HEIGHT = 80;   //��Ҹ߶�
	const int SHADOW_WIDTH = 32;    //��Ӱ���

private:
	IMAGE img_shadow;//        �����Ӱͼ
	Animation* anim_left;//  ���Animation�౬�İ�
	Animation* anim_right;
	PNT player_pos;//  ��ҳ�ʼ��
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

};

class Enemy//  ������
{
public:
	Enemy()
	{
		loadimage(&img_shadow, _T("img/shadow_enemy.png"));
		anim_left = new Animation(_T("img/enemy_left_%d.png"), 6, 45);
		anim_right = new Animation(_T("img/enemy_right_%d.png"), 6, 45);

		// �������ɱ߽�
		enum class SpawnEdge //ö���� what? 
		{
			Up = 0,
			Down,
			Left,
			Right
		};

		// �����������ڵ�ͼ������λ��
		SpawnEdge edge = (SpawnEdge)(rand() % 4);//0-3
		switch (edge)
		{
		case SpawnEdge::Up:
			position.x = rand() % WINDOW_WIDTH;
			position.y = -FRAME_HEIGHT;
			break;
		case SpawnEdge::Down:
			position.x = rand() % WINDOW_WIDTH;
			position.y = WINDOW_HEIGHT;
			break;
		case SpawnEdge::Left:
			position.x = -FRAME_WIDTH;
			position.y = rand() % WINDOW_HEIGHT;
			break;
		case SpawnEdge::Right:
			position.x = WINDOW_WIDTH;
			position.y = rand() % WINDOW_HEIGHT;
			break;
		default:
			break;
		}
	}

	bool CheckBulletCollision(const Bullet& bullet)
	{
		//���ӵ���ЧΪ�㣬�жϵ��Ƿ��ڵ��˾�����ײ����
		bool is_overlap_x = bullet.position.x >= position.x&&bullet.position.x <= position.x + FRAME_WIDTH;
		bool is_overlap_y = bullet.position.y >= position.y&&bullet.position.y <= position.y + FRAME_HEIGHT;
		return is_overlap_x && is_overlap_y;
	}

	bool CheckPlayerCollision(const Player& player)
	{
		PNT check_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
		PNT player_collect_leftup = { (player.GetPLAYER_WIDTH() / 5) * 2, (player.GetPLAYER_HEIGHT() / 5) * 2 };// player��ײ�ж������ϵ�
		PNT player_collect_rightdown = { (player.GetPLAYER_WIDTH() / 5) * 4, (player.GetPLAYER_HEIGHT() / 5) * 4 };// player��ײ�ж������µ�
		PNT player_position=player.GetPosition();// ��һ�������λ��
		if (check_position.x >= (player_position.x + player_collect_leftup.x) && check_position.x <= (player_position.x + player_collect_rightdown.x)){
			if (check_position.y >= (player_position.y + player_collect_leftup.y) && check_position.y <= (player_position.y + player_collect_rightdown.y)){
				return true;
			}
		}
		return false;
	}

	

	

	void Move(const Player& player)
	{
		const PNT& player_position = player.GetPosition();
		int dir_x = player_position.x - position.x;//  
		int dir_y = player_position.y - position.y;
		double len_dir = sqrt(dir_x*dir_x + dir_y*dir_y);//  ����
		if (len_dir != 0)
		{
			double normalized_x = dir_x / len_dir;
			double normalized_y = dir_y / len_dir;
			position.x += (int)(SPEED * normalized_x);
			position.y += (int)(SPEED * normalized_y);
		}

		if (dir_x < 0)facing_left = true;
		else if (dir_x>0)facing_left = false;

	}

	void Draw(int delta)
	{
		int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
		int pos_shadow_y = position.y + FRAME_HEIGHT - 35;      //�������35��?
		putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

		
		if (facing_left)
			anim_left->Play(position.x, position.y, delta);
		else
			anim_right->Play(position.x, position.y, delta);
	}


	~Enemy()
	{
		delete anim_left;
		delete anim_right;
	}

	//�������Ǹ���ӵ�ײ��Ұ����ʧ����
	void Hurt(){
		alive = false;
	}

	bool CheckAlive(){
		return alive;
	}

	bool ASpeed()   //���˼���
	{
		if (SPEED +1<9){
			SPEED++;
			return true;
		}return false;
	}
	bool CSpeed()
	{
		if (SPEED - 1 > 0){
			SPEED--;
			return true;
		}return false;
	}

private:
	int SPEED = 2;//   �����ƶ��ٶ�
	const int FRAME_WIDTH = 80;    //���˿��
	const int FRAME_HEIGHT = 80;   //���˸߶�
	const int SHADOW_WIDTH = 48;    //��Ӱ���

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	PNT position = { 0, 0 };
	bool facing_left = false;
	bool alive = true;
};



/*void DrawPlayer(int delta, int dir_x) //  ��Ǩ����Player����Draw����
{
	int pos_shadow_x = player_pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;      //8?
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	static bool facing_left = false;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x>0)
		facing_left = false;

	if (facing_left)
		anim_left_player.Play(player_pos.x, player_pos.y, delta);
	else
		anim_right_player.Play(player_pos.x, player_pos.y, delta);
}*/ 
/*void LoadAnimation(){
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_left_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_left[i], path.c_str());

	}
	for (size_t i = 0; i < PLAYER_ANIM_NUM; i++)
	{
		std::wstring path = L"img/player_right_" + std::to_wstring(i) + L".png";
		loadimage(&img_player_right[i], path.c_str());

	}
}*/

//  �����µĵ���
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter)%INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

// �����ӵ�λ��
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;                         //���򲨶��ٶ�
	const double TANGENT_SPEED = 0.0055;                        //���򲨶��ٶ�
	double radian_interval = 2 * 3.14159 / bullet_list.size();  //�ӵ��仡��_���
	PNT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount()*RADIAL_SPEED);   // ͨ��sin��̬�����뾶
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount()*TANGENT_SPEED + radian_interval * i;  //��ǰ�ӵ����ڻ���ֵ   ֵ����ʱ��GetTickCount()��󣬸��ӵ������radian_interval*i�ṩ
		bullet_list[i].position.x = player_position.x + player.GetPLAYER_WIDTH() / 2 + (int)(radius*cos(radian));
		bullet_list[i].position.y = player_position.y + player.GetPLAYER_HEIGHT() / 2 + (int)(radius*sin(radian));//  ���������Ǻ����ĵ���������˼����
	}
}

void DrawPlayerScore(int score){
	static TCHAR text[64];
	_stprintf_s(text, _T("��ǰ��ҵ÷֣�%d", score), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}


int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//���촰��


	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL); //����bgm
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL); //���ز�����hit
	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);    
	//                        һֱ��  ��bgm��0��ʼ��

	bool running = true;//����״̬

	int score = 0; //�÷�

	//��ʾ��Ϣ�ñ���
	bool isMessageVisible = false;
	const int messageDisplayTime = 100; // ������Ϣ��ʾ100֡  
	int currentDisplayFrame = 0;

	Player player;
	ExMessage msg;//�����¼��ṹ
	IMAGE img_background;//����ͼƬ������
	std::vector<Enemy*>enemy_list;//  ����Enemy����ָ��
	std::vector<Bullet>bullet_list(3);
	//IMAGE img_player;


	loadimage(&img_background, _T("img/background.png"));//���ر���ͼƬ
	//LoadAnimation();
	
	//loadimage(&img_player,_T("img/player_left_1.png"));
	BeginBatchDraw();//========================================================================================��ʼ��������
	/*int a = 0;
	char tt[] = "012345";����ѭ��Ƶ�ʵ�*/

	while (running)
	{
		DWORD start_time = GetTickCount();//===========================================================================�������п�ʼ��ʱ,��õδ�������

		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}

		player.Move();
		UpdateBullets(bullet_list, player);
		TryGenerateEnemy(enemy_list);//  ��ӵ���
		for (Enemy*enemy : enemy_list)
			enemy->Move(player);

		// �����������λ����ײ
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player))
			{
				static TCHAR text[128];
				_stprintf_s(text, _T("���յ÷֣�%d !"), score);
				MessageBox(GetHWnd(), text, _T("��Ϸ����"), MB_OK);
				running = false;
				break;
			}
		}

		// ����ӵ��͵��˵���ײ
		for (Enemy* enemy : enemy_list)
		{
			for (const Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL); //��hit��0��ʼ�ţ�����repeat
					enemy->Hurt();
					score++;
					
				}
				
			}
		}

		//�Ƴ�����ֵ����ĵ���
		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			Enemy*enemy = enemy_list[i];
			if (!enemy->CheckAlive())
			{
				std::swap(enemy_list[i], enemy_list.back()); // swap��0enemy��ĩβ����pop_back();
				enemy_list.pop_back();
				delete enemy;
			}
			if (score % 10 == 0){
				if (score != 0)isMessageVisible = true; //ok��ʾ
				enemy_list[i]->ASpeed();
				
			}
		}

		
		/*while (peekmessage(&msg))//��Ϣ����
		{
			
		}*/

		/*if (is_move_up)player_pos.y -= PLAYER_SPEED;
		if (is_move_down)player_pos.y += PLAYER_SPEED;
		if (is_move_left)player_pos.x -= PLAYER_SPEED;
		if (is_move_right)player_pos.x += PLAYER_SPEED;*///����б����ٸ���2�����

		

		/*static int i = 0;//==�����ɵ�ѭ�����ű���
		if(++i % 5 == 0)a++;*/

		/*static int counter = 0;//�Ǽ���ѭ����һ��ͼƬ;
		if (++counter % 5 == 0){ idx_current_anim++;}
		//ʹ����ѭ������
		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;*/ //��DrawPlayer
		//a = a % 6;�����ɵ�֡a

		cleardevice();//============================================================�ñ���ɫ��ջ�ͼװ��,ˢ�»�ͼ������?

		putimage(0, 0,&img_background);
		player.Draw(1000 / 60);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000 / 60);//����ˢ��֮ǰд��100/60���Ե��˶���һ��һ����
		for (const Bullet& bullet : bullet_list)
			bullet.Draw();
		DrawPlayerScore(score);

		if (isMessageVisible) {
			// ��ʾ��Ϣ  
			static TCHAR tip[64];
			_stprintf_s(tip, _T("����������%d��������Ҫ���ٿ�"), score);
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			//settextstyle(16, 0, tip);
			outtextxy(WINDOW_WIDTH/2-100, WINDOW_HEIGHT/2, tip);

			// ���ӵ�ǰ��ʾ֡��  
			currentDisplayFrame++;

			// ����Ѿ���ʾ���㹻��ʱ�䣬��������Ϣ  
			if (currentDisplayFrame >= messageDisplayTime) {
				//Sleep(1000);
				isMessageVisible = false;
				currentDisplayFrame = 0; // ������ʾ֡��  
			}
		}

		//�ѷ�����װ��Player���У�DrawPlayer(1000 / 60, is_move_right - is_move_left);//     ������ж�����

		//putimage_alpha(player_pos.x,player_pos.y, &img_player_left[idx_current_anim]);//��ӡ֡������Ӧ��ͼƬ
		
		//outtextxy(0, 0, tt[a]);����ѭ��Ƶ�ʵ����
		FlushBatchDraw();//====================================================================================��ϴ��������,ִ��δ��ɵĻ�ͼ����

		DWORD end_time = GetTickCount();//=============================================================================�ý�����ʱ;
		DWORD delay_time = end_time - start_time;
		if (delay_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delay_time);
		}
	}

	EndBatchDraw();//==========================================================================================�ر�������ͼ

	return 0;
}