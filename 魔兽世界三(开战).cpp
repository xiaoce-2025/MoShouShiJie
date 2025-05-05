#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;


const string wushi_mode[5] = { "dragon","ninja","iceman","lion","wolf" };//武士种类名称
const string group_color[2] = { "red","blue" };//阵营颜色
const int the_num_of_group_color = 2;//阵营的数量
const int the_num_of_wushi_mode = 5;//武士种类的数量
const string weapon_mode[3] = { "sword","bomb","arrow" };
const int the_create_num_of_the_slb_to_wushi[2][5] = { {2,3,4,1,0},{3,0,1,2,4} };//两大阵营生成武士顺序
bool flag_create_wushi[2] = { 0 };
int wushi_HP_init[5], wushi_HP_min;//各种武士初始生命值
int wushi_ATK_init[5];//武士初始攻击力
int time_total = 0;//游戏总时间
int time_goal;
int lion_k;
int city_amount;
class silingbu;
class wushi;
wushi* wushi_create_sum(int i, int j, int k, int m, int l);
void city_create_wushi(wushi* p, int group);
bool win_or_lose;



class silingbu {
private:
	int HP;
	int name;
	int wushi_num[the_num_of_wushi_mode] = { 0 }, wushi_sum = 0;//表示各种武士数量和武士总数量
	int wushi_num_create = 0;//表示即将尝试生成的武士编号（映射前）

public:
	vector<wushi*> warriors;
	void silingbu_init(int i, int j) {//HP表示司令部剩余生命值,name表示司令部编号
		HP = i;
		name = j;
		wushi_num_create = 0;
		wushi_sum = 0;
		for (int i = 0; i < the_num_of_wushi_mode; i++) {
			wushi_num[i] = 0;
		}
	}

	int HP_f() { return HP; }


	void silingbu_wushi_create() {//武士生成
		if (HP < wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]]) {
			//cout << setw(3) << setfill('0') << time_total << " " << group_color[name] << " headquarter stops making warriors" << endl;
			flag_create_wushi[name] = 1;
			return;
		}
		/*
		while (wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]] > HP) {
			wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
		}
		*/
		wushi* p;
		p = wushi_create_sum(wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]], name, the_create_num_of_the_slb_to_wushi[name][wushi_num_create], time_total, wushi_sum + 1);
		warriors.push_back(p);
		city_create_wushi(p, name);
	}

	void after_wushi_create() {
		slb_ws_create_debug(wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]], name, the_create_num_of_the_slb_to_wushi[name][wushi_num_create], time_total, wushi_sum + 1);
		wushi_sum++; wushi_num[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]]++; HP -= wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]];
		wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
	}


	void slb_ws_create_debug(int i, int j, int k, int m, int l) {//武士生成的信息输出
		//HP生命值，group阵营，0红1蓝，mode表示怪物种类,time_appear表示武士生成时间,num为编号
		//cout << wushi_num[wushi_num_create] << " " << wushi_mode[wushi_num_create] << " in " << group_color[name] << " headquarter" << endl;
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[j] << " " << wushi_mode[k] << " " << l << " born" << endl;
	}


	~silingbu() {
		/*
		for (auto i : warriors) {
			delete i;
			warriors.clear();
		}
		*/
	}
};


silingbu red, blue;

class weapon;

class wushi {
protected:
	int HP, group, mode, time_appear, num, atk;
	friend silingbu;
public:
	int weapons_num[3] = { 0 };
	vector <weapon*> weapons;
public:
	wushi(int i, int j, int k, int m, int l) :HP(i), group(j), mode(k), time_appear(m), num(l)
	{//HP生命值，group阵营，0红1蓝，mode表示怪物种类,time_appear表示武士生成时间,num为编号,atk攻击力
		atk = wushi_ATK_init[k];
		wushi_appear_debug(i, j, k, m, l);
	}

	int get_atk() {
		return atk;
	}

