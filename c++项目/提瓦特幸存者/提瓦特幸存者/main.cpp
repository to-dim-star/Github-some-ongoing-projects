#include<graphics.h>

#include<iostream>
#include<string>
#include<vector>

int idx_current_anim = 0;//帧索引

const int PLAYER_ANIM_NUM = 6;//帧总数

const int WINDOW_WIDTH = 1280;	//窗口宽度
const int WINDOW_HEIGHT = 720;	//窗口高度

const int BUTTON_WIDTH = 192;	//按钮宽
const int BUTTON_HEIGHT = 75;	//按钮高

bool running = true;//运行状态
bool is_game_started = false;	//判断游戏开始

/*IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];实验的左右图画数组*/

class PNT{
public:
	int x, y;
	PNT(int xx, int yy){
		x = xx; y = yy;
	}
};


//链接库
#pragma comment(lib,"winmm.lib")  //连接windows播放音乐库
#pragma comment(lib,"MSIMG32.LIB") 




//GDI+接口
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}//GDI+一直到这处理透明通道

class Button	//按钮类
{
public:
	Button(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered,LPCTSTR path_img_pushed)
	{
		region = rect; //继承大小信息

		loadimage(&img_idle, path_img_idle);
		loadimage(&img_hovered, path_img_hovered);
		loadimage(&img_pushed, path_img_pushed);
	}

	~Button() = default;
	
	void ProcessEvent(const ExMessage& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
				status = Status::Hovered;
			else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
				status = Status::Idle;
			break;
		case WM_LBUTTONDOWN:
			if (CheckCursorHit(msg.x, msg.y))
				status = Status::Pushed;
			break;
		case WM_LBUTTONUP:
			if (status == Status::Pushed)
				OnClick();
			break;
		default:
			break;
		}
	}

	void Draw() //对应状态绘制不同图
	{
		switch (status)
		{
		case Status::Idle:
			putimage(region.left, region.top, &img_idle);
			break;
		case Status::Hovered:
			putimage(region.left, region.top, &img_hovered);
			break;
		case Status::Pushed:
			putimage(region.left, region.top, &img_pushed);
			break;
		}
	}

protected:
	virtual void OnClick() = 0;	//纯虚函数??，后续继承Button类的函数必须实现自己的OnClick函数才能实例化

private:
	enum class Status //枚举状态
	{
		Idle = 0,	//空
		Hovered,	//悬
		Pushed		//点
	};

private:
	RECT region; //矩形大小数据
	IMAGE img_idle; //三个状态的图片资源
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status = Status::Idle;

private:
	bool CheckCursorHit(int x, int y)
	{
		return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
	}

};


//游戏开始按钮
class StartGameButton : public Button
{
public:
	StartGameButton(RECT rect,LPCTSTR path_img_idle,LPCTSTR path_img_hovered,LPCTSTR path_img_pushed)
		:Button(rect,path_img_idle,path_img_hovered,path_img_pushed){}
	~StartGameButton() = default;

protected:
	void OnClick()
	{
		is_game_started = true;
		mciSendString(_T("play BattleBgm repeat from 0"), NULL, 0, NULL);	//放战斗bgm;
	}
};

//退出游戏按钮
class QuitGameButton :public Button
{
public:
	QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		:Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {}
	~QuitGameButton() = default;

protected:
	void OnClick()
	{
		running = false;	// 即直接退出游戏
	}
};

class Atlas //专门加载享元模式的图片资源
{
public:
	Atlas(LPCTSTR path, int num)//LPCTSTR:LP代表指针,C代表不可改变,T代表根据是否定义UNICODE宏而分别define为char或wchar_t,STR代表字符串。
	{
		//interval_ms = interval;//每个实例类的帧间隔都自定义，现在帧数在Animation动，这里独立加载图片

		TCHAR path_file[256];//==存图片地址?√存图片中文
		for (size_t i = 0; i < num; i++)
		{
			_stprintf_s(path_file, path, i);//暂不知道干嘛的函数,格式化输出

			IMAGE* frame = new IMAGE();//申请内存放图片
			loadimage(frame, path_file);//用exayx加载图片函数加载loadimage(&IMAGE 图片指针,c_str 图片地址字符);
			frame_list.push_back(frame);//只有push_back就能自动增长内存?对√  //弹幕:用vector放原始指针已经是很危险的事情了，如果拷贝了数组怎么办?
		}
	}
	~Atlas()//delete 图片new的内存
	{
		for (size_t i = 0; i < frame_list.size(); i++) {
			delete frame_list[i];
		}
	}
public:
	std::vector<IMAGE*>frame_list;//这是在取名字?对√
};