	void wushi_appear_debug(int i, int j, int k, int m, int l) {//输出刚刚生成的武士信息+执行司令部后续操作
		//cout << setw(3) << setfill('0') << time_appear << " " << group_color[group] << " " << wushi_mode[mode] << " " << num << " born with strength " << HP << ",";


		if (j == 0) {
			red.after_wushi_create();
		}
		else if (j == 1) {
			blue.after_wushi_create();
		}
		else {
			cout << "ERROR #2" << endl;
		}
	};
	void hurt(int harmness) {//受到攻击
		HP -= harmness;
	}

	virtual ~wushi() {
		for (auto i : weapons) {
			delete i;
			weapons.clear();
		}
	}
	int s_wushi_mode() {
		return mode;
	}
	int s_wushi_num() {
		return num;
	}
	int s_wushi_group() {
		return group;
	}
	int s_wushi_HP() {
		return HP;
	}
	int s_wushi_atk() {
		return atk;
	}
	virtual int dead_detect() {
		if (HP <= 0) {
			return 1;//1表示战死
		}
		else return 0;
	}

	virtual void after_forward() {

	}
};

wushi* city[30][2];


class weapon {
private:
	int broken;
public:
	weapon() {
		broken = 0;
	}
	void broke() {
		broken = 1;
	}
	//返回值1正常，0攻击失败，-1表示武器损毁
	virtual int attack(wushi* p1, wushi* p2) = 0;//p1为武器持有者，p2为武器目标
	//mode函数，0sword，1bomb，2arrow
	virtual int mode() = 0;
	virtual int s_unbreaking() {
		return -1;
	}
	virtual ~weapon() {

	}

};

class sword :public weapon {
public:
	virtual int attack(wushi* p1, wushi* p2) {
		p2->hurt(p1->get_atk() / 5);
		return 1;

	}
	virtual int mode() {
		return 0;
	}
};

class bomb :public weapon {
private:
	int unbreaking;
public:
	bomb() {
		unbreaking = 1;
	}
	virtual int attack(wushi* p1, wushi* p2) {
		p2->hurt(p1->get_atk() * 2 / 5);
		if (p1->s_wushi_mode() != 1) {//ninja使用炸弹自己不会受伤
			p1->hurt(p1->get_atk() / 5);
		}
		unbreaking--;
		broke();
		return -1;
	}
	virtual int s_unbreaking() {
		return unbreaking;
	}
	virtual int mode() {
		return 1;
	}

};

class arrow :public weapon {
private:
	int unbreaking;
public:
	arrow() {
		unbreaking = 2;
	}
	virtual int attack(wushi* p1, wushi* p2) {
		p2->hurt(p1->get_atk() * 3 / 10);
		unbreaking--;
		if (unbreaking <= 0) {
			broke();
			return -1;
		}
		return 1;
	}
	virtual int mode() {
		return 2;
	}
	virtual int s_unbreaking() {
		return unbreaking;
	}
};


bool cmp_weapons(weapon* p1, weapon* p2) {//武器排序规则
	if (p1->mode() != p2->mode()) {
		return p1->mode() < p2->mode();
	}
	if (p1->mode() == 2) {
		arrow* a1 = dynamic_cast<arrow*>(p1);
		arrow* a2 = dynamic_cast<arrow*>(p2);
		return (a1->s_unbreaking() < a2->s_unbreaking());
	}
	else {
		return false;
	}
}




weapon* weapon_generate(int mode) {
	weapon* p;
	if (mode == 0) {
		p = new sword;
	}
	else if (mode == 1) {
		p = new bomb;
	}
	else if (mode == 2) {
		p = new arrow;
	}
	else {
		cout << "ERROR！武器生成类型不匹配" << endl;
		p = nullptr;
	}
	return p;
}


class wushi_dragon :public wushi {
private:
	int _weapon;
	float shiqi;
public:
	wushi_dragon(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		//HP生命值，group阵营，0红1蓝，mode表示怪物种类,time_appear表示武士生成时间,num为编号
		weapon* p;
		_weapon = l % 3;
		p = weapon_generate(l % 3);
		weapons.push_back(p);
		weapons_num[_weapon]++;

		shiqi = float(j == 0 ? red.HP_f() : blue.HP_f()) / float(wushi_HP_init[0]);
		wushi_dragon_appear_debug();
	}

	void wushi_dragon_appear_debug() {
		//cout << "It has a " << weapon_mode[_weapon] << ",and it's morale is " << fixed << setprecision(2) << shiqi << endl;
	}
};

class wushi_ninja :public wushi {
private:
	int weapon_1, weapon_2;
public:
	wushi_ninja(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		weapon_1 = l % 3;
		weapon_2 = (l + 1) % 3;


		weapon* p1;
		weapon* p2;
		p1 = weapon_generate(l % 3);
		weapons.push_back(p1);
		weapons_num[weapon_1]++;
		p2 = weapon_generate((l + 1) % 3);
		weapons.push_back(p2);
		weapons_num[weapon_2]++;

		wushi_ninja_appear_debug();
	}

	void wushi_ninja_appear_debug() {
		//cout << "It has a " << weapon_mode[weapon_1] << " and a " << weapon_mode[weapon_2] << endl;
	}
};

class wushi_iceman :public wushi {
private:
	int _weapon;
public:
	wushi_iceman(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {

		_weapon = l % 3;
		weapon* p1;
		p1 = weapon_generate(l % 3);
		weapons.push_back(p1);
		weapons_num[_weapon]++;

		wushi_iceman_appear_debug();
	}

	void wushi_iceman_appear_debug() {
		//cout << "It has a " << weapon_mode[_weapon] << endl;
	}

	virtual void after_forward() {
		HP -= HP / 10;
	}
};

class wushi_lion :public wushi {
private:
	int _weapon;
	int loyalty;
public:
	virtual int dead_detect() {
		if (HP <= 0) {
			return 1;
		}
		else if (loyalty <= 0) {
			return 2;
		}
		else return 0;
	}
	wushi_lion(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		loyalty = (j == 0 ? red.HP_f() : blue.HP_f());

		_weapon = l % 3;
		weapon* p1;
		p1 = weapon_generate(l % 3);
		weapons_num[_weapon]++;

		weapons.push_back(p1);

		wushi_lion_appear_debug();
	}

	void wushi_lion_appear_debug() {
		cout << "Its loyalty is " << loyalty << endl;
	}

	virtual void after_forward() {
		loyalty -= lion_k;
	}

};


class wushi_wolf :public wushi {
private:

public:
	wushi_wolf(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {

		wushi_wolf_appear_debug();
	}

	void wushi_wolf_appear_debug() {

	}
};



wushi* wushi_create_sum(int i, int j, int k, int m, int l) {
	wushi* p;
	if (k == 0) {
		p = new wushi_dragon(i, j, k, m, l);
	}
	else if (k == 1) {
		p = new wushi_ninja(i, j, k, m, l);
	}
	else if (k == 2) {
		p = new wushi_iceman(i, j, k, m, l);
	}
	else if (k == 3) {
		p = new wushi_lion(i, j, k, m, l);
	}
	else if (k == 4) {
		p = new wushi_wolf(i, j, k, m, l);
	}
	else {
		cout << "ERROR #1" << endl;
		p = nullptr;
	}
	return p;
}





void game_init() {//全盘游戏初始化
	time_total = 0;
	flag_create_wushi[0] = 0;
	flag_create_wushi[1] = 0;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 2; j++) {
			city[i][j] = nullptr;
		}
	}
	win_or_lose = false;
}