Atlas* atlas_player_left; //四种图集
Atlas* atlas_player_right;
Atlas* atlas_enemy_left;
Atlas* atlas_enemy_right;

class Animation //动画类绘画图片资源
{
public: //加载动画

	Animation(Atlas* atles, int interval)
	{
		anim_atlas = atles;//图集
		interval_ms = interval;//帧数
	}

	~Animation() = default;

	//  绘画
	void Play(int x,int y,int delta)//计时器进行绘画
	{
		timer += delta;
		if (timer >= interval_ms){
			idx_frame = (idx_frame + 1) % anim_atlas->frame_list.size(); //用%拿第几帧
			timer = 0;
		}

		putimage_alpha(x, y, anim_atlas->frame_list[idx_frame]); //自定的利用系统的渲染绘图函数
	}

private:
	int timer = 0;     //动画计时器
	int idx_frame = 0; //动画帧索引
	int interval_ms = 0;//帧interval间隔
	
private:
	Atlas* anim_atlas;//只用指针负责动画加载
};

class Bullet//  子弹类
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
	const int RADIUS = 10;//子弹半径

};
 

class Player//  主角类
{
public:
	Player() :player_pos(500,500)
	{// 加载动画组
		loadimage(&img_shadow, _T("img/shadow_player.png"));// 加载玩家阴影图
		anim_left = new Animation(atlas_player_left, 45);//加载玩家角色的向左向右的动画
		anim_right = new Animation(atlas_player_right, 45);
	}

	~Player()
	{
		delete anim_left;
		delete anim_right;
	}

	void ProcessEvent(const ExMessage& msg)//  处理操作信息
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
	const int PLAYER_SPEED = 3;//   玩家移动速度
	const int PLAYER_WIDTH = 80;    //玩家宽度
	const int PLAYER_HEIGHT = 80;   //玩家高度
	const int SHADOW_WIDTH = 32;    //阴影宽度

private:
	IMAGE img_shadow;//        玩家阴影图
	Animation* anim_left;//  会对Animation类爆改吧，确实改了点
	Animation* anim_right;
	PNT player_pos;//  玩家初始点
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

};