void timeline_lion_runaway() {//狮子逃跑
	//城市武士信息删除+输出
	for (int i = 1; i <= city_amount; i++) {
		for (int j = 0; j < 2; j++) {
			if (city[i][j] != nullptr) {
				//调试：cout << i << " " << j << endl;
				//调试：cout << city[i][j]->dead_detect() << endl;
				if (city[i][j]->dead_detect() == 2) {
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][j]->s_wushi_group()] << " " << wushi_mode[city[i][j]->s_wushi_mode()] << " " << city[i][j]->s_wushi_num() << " ran away" << endl;
					city[i][j] = nullptr;
				}
			}
		}
	}


	//从司令部武士信息中删除
	/*
	auto it = red.warriors.begin();
	while (it != red.warriors.end()) {
		if ((*it)->dead_detect()==2) {//狮子逃跑
			delete* it;
			it = red.warriors.erase(it);
		}
		else {
			++it;
		}
	}
	it = blue.warriors.begin();

	while (it != blue.warriors.end()) {
		if ((*it)->dead_detect()==2) {//狮子逃跑
			delete* it;
			it = blue.warriors.erase(it);
		}
		else {
			++it;
		}
	}
	*/
}

void city_create_wushi(wushi* p, int group) {//司令部位置武士处理
	if (group == 1) {
		city[city_amount + 1][1] = p;
	}
	else if (group == 0) {
		city[0][0] = p;
	}
	else
	{
		cout << "ERROR! #444" << endl;
	}
}

wushi* city_ys[22][2];

void wushi_forward() {//武士前进
	int i = 1;
	//复制一份武士数据供后面输出用
	for (int i = 0; i <= city_amount+1; i++) {
		for (int j = 0; j < 2; j++) {
			city_ys[i][j] = city[i][j];
		}
	}




	//实际的武士移动
	for (i = city_amount+1; i >= 1; i--) {
		if (city[i - 1][0] != nullptr) {
			city[i][0] = city[i - 1][0];
			city[i - 1][0] = nullptr;
			city[i][0]->after_forward();
		}
	}
	for (int i = 0; i <= city_amount; i++) {
		if (city[i + 1][1] != nullptr) {
			city[i][1] = city[i + 1][1];
			city[i + 1][1] = nullptr;
			city[i][1]->after_forward();
		}
	}

	//以上为实际操作部分，下面均为信息输出

	i = 1;
	
	if (city_ys[i][1] != nullptr) {


		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city_ys[i][1]->s_wushi_group()] << " " << wushi_mode[city_ys[i][1]->s_wushi_mode()] << " " << city_ys[i][1]->s_wushi_num() << " reached red headquarter";
		cout << " with " << city_ys[i][1]->s_wushi_HP() << " elements and force " << city_ys[i][1]->s_wushi_atk() << endl;


		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << "red headquarter was taken" << endl;
		win_or_lose = true;
		
	}


	for (i = 1; i <= city_amount; i++) {
		if (city_ys[i - 1][0] != nullptr) {


			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city_ys[i - 1][0]->s_wushi_group()] << " " << wushi_mode[city_ys[i - 1][0]->s_wushi_mode()] << " " << city_ys[i - 1][0]->s_wushi_num() << " marched to city ";
			cout << i << " with " << city_ys[i - 1][0]->s_wushi_HP() << " elements and force " << city_ys[i - 1][0]->s_wushi_atk() << endl;
			/*
			city[i][0] = city[i - 1][0];
			city[i-1][0] = nullptr;
			city[i][0]->after_forward();
			*/

		}
		if (city_ys[i + 1][1] != nullptr) {
			//city[i][1] = city[i+1][1];

			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city_ys[i + 1][1]->s_wushi_group()] << " " << wushi_mode[city_ys[i + 1][1]->s_wushi_mode()] << " " << city_ys[i + 1][1]->s_wushi_num() << " marched to city ";
			cout << i << " with " << city_ys[i + 1][1]->s_wushi_HP() << " elements and force " << city_ys[i + 1][1]->s_wushi_atk() << endl;

			//city[i+1][1] = nullptr;
			//city[i][1]->after_forward();
		}
	}
	i = city_amount + 1;

	if (city_ys[i - 1][0] != nullptr) {
		//city[i][0] = city[i - 1][0];

		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city_ys[i-1][0]->s_wushi_group()] << " " << wushi_mode[city_ys[i-1][0]->s_wushi_mode()] << " " << city_ys[i-1][0]->s_wushi_num() << " reached blue headquarter";
		cout << " with " << city_ys[i-1][0]->s_wushi_HP() << " elements and force " << city_ys[i-1][0]->s_wushi_atk() << endl;
		/*
		city[i - 1][0] = nullptr;
		city[i][0]->after_forward();
		*/
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << "blue headquarter was taken" << endl;
		win_or_lose = true;

	}
	

}

//每个武士汇报武器情况
void warrior_check() {
	for (int i = 0; i <= city_amount + 1; i++) {
		for (int j = 0; j < 2; j++) {
			if (city[i][j] != nullptr) {
				
				for (int i_ = 0; i_ < 3; i_++) {
					city[i][j]->weapons_num[i_] = 0;
				}
				for (auto h : city[i][j]->weapons) {
					city[i][j]->weapons_num[h->mode()]++;
				}
				
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << group_color[city[i][j]->s_wushi_group()] << " " << wushi_mode[city[i][j]->s_wushi_mode()] << " " << city[i][j]->s_wushi_num() << " has ";
				for (int k = 0; k < 3; k++) {
					cout << city[i][j]->weapons_num[k] << " " << weapon_mode[k] << " ";
				}
				cout << "and " << city[i][j]->s_wushi_HP() << " elements" << endl;
			}
		}
	}

}

void wolf_snatch() {//抢夺武器
	for (int i = 1; i <= city_amount; i++) {
		if (city[i][0] != nullptr && city[i][1] != nullptr) {
			if (city[i][0]->s_wushi_mode() == 4 && city[i][1]->s_wushi_mode() != 4) {
				int sum_w;
				sum_w = city[i][0]->weapons_num[0] + city[i][0]->weapons_num[1] + city[i][0]->weapons_num[2];
				for (int j = 0; j < 3; j++) {
					//cout << "抢武器" << j << endl;
					if (city[i][1]->weapons_num[j] > 0) {
						sort(city[i][1]->weapons.begin(), city[i][1]->weapons.end(), cmp_weapons);
						reverse(city[i][1]->weapons.begin(), city[i][1]->weapons.end());

						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num() << " took ";
						cout << min(10 - sum_w, city[i][1]->weapons_num[j]) << " " << weapon_mode[j] << " from ";
						cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num() << " in city " << i << endl;
						/*
						while (sum_w <= 10 && city[i][1]->weapons_num[j] >= 0) {
							sum_w++;
							city[i][0]->weapons_num[j]++;
							city[i][1]->weapons_num[j]--;
							city[i][0]->weapons.push_back(city[i][1]->weapons[city[i][1]->weapons.size() - 1]);
							city[i][1]->weapons.pop_back();

						}
						*/
						//
						int snatched = 0;
						int max_snatch = min(10 - sum_w, city[i][1]->weapons_num[j]);
						while (snatched < max_snatch) {
							city[i][0]->weapons_num[j]++;
							city[i][1]->weapons_num[j]--;
							city[i][0]->weapons.push_back(city[i][1]->weapons.back());
							city[i][1]->weapons.pop_back();
							snatched++;
							sum_w++;
						}
						break;
					}
				}
			}
			else if (city[i][0]->s_wushi_mode() != 4 && city[i][1]->s_wushi_mode() == 4) {
				swap(city[i][0], city[i][1]);
				int sum_w;
				sum_w = city[i][0]->weapons_num[0] + city[i][0]->weapons_num[1] + city[i][0]->weapons_num[2];
				for (int j = 0; j < 3; j++) {
					if (city[i][1]->weapons_num[j] > 0) {
						sort(city[i][1]->weapons.begin(), city[i][1]->weapons.end(), cmp_weapons);
						reverse(city[i][1]->weapons.begin(), city[i][1]->weapons.end());

						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num() << " took ";
						cout << min(10 - sum_w, city[i][1]->weapons_num[j]) << " " << weapon_mode[j] << " from ";
						cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num() << " in city " << i << endl;
						/*
						while (sum_w <= 10 && city[i][1]->weapons_num[j] >= 0) {
							sum_w++;
							city[i][0]->weapons_num[j]++;
							city[i][1]->weapons_num[j]--;
							city[i][0]->weapons.push_back(city[i][1]->weapons[city[i][1]->weapons.size() - 1]);
							city[i][1]->weapons.pop_back();

						}
						*/
						//
						int snatched = 0;
						int max_snatch = min(10 - sum_w, city[i][1]->weapons_num[j]);
						while (snatched < max_snatch) {
							city[i][0]->weapons_num[j]++;
							city[i][1]->weapons_num[j]--;
							city[i][0]->weapons.push_back(city[i][1]->weapons.back());
							city[i][1]->weapons.pop_back();
							snatched++;
							sum_w++;
						}
						break;
					}
				}
				swap(city[i][0], city[i][1]);
			}
		}
	}
}