class Enemy//  敌人类
{
public:
	Enemy()
	{
		loadimage(&img_shadow, _T("img/shadow_enemy.png"));
		anim_left = new Animation(atlas_enemy_left, 45);
		anim_right = new Animation(atlas_enemy_right, 45);

		// 敌人生成边界
		enum class SpawnEdge //枚举类 what? 
		{
			Up = 0,
			Down,
			Left,
			Right
		};

		// 将敌人生成在地图外的随机位置
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

	bool CheckBulletCollision(const Bullet& bullet) const
	{
		//将子弹等效为点，判断点是否在敌人矩形碰撞箱内
		bool is_overlap_x = bullet.position.x >= position.x&&bullet.position.x <= position.x + FRAME_WIDTH;
		bool is_overlap_y = bullet.position.y >= position.y&&bullet.position.y <= position.y + FRAME_HEIGHT;
		return is_overlap_x && is_overlap_y;
	}

	bool CheckPlayerCollision(const Player& player)
	{
		PNT check_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
		PNT player_collect_leftup = { (player.GetPLAYER_WIDTH() / 5) * 2, (player.GetPLAYER_HEIGHT() / 5) * 2 };// player碰撞判定箱左上点
		PNT player_collect_rightdown = { (player.GetPLAYER_WIDTH() / 5) * 4, (player.GetPLAYER_HEIGHT() / 5) * 4 };// player碰撞判定箱右下点
		PNT player_position=player.GetPosition();// 拿一下玩家现位置
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
		double len_dir = sqrt(dir_x*dir_x + dir_y*dir_y);//  向量
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
		int pos_shadow_y = position.y + FRAME_HEIGHT - 35;      //这会又是35咯?
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

	//接下来是搞个子弹撞击野猪消失术了
	void Hurt(){
		alive = false;
	}

	bool CheckAlive()const{
		return alive;
	}

	bool ASpeed()   //敌人加速
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
	int SPEED = 2;//   敌人移动速度
	const int FRAME_WIDTH = 80;    //敌人宽度
	const int FRAME_HEIGHT = 80;   //敌人高度
	const int SHADOW_WIDTH = 48;    //阴影宽度

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	PNT position = { 0, 0 };
	bool facing_left = false;
	bool alive = true;
};



/*void DrawPlayer(int delta, int dir_x) //  现迁移至Player类中Draw函数
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

//  生成新的敌人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter)%INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

// 更新子弹位置
void UpdateBullets(std::vector<Bullet>& bullet_list, const Player& player)
{
	const double RADIAL_SPEED = 0.0045;                         //径向波动速度:子弹收缩速度
	const double TANGENT_SPEED = 0.0055;                        //切向波动速度:子弹转速
	double radian_interval = 2 * 3.14159 / bullet_list.size();  //子弹间弧度_间隔，计算为2 * PI / bullet_list.size()，确保子弹均匀分布在圆周上
	PNT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount()*RADIAL_SPEED);   // 动态波动半径r，使用sin和GetTickCount获取时间以实现角度变化
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount()*TANGENT_SPEED + radian_interval * i;  //当前子弹所在弧度值α   值会随时间GetTickCount()变大，各子弹间隔由radian_interval*i提供
		bullet_list[i].position.x = player_position.x + player.GetPLAYER_WIDTH() / 2 + (int)(radius*cos(radian)); //  radius是变化的r长，
		bullet_list[i].position.y = player_position.y + player.GetPLAYER_HEIGHT() / 2 + (int)(radius*sin(radian));//  这两个三角函数的调整很有意思哈
	}
}//若想只旋转,那radius不动即可

void DrawPlayerScore(int score){
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d", score), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}


int main()
{
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//创造窗口

	atlas_player_left = new Atlas(_T("img/player_left_%d.png"), 6);
	atlas_player_right = new Atlas(_T("img/player_right_%d.png"), 6);
	atlas_enemy_left = new Atlas(_T("img/enemy_left_%d.png"), 6);
	atlas_enemy_right = new Atlas(_T("img/enemy_right_%d.png"), 6);

	mciSendString(_T("open mus/bgm.mp3 alias BattleBgm"), NULL, 0, NULL); //加载bgm
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL); //加载并命名hit
	//mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);    //已移至StarGameButton
	//                        一直放  把bgm从0开始放


	//显示消息用变量
	static TCHAR tip[64];// 显示猪猪消息
	bool isMessageVisible = false;
	const int messageDisplayTime = 100; // 假设消息显示100帧  
	int currentDisplayFrame = 0;

	int score = 0; //得分
	Player player;	
	ExMessage msg;//定义事件结构
	IMAGE img_menu;//菜单图变量
	IMAGE img_background;//定义背景图片变量名
	std::vector<Enemy*>enemy_list;//  储存Enemy对象指针
	std::vector<Bullet>bullet_list(3);//3个子弹对象
	
	//为按钮初始化
	RECT region_btn_start_game, region_btn_quit_game;//按钮所在矩形

	region_btn_start_game.left = ((WINDOW_WIDTH - BUTTON_WIDTH) / 2);//放置在居中位置
	region_btn_start_game.right = region_btn_start_game.left + BUTTON_WIDTH;
	region_btn_start_game.top = 430;
	region_btn_start_game.bottom = region_btn_start_game.top + BUTTON_HEIGHT;

	region_btn_quit_game.left = ((WINDOW_WIDTH - BUTTON_WIDTH) / 2);//放置在居中位置
	region_btn_quit_game.right = region_btn_quit_game.left + BUTTON_WIDTH;
	region_btn_quit_game.top = 550;
	region_btn_quit_game.bottom = region_btn_quit_game.top + BUTTON_HEIGHT;


	StartGameButton btn_start_game = StartGameButton(region_btn_start_game,
		_T("img/ui_start_idle.png"), _T("img/ui_start_hovered.png"), _T("img / ui_start_pushed.png"));
	QuitGameButton btn_quit_game=QuitGameButton(region_btn_quit_game,
		_T("img/ui_quit_idle.png"), _T("img/ui_quit_hovered.png"), _T("img / ui_quit_pushed.png"));

	loadimage(&img_menu, _T("img/menu.png"));//加载主菜单图
	loadimage(&img_background, _T("img/background.png"));//加载背景图片
	
	
	
	BeginBatchDraw();//========================================================================================开始批量画布
	int a = 0;
	char tt[] = "012345";//测试循环频率的*/



	while (running)
	{
		DWORD start_time = GetTickCount();//===========================================================================定义运行开始耗时,获得滴答声计数

		while (peekmessage(&msg))
		{
			if(is_game_started)
				player.ProcessEvent(msg);
			else //还在主菜单
			{
				btn_start_game.ProcessEvent(msg);
				btn_quit_game.ProcessEvent(msg);
			}
		}

		if (is_game_started)
		{
			// 移动玩家
			player.Move();
			// 更新子弹位置
			UpdateBullets(bullet_list, player);
			// 尝试添加敌人
			TryGenerateEnemy(enemy_list);
			// 更新敌人位置
			for (Enemy* enemy : enemy_list)
				enemy->Move(player);

			// 检测敌人与玩家位置碰撞
			for (Enemy* enemy : enemy_list)
			{
				if (enemy->CheckPlayerCollision(player))
				{
					static TCHAR text[128];
					_stprintf_s(text, _T("最终得分：%d !"), score);
					MessageBox(GetHWnd(), text, _T("游戏结束"), MB_OK);
					running = false;
					break;
				}
			}

			// 检测子弹和敌人的碰撞
			for (Enemy* enemy : enemy_list)
			{
				for (const Bullet& bullet : bullet_list)
				{
					if (enemy->CheckBulletCollision(bullet))
					{
						mciSendString(_T("play hit from 0"), NULL, 0, NULL); //把hit从0开始放，但不repeat
						enemy->Hurt();
						score++;

					}

				}
			}

			//移除生命值归零的敌人
			for (size_t i = 0; i < enemy_list.size(); i++)
			{
				Enemy* enemy = enemy_list[i];

				if (!enemy->CheckAlive())
				{
					std::swap(enemy_list[i], enemy_list.back()); // swap归0enemy到末尾，再pop_back();
					enemy_list.pop_back();
					delete enemy;
				}
				if (score % 10 == 0) {
					if (score != 0)isMessageVisible = true; //ok显示
					enemy_list[i]->ASpeed();

				}
			}


		}

			/*while (peekmessage(&msg))//消息处理
			{

			}*/

			/*if (is_move_up)player_pos.y -= PLAYER_SPEED;
			if (is_move_down)player_pos.y += PLAYER_SPEED;
			if (is_move_left)player_pos.x -= PLAYER_SPEED;
			if (is_move_right)player_pos.x += PLAYER_SPEED;*///会有斜向加速根号2的情况



			/*static int i = 0;//==左派蒙的循环播放变量
			if(++i % 5 == 0)a++;*/

			/*static int counter = 0;//记几次循环放一张图片;
			if (++counter % 5 == 0){ idx_current_anim++;}
			//使动画循环播放
			idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;*/ //旧DrawPlayer
			//a = a % 6;左派蒙的帧a
		

		cleardevice();//============================================================用背景色清空绘图装置,刷新绘图缓冲区?

		if (is_game_started)
		{
			putimage(0, 0, &img_background);	//渲染背景图
			player.Draw(1000 / 60);			//渲染角色60帧
			for (Enemy* enemy : enemy_list)
				enemy->Draw(1000 / 60);//这里刷新之前写成100/60所以敌人动画一卡一卡的
			for (const Bullet& bullet : bullet_list)
				bullet.Draw();
			DrawPlayerScore(score);
			//DrawEnemyScore(isMessageVisible);
			//显示猪猪信息---不能在背景图之前渲染呀
			if (isMessageVisible)
			{
				_stprintf_s(tip, _T("猪猪阵亡了%d个，猪猪要加速咯", score), score);
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				//settextstyle(16, 0, tip);
				outtextxy(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2, tip);


				// 增加当前显示帧数  
				currentDisplayFrame++;

				// 如果已经显示了足够的时间，则隐藏消息  
				if (currentDisplayFrame >= messageDisplayTime) {
					//Sleep(1000);
					isMessageVisible = false;
					currentDisplayFrame = 0; // 重置显示帧数  
				}
			}
		}
		else
		{
			putimage(0, 0, &img_menu);
			btn_start_game.Draw();
			btn_quit_game.Draw();
		}


		//已废弃封装至Player类中：DrawPlayer(1000 / 60, is_move_right - is_move_left);//     相减以判断左右

		//putimage_alpha(player_pos.x,player_pos.y, &img_player_left[idx_current_anim]);//打印帧索引对应的图片
		
		/*outtextxy(0, 0, tt[(a) % 6]);//测试循环频率的输出
		a++;*/
		
		


		FlushBatchDraw();//====================================================================================冲洗批量画布,执行未完成的绘图任务

		DWORD end_time = GetTickCount();//=============================================================================拿结束耗时;
		DWORD delay_time = end_time - start_time;
		if (delay_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delay_time);
		}
	}

	EndBatchDraw();//==========================================================================================关闭批量绘图
	delete atlas_player_left;
	delete atlas_player_right;
	delete atlas_enemy_left;
	delete atlas_enemy_right;
	return 0;
}