/*
void fight_weapon(wushi *p1, wushi *p2){
	sort(p1->weapons.begin(), p1->weapons.end(), cmp_weapons);
	sort(p2->weapons.begin(), p2->weapons.end(), cmp_weapons);
	int i = 0, j = 0,flag_temp1;
	while ((p1->weapons.size() > 0 || p2->weapons.size() > 0) && (p1->s_wushi_HP() > 0 && p2->s_wushi_HP() > 0)) {
		flag_temp1 = p1->weapons[i]->attack(p1, p2);
		if (flag_temp1 == -1) {

		}

	}

}
*/

/*
void city_weapon_fight() {
	for (int i = 1; i <= city_amount; i++) {
		if (city[i][0] != nullptr && city[i][1] != nullptr) {

		}
	}
}
*/




//缴获武器
void captureWeapons(wushi* winner, wushi* loser) {
	vector<weapon*> captured;
	for (auto w : loser->weapons) {
		captured.push_back(w);
	}
	sort(captured.begin(), captured.end(), [](weapon* a, weapon* b) {
		if (a->mode() != b->mode()) {
			return a->mode() < b->mode();
		}
		else {
			if (a->mode() == 2) {
				arrow* aa = dynamic_cast<arrow*>(a);
				arrow* ab = dynamic_cast<arrow*>(b);
				return aa->s_unbreaking() > ab->s_unbreaking();
			}
			return false;
		}
		});
	//缴获武器，max=10
	for (auto w : captured) {
		if (winner->weapons.size() >= 10) break;
		winner->weapons.push_back(w);
		winner->weapons_num[w->mode()]++;
		//移除
		auto it = find(loser->weapons.begin(), loser->weapons.end(), w);
		if (it != loser->weapons.end()) {
			loser->weapons.erase(it);
			loser->weapons_num[w->mode()]--;
		}
	}
}

//战斗处理函数
void city_weapon_fight() {
	for (int i = 1; i <= city_amount; i++) {
		if (city[i][0] != nullptr && city[i][1] != nullptr) {
			wushi* red_w = city[i][0];
			wushi* blue_w = city[i][1];
			int first_attacker = (i % 2 == 1) ? 0 : 1; // 0红先，1蓝先

			vector<weapon*> red_weapons = red_w->weapons;
			sort(red_weapons.begin(), red_weapons.end(), cmp_weapons);
			deque<weapon*> red_queue(red_weapons.begin(), red_weapons.end());

			vector<weapon*> blue_weapons = blue_w->weapons;
			sort(blue_weapons.begin(), blue_weapons.end(), cmp_weapons);
			deque<weapon*> blue_queue(blue_weapons.begin(), blue_weapons.end());

			int turn = first_attacker;
			bool fight_over = false;
			int prev_red_hp = -1, prev_blue_hp = -1,flag_changeturn = 0;

			int same_time = 0;

			while (!fight_over) {
				int current_red_hp = max(red_w->s_wushi_HP(), 0);
				int current_blue_hp = max(blue_w->s_wushi_HP(), 0);

				//检查是否双方死亡
				bool red_dead = (current_red_hp <= 0);
				bool blue_dead = (current_blue_hp <= 0);
				if (red_dead || blue_dead) {
					fight_over = true;
					break;
				}

				//检查生命值
				if (current_red_hp == prev_red_hp && current_blue_hp == prev_blue_hp ) {
					if ((red_queue.empty() && blue_queue.empty()) || same_time>=21) {
						fight_over = true;
						break;
					}
					else {
						same_time++;
					}
					
				}
				else {
					same_time = 0;
				}
				prev_red_hp = current_red_hp;
				prev_blue_hp = current_blue_hp;
				flag_changeturn = 0;

				if (turn == 0) { //红attack
					if (red_queue.empty()) {
						if (!blue_queue.empty()) {
							flag_changeturn = 1;
						}
						turn = 1;
						continue;
					}
					weapon* w = red_queue.front();
					red_queue.pop_front();
					int atk_result = w->attack(red_w, blue_w);
					if (atk_result == -1) {
						//武器销毁(含中间销毁)
						auto it = find(red_w->weapons.begin(), red_w->weapons.end(), w);
						if (it != red_w->weapons.end()) {
							red_w->weapons.erase(it);
							red_w->weapons_num[w->mode()]--;
						}
					}
					else {
						if (w->mode() == 0) { // sword
							red_queue.push_back(w);
						}
						else if (w->mode() == 2) { // arrow
							arrow* a = dynamic_cast<arrow*>(w);
							if (a->s_unbreaking() > 0) {
								red_queue.push_back(w);
							}
						}
					}
					turn = 1;
				}
				else { //蓝
					if (blue_queue.empty()) {
						if (!red_queue.empty()) {
							flag_changeturn = 1;
						}
						turn = 0;
						continue;
					}
					weapon* w = blue_queue.front();
					blue_queue.pop_front();
					int atk_result = w->attack(blue_w, red_w);
					if (atk_result == -1) {
						auto it = find(blue_w->weapons.begin(), blue_w->weapons.end(), w);
						if (it != blue_w->weapons.end()) {
							blue_w->weapons.erase(it);
							blue_w->weapons_num[w->mode()]--;
						}
					}
					else {
						if (w->mode() == 0) {
							blue_queue.push_back(w);
						}
						else if (w->mode() == 2) {
							arrow* a = dynamic_cast<arrow*>(w);
							if (a->s_unbreaking() > 0) {
								blue_queue.push_back(w);
							}
						}
					}
					turn = 0;
				}
			}

			//战斗结果
			bool red_alive = red_w->s_wushi_HP() > 0;
			bool blue_alive = blue_w->s_wushi_HP() > 0;

			cout << setw(3) << setfill('0') << time_total / 60 << ":"
				<< setw(2) << setfill('0') << time_total % 60 << " ";
			if (!red_alive && !blue_alive) {
				cout << "both red " << wushi_mode[red_w->s_wushi_mode()] << " " << red_w->s_wushi_num()
					<< " and blue " << wushi_mode[blue_w->s_wushi_mode()] << " " << blue_w->s_wushi_num()
					<< " died in city " << i << endl;
				city[i][0] = city[i][1] = nullptr;
				delete red_w;
				delete blue_w;
			}
			else if (!red_alive) {
				cout << "blue " << wushi_mode[blue_w->s_wushi_mode()] << " " << blue_w->s_wushi_num()
					<< " killed red " << wushi_mode[red_w->s_wushi_mode()] << " " << red_w->s_wushi_num()
					<< " in city " << i << " remaining " << blue_w->s_wushi_HP() << " elements" << endl;
				captureWeapons(blue_w, red_w);
				if (blue_w->s_wushi_mode() == 0) {//欢呼
					cout << setw(3) << setfill('0') << time_total / 60 << ":"
						<< setw(2) << setfill('0') << time_total % 60 << " "
						<< "blue dragon " << blue_w->s_wushi_num() << " yelled in city " << i << endl;
				}
				city[i][0] = nullptr;
				delete red_w;
			}
			else if (!blue_alive) {
				cout << "red " << wushi_mode[red_w->s_wushi_mode()] << " " << red_w->s_wushi_num()
					<< " killed blue " << wushi_mode[blue_w->s_wushi_mode()] << " " << blue_w->s_wushi_num()
					<< " in city " << i << " remaining " << red_w->s_wushi_HP() << " elements" << endl;
				captureWeapons(red_w, blue_w);
				if (red_w->s_wushi_mode() == 0) {//欢呼
					cout << setw(3) << setfill('0') << time_total / 60 << ":"
						<< setw(2) << setfill('0') << time_total % 60 << " "
						<< "red dragon " << red_w->s_wushi_num() << " yelled in city " << i << endl;
				}
				city[i][1] = nullptr;
				delete blue_w;
			}
			else {
				cout << "both red " << wushi_mode[red_w->s_wushi_mode()] << " " << red_w->s_wushi_num()
					<< " and blue " << wushi_mode[blue_w->s_wushi_mode()] << " " << blue_w->s_wushi_num()
					<< " were alive in city " << i << endl;
				if (red_w->s_wushi_mode() == 0) {//欢呼
					cout << setw(3) << setfill('0') << time_total / 60 << ":"
						<< setw(2) << setfill('0') << time_total % 60 << " "
						<< "red dragon " << red_w->s_wushi_num() << " yelled in city " << i << endl;
				}
				if (blue_w->s_wushi_mode() == 0) {//欢呼
					cout << setw(3) << setfill('0') << time_total / 60 << ":"
						<< setw(2) << setfill('0') << time_total % 60 << " "
						<< "blue dragon " << blue_w->s_wushi_num() << " yelled in city " << i << endl;
				}


			}
		}
	}
}





void game_timeline() {
	time_total = 0;
	while (time_total <= time_goal && !win_or_lose) {


		//武士降生
		if (flag_create_wushi[0] == 0) {
			red.silingbu_wushi_create();
		}
		if (flag_create_wushi[1] == 0) {
			blue.silingbu_wushi_create();
		}

		time_total += 5;
		if (time_total > time_goal || win_or_lose)	break;
		//lion逃跑
		timeline_lion_runaway();

		time_total += 5;
		if (time_total > time_goal || win_or_lose)	break;
		wushi_forward();
		//武士前进

		time_total += 25;
		if (time_total > time_goal || win_or_lose)	break;
		//wolf抢武器
		wolf_snatch();

		time_total += 5;
		if (time_total > time_goal || win_or_lose)	break;
		//cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		//战斗
		city_weapon_fight();

		//cout <<"dgcyss：进战过程待完善！"<< endl;
		time_total += 10;
		if (time_total > time_goal || win_or_lose)	break;
		//司令部报告生命元
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << red.HP_f() << " elements in red headquarter" << endl;
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << blue.HP_f() << " elements in blue headquarter" << endl;

		time_total += 5;
		if (time_total > time_goal || win_or_lose)	break;
		//每个武士报告武器情况
		warrior_check();

		time_total += 5;
	}

}





int main() {
	int n;
	cin >> n;
	for (int mhx_tql = 0; mhx_tql < n; mhx_tql++) {
		cout << "Case " << mhx_tql + 1 << ":" << endl;
		game_init();
		int m;
		cin >> m;
		cin >> city_amount >> lion_k >> time_goal;
		cin >> wushi_HP_init[0];
		wushi_HP_min = wushi_HP_init[0];
		for (int i = 1; i < 5; i++) {
			cin >> wushi_HP_init[i];
			wushi_HP_min = min(wushi_HP_init[i], wushi_HP_min);
		}
		for (int i = 0; i < 5; i++) {
			cin >> wushi_ATK_init[i];
		}
		red.silingbu_init(m, 0);
		blue.silingbu_init(m, 1);

		game_timeline();
	}
}