#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <deque>
#include <cstdint>
#include <algorithm>
#include <fstream>
using namespace std;

const string wushi_mode[5] = {"dragon", "ninja", "iceman", "lion", "wolf"}; // ��ʿ��������
const string group_color[2] = {"red", "blue"};								// ��Ӫ��ɫ
const int the_num_of_group_color = 2;										// ��Ӫ������
const int the_num_of_wushi_mode = 5;										// ��ʿ���������
const string weapon_mode[3] = {"sword", "bomb", "arrow"};
const int the_create_num_of_the_slb_to_wushi[2][5] = {{2, 3, 4, 1, 0}, {3, 0, 1, 2, 4}}; // ������Ӫ������ʿ˳��
bool flag_create_wushi[2] = {0};
int wushi_HP_init[5], wushi_HP_min; // ������ʿ��ʼ����ֵ
int wushi_ATK_init[5];				// ��ʿ��ʼ������
int time_total = 0;					// ��Ϸ��ʱ��
int time_goal;
int lion_k;
int arrow_R;
int city_amount;
class silingbu;
class wushi;
wushi *wushi_create_sum(int i, int j, int k, int m, int l);
void city_create_wushi(wushi *p, int group);
bool win_or_lose;
int silingbu_enemynum[2];

class silingbu
{
private:
	int HP;
	int name;
	int wushi_num[the_num_of_wushi_mode] = {0}, wushi_sum = 0; // ��ʾ������ʿ��������ʿ������
	int wushi_num_create = 0;								   // ��ʾ�����������ɵ���ʿ��ţ�ӳ��ǰ��

public:
	vector<wushi *> warriors;
	// ��������Ԫ
	void earnHP(int k)
	{
		HP += k;
		return;
	}
	void useHP(int k)
	{
		HP -= k;
		return;
	}
	void silingbu_init(int i, int j)
	{ // HP��ʾ˾�ʣ������ֵ,name��ʾ˾����
		HP = i;
		name = j;
		wushi_num_create = 0;
		wushi_sum = 0;
		for (int i = 0; i < the_num_of_wushi_mode; i++)
		{
			wushi_num[i] = 0;
		}
	}

	int HP_f() { return HP; }

	void silingbu_wushi_create()
	{ // ��ʿ����
		if (HP < wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]])
		{
			// cout << setw(3) << setfill('0') << time_total << " " << group_color[name] << " headquarter stops making warriors" << endl;
			return;
		}
		/*
		while (wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]] > HP) {
			wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
		}
		*/
		wushi *p;
		p = wushi_create_sum(wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]], name, the_create_num_of_the_slb_to_wushi[name][wushi_num_create], time_total, wushi_sum + 1);
		warriors.push_back(p);
		city_create_wushi(p, name);
	}

	void after_wushi_create()
	{
		slb_ws_create_debug(wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]], name, the_create_num_of_the_slb_to_wushi[name][wushi_num_create], time_total, wushi_sum + 1);
		wushi_sum++;
		wushi_num[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]]++;
		HP -= wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]];
		wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
	}

	void slb_ws_create_debug(int i, int j, int k, int m, int l)
	{ // ��ʿ���ɵ���Ϣ���
		// HP����ֵ��group��Ӫ��0��1����mode��ʾ��������,time_appear��ʾ��ʿ����ʱ��,numΪ���
		// cout << wushi_num[wushi_num_create] << " " << wushi_mode[wushi_num_create] << " in " << group_color[name] << " headquarter" << endl;
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[j] << " " << wushi_mode[k] << " " << l << " born" << endl;
	}

	~silingbu()
	{
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

class wushi
{
protected:
	int HP, group, mode, time_appear, num, atk;
	friend silingbu;

public:
	int weapons_num[3] = {0};
	vector<weapon *> weapons;

public:
	wushi(int i, int j, int k, int m, int l) : HP(i), group(j), mode(k), time_appear(m), num(l)
	{ // HP����ֵ��group��Ӫ��0��1����mode��ʾ��������,time_appear��ʾ��ʿ����ʱ��,numΪ���,atk������
		atk = wushi_ATK_init[k];
		wushi_appear_debug(i, j, k, m, l);
	}

	int get_atk()
	{
		return atk;
	}

	void wushi_appear_debug(int i, int j, int k, int m, int l)
	{ // ����ո����ɵ���ʿ��Ϣ+ִ��˾���������
		// cout << setw(3) << setfill('0') << time_appear << " " << group_color[group] << " " << wushi_mode[mode] << " " << num << " born with strength " << HP << ",";

		if (j == 0)
		{
			red.after_wushi_create();
		}
		else if (j == 1)
		{
			blue.after_wushi_create();
		}
		else
		{
			cout << "ERROR #2" << endl;
		}
	};
	void hurt(int harmness)
	{ // �ܵ�����
		HP -= harmness;
	}
	void earnHP(int k)
	{
		HP += k;
	}

	virtual ~wushi()
	{
		for (auto i : weapons)
		{
			weapons.clear();
		}
	}
	int s_wushi_mode()
	{
		return mode;
	}
	int s_wushi_num()
	{
		return num;
	}
	int s_wushi_group()
	{
		return group;
	}
	int s_wushi_HP()
	{
		return HP;
	}
	int s_wushi_atk()
	{
		return atk;
	}
	virtual int dead_detect()
	{
		if (HP <= 0)
		{
			return 1; // 1��ʾս��
		}
		else
			return 0;
	}

	virtual void after_forward()
	{
	}

	virtual weapon *get_weapon(int i)
	{
		return nullptr;
	}
	virtual void have_weapon(int i, weapon *p)
	{
		return;
	}
	virtual void delete_weapon(int i)
	{
		return;
	}
	virtual void Iwin(bool k)
	{
		return;
	}
	virtual double s_dragon_shiqi()
	{
		return 0;
	}
};

wushi *city[30][2];
wushi *city_wolfsearch[30][2];
int city_flag_color[30][2]; // ����������ɫ
// ����[][0]���ԣ�-1Ϊ��ʤ����¼��0Ϊ�죬1Ϊ��ʤһ�Σ�[][1]���ԣ�-1�����ӣ�0Ϊ��ɫ���ӣ�1Ϊ��ɫ����
int HP_city[30];
bool is_arrow_battle[30];

class weapon
{
protected:
	int broken;
	int atk;

public:
	weapon()
	{
		broken = 0;
		atk = 0;
	}
	void broke()
	{
		broken = 1;
	}
	// ����ֵ1������0����ʧ�ܣ�-1��ʾ�������
	virtual int attack(wushi *p1, wushi *p2) = 0; // p1Ϊ���������ߣ�p2Ϊ����Ŀ��
	// mode������0sword��1bomb��2arrow
	virtual int mode() = 0;
	virtual int s_unbreaking()
	{
		return -1;
	}
	virtual ~weapon()
	{
	}
	virtual int get_info() = 0;
	virtual bool after_attack_thing() = 0;
	virtual bool if_broken() {
		return false;
	}
};

class sword : public weapon
{
public:
	sword(wushi *p)
	{
		atk = int(p->get_atk() / 5.0);
	}
	virtual int attack(wushi *p1, wushi *p2)
	{
		p2->hurt(p1->get_atk() / 5.0);
		return 1;
	}
	virtual int mode()
	{
		return 0;
	}
	virtual int get_info()
	{
		return atk;
	}
	virtual bool after_attack_thing()
	{
		atk = int(double(atk * 4) / 5);
		if (atk <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual bool if_broken() {
		if (atk <= 0) {
			return true;
		}
		else {
			return false;
		}
	}
};

class bomb : public weapon
{
private:
	int unbreaking;

public:
	bomb(wushi *p)
	{
		unbreaking = 1;
	}
	virtual int attack(wushi *p1, wushi *p2)
	{
		// ʹ��ը����ͬ���ھ�
		p2->hurt(INT32_MAX);
		p1->hurt(INT32_MAX);
		unbreaking--;
		broke();
		return -1;
	}
	virtual int s_unbreaking()
	{
		return unbreaking;
	}
	virtual int mode()
	{
		return 1;
	}
	virtual int get_info()
	{
		return -1;
	}
	virtual bool after_attack_thing()
	{
		return true;
	}
};

class arrow : public weapon
{
private:
	int unbreaking;

public:
	arrow(wushi *p)
	{
		unbreaking = 3;
		atk = arrow_R;
	}
	virtual int attack(wushi *p1, wushi *p2)
	{
		p2->hurt(p1->get_atk() * 3 / 10);
		unbreaking--;
		if (unbreaking <= 0)
		{
			broke();
			return -1;
		}
		return 1;
	}
	virtual int mode()
	{
		return 2;
	}
	virtual int s_unbreaking()
	{
		return unbreaking;
	}
	virtual int get_info()
	{
		return unbreaking;
	}
	virtual bool after_attack_thing()
	{
		unbreaking--;
		if (unbreaking <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

weapon *weapon_generate(int mode, wushi *p1)
{
	weapon *p;
	if (mode == 0)
	{
		p = new sword(p1);
	}
	else if (mode == 1)
	{
		p = new bomb(p1);
	}
	else if (mode == 2)
	{
		p = new arrow(p1);
	}
	else
	{
		cout << "ERROR�������������Ͳ�ƥ��" << endl;
		p = nullptr;
	}
	return p;
}

class wushi_dragon : public wushi
{
private:
	double shiqi;
	weapon *weapons[3];

public:
	wushi_dragon(int i, int j, int k, int m, int l) : wushi(i, j, k, m, l)
	{
		// HP����ֵ��group��Ӫ��0��1����mode��ʾ��������,time_appear��ʾ��ʿ����ʱ��,numΪ���
		for (int i = 0; i < 3; i++)
		{
			weapons[i] = nullptr;
		}
		weapons[l % 3] = weapon_generate(l % 3, this);
		weapons_num[l % 3]++;
		if (weapons[l % 3]->if_broken()) {
			weapons[l % 3] = nullptr;
			weapons_num[l % 3]--;
		}

		shiqi = 1.0 * (j == 0 ? red.HP_f() : blue.HP_f()) / wushi_HP_init[0];
		wushi_dragon_appear_debug();
	}

	void wushi_dragon_appear_debug()
	{
		cout << "Its morale is ";
		// �������֣���cout�Ļ���Ȼ���������룬���ǺͲ�������out�и��ı��������Ľ����̫һ����������
		// printf("%.2lf\n", shiqi);
		double eps = 1e-6;
		// if (abs(shiqi - 11.125) < eps) {
		// cout << "11.13" << endl;
		//}
		// else
		cout << fixed << setprecision(2) << 1.0 * (group == 0 ? red.HP_f() : blue.HP_f()) / wushi_HP_init[0] << endl;
	}
	virtual weapon *get_weapon(int i)
	{
		return weapons[i];
	}
	virtual void delete_weapon(int i)
	{
		weapons[i] = nullptr;
		return;
	}
	virtual void Iwin(bool k)
	{
		if (k)
		{
			shiqi += 0.2;
		}
		else
		{
			shiqi -= 0.2;
		}
		return;
	}
	virtual double s_dragon_shiqi()
	{
		return shiqi;
	}
};

class wushi_ninja : public wushi
{
private:
	weapon *weapons[3];

public:
	wushi_ninja(int i, int j, int k, int m, int l) : wushi(i, j, k, m, l)
	{
		for (int i = 0; i < 3; i++)
		{
			weapons[i] = nullptr;
		}
		weapons[l % 3] = weapon_generate(l % 3, this);
		weapons[(l + 1) % 3] = weapon_generate((l + 1) % 3, this);

		weapons_num[l % 3]++;
		weapons_num[(l + 1) % 3]++;

		if (weapons[l % 3]->if_broken()) {
			weapons[l % 3] = nullptr;
			weapons_num[l % 3]--;
		}

		if (weapons[(l +1 ) % 3]->if_broken()) {
			weapons[(l + 1) % 3] = nullptr;
			weapons_num[(l + 1) % 3]--;
		}

		wushi_ninja_appear_debug();
	}

	void wushi_ninja_appear_debug()
	{
		// cout << "It has a " << weapon_mode[weapon_1] << " and a " << weapon_mode[weapon_2] << endl;
	}
	virtual weapon *get_weapon(int i)
	{
		return weapons[i];
	}
	virtual void delete_weapon(int i)
	{
		weapons[i] = nullptr;
		return;
	}
};

class wushi_iceman : public wushi
{
private:
	weapon *weapons[3];
	int forward_flag;

public:
	wushi_iceman(int i, int j, int k, int m, int l) : wushi(i, j, k, m, l)
	{
		for (int i = 0; i < 3; i++)
		{
			weapons[i] = nullptr;
		}
		forward_flag = -1;
		weapons[l % 3] = weapon_generate(l % 3, this);
		weapons_num[l % 3]++;
		if (weapons[l % 3]->if_broken()) {
			weapons[l % 3] = nullptr;
			weapons_num[l % 3]--;
		}

		wushi_iceman_appear_debug();
	}

	void wushi_iceman_appear_debug()
	{
		// cout << "It has a " << weapon_mode[_weapon] << endl;
	}

	virtual void after_forward()
	{
		forward_flag = (forward_flag + 1) % 2;
		if (forward_flag == 1)
		{
			if (HP > 9)
			{
				HP -= 9;
			}
			else
			{
				HP = 1;
			}
			atk += 20;
		}
	}
	virtual weapon *get_weapon(int i)
	{
		return weapons[i];
	}
	virtual void delete_weapon(int i)
	{
		weapons[i] = nullptr;
		return;
	}
};

class wushi_lion : public wushi
{
private:
	int loyalty;

public:
	virtual int dead_detect()
	{
		if (HP <= 0)
		{
			return 1;
		}
		else if (loyalty <= 0)
		{
			return 2;
		}
		else
			return 0;
	}
	wushi_lion(int i, int j, int k, int m, int l) : wushi(i, j, k, m, l)
	{
		loyalty = (j == 0 ? red.HP_f() : blue.HP_f());
		wushi_lion_appear_debug();
	}

	void wushi_lion_appear_debug()
	{
		cout << "Its loyalty is " << loyalty << endl;
	}

	virtual void after_forward()
	{
	}
	virtual void Iwin(bool k)
	{
		if (k)
		{
		}
		else
		{
			loyalty -= lion_k;
		}
		return;
	}
};

class wushi_wolf : public wushi
{
private:
	weapon *weapons[3];

public:
	wushi_wolf(int i, int j, int k, int m, int l) : wushi(i, j, k, m, l)
	{
		for (int i = 0; i < 3; i++)
		{
			weapons[i] = nullptr;
		}
		wushi_wolf_appear_debug();
	}

	void wushi_wolf_appear_debug()
	{
	}
	virtual weapon *get_weapon(int i)
	{
		return weapons[i];
	}
	virtual void delete_weapon(int i)
	{
		weapons[i] = nullptr;
		return;
	}
	virtual void have_weapon(int i, weapon *p)
	{
		weapons[i] = p;
		return;
	}
};

wushi *wushi_create_sum(int i, int j, int k, int m, int l)
{
	wushi *p;
	if (k == 0)
	{
		p = new wushi_dragon(i, j, k, m, l);
	}
	else if (k == 1)
	{
		p = new wushi_ninja(i, j, k, m, l);
	}
	else if (k == 2)
	{
		p = new wushi_iceman(i, j, k, m, l);
	}
	else if (k == 3)
	{
		p = new wushi_lion(i, j, k, m, l);
	}
	else if (k == 4)
	{
		p = new wushi_wolf(i, j, k, m, l);
	}
	else
	{
		cout << "ERROR #1" << endl;
		p = nullptr;
	}
	return p;
}

void game_init()
{ // ȫ����Ϸ��ʼ��
	time_total = 0;
	flag_create_wushi[0] = 0;
	flag_create_wushi[1] = 0;
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			city[i][j] = nullptr;
			city_flag_color[i][j] = -1;
		}
		HP_city[i] = 0;
		is_arrow_battle[i] = false;
	}
	win_or_lose = false;
	silingbu_enemynum[0] = 0;
	silingbu_enemynum[1] = 0;
}

// ʨ������
void timeline_lion_runaway()
{
	// ������ʿ��Ϣɾ��+���
	int i = 0, j = 0;
	if (city[i][j] != nullptr)
	{
		// ���ԣ�cout << i << " " << j << endl;
		// ���ԣ�cout << city[i][j]->dead_detect() << endl;
		if (city[i][j]->dead_detect() == 2)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][j]->s_wushi_group()] << " " << wushi_mode[city[i][j]->s_wushi_mode()] << " " << city[i][j]->s_wushi_num() << " ran away" << endl;
			city[i][j] = nullptr;
		}
	}
	for (i = 1; i <= city_amount; i++)
	{
		for (j = 0; j < 2; j++)
		{
			if (city[i][j] != nullptr)
			{
				// ���ԣ�cout << i << " " << j << endl;
				// ���ԣ�cout << city[i][j]->dead_detect() << endl;
				if (city[i][j]->dead_detect() == 2)
				{
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][j]->s_wushi_group()] << " " << wushi_mode[city[i][j]->s_wushi_mode()] << " " << city[i][j]->s_wushi_num() << " ran away" << endl;
					city[i][j] = nullptr;
				}
			}
		}
	}

	i = city_amount + 1;
	j = 1;
	if (city[i][j] != nullptr)
	{
		// ���ԣ�cout << i << " " << j << endl;
		// ���ԣ�cout << city[i][j]->dead_detect() << endl;
		if (city[i][j]->dead_detect() == 2)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][j]->s_wushi_group()] << " " << wushi_mode[city[i][j]->s_wushi_mode()] << " " << city[i][j]->s_wushi_num() << " ran away" << endl;
			city[i][j] = nullptr;
		}
	}
}

// ˾�λ����ʿ����
void city_create_wushi(wushi *p, int group)
{
	if (group == 1)
	{
		city[city_amount + 1][1] = p;
	}
	else if (group == 0)
	{
		city[0][0] = p;
	}
	else
	{
		cout << "ERROR! #444" << endl;
	}
}

wushi *city_ys[22][2];

// ��ʿǰ��
void wushi_forward()
{
	int i = 1;
	// ����һ����ʿ���ݹ����������
	for (int i = 0; i <= city_amount + 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			city_ys[i][j] = city[i][j];
		}
	}

	// ʵ�ʵ���ʿ�ƶ�
	for (i = city_amount + 1; i >= 1; i--)
	{
		if (city[i - 1][0] != nullptr)
		{
			city[i][0] = city[i - 1][0];
			city[i - 1][0] = nullptr;
			city[i][0]->after_forward();
		}
	}
	for (int i = 0; i <= city_amount; i++)
	{
		if (city[i + 1][1] != nullptr)
		{
			city[i][1] = city[i + 1][1];
			city[i + 1][1] = nullptr;
			city[i][1]->after_forward();
		}
	}

	// ����Ϊʵ�ʲ������֣������Ϊ��Ϣ���

	i = 1;

	if (city_ys[i][1] != nullptr)
	{

		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city_ys[i][1]->s_wushi_group()] << " " << wushi_mode[city_ys[i][1]->s_wushi_mode()] << " " << city_ys[i][1]->s_wushi_num() << " reached red headquarter";
		cout << " with " << city[i - 1][1]->s_wushi_HP() << " elements and force " << city[i - 1][1]->s_wushi_atk() << endl;

		silingbu_enemynum[0] += 1;
		if (silingbu_enemynum[0] >= 2)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << "red headquarter was taken" << endl;
			win_or_lose = true;
		}
	}

	for (i = 1; i <= city_amount; i++)
	{
		if (city_ys[i - 1][0] != nullptr)
		{

			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city_ys[i - 1][0]->s_wushi_group()] << " " << wushi_mode[city_ys[i - 1][0]->s_wushi_mode()] << " " << city_ys[i - 1][0]->s_wushi_num() << " marched to city ";
			cout << i << " with " << city[i][0]->s_wushi_HP() << " elements and force " << city[i][0]->s_wushi_atk() << endl;
		}
		if (city_ys[i + 1][1] != nullptr)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city_ys[i + 1][1]->s_wushi_group()] << " " << wushi_mode[city_ys[i + 1][1]->s_wushi_mode()] << " " << city_ys[i + 1][1]->s_wushi_num() << " marched to city ";
			cout << i << " with " << city[i][1]->s_wushi_HP() << " elements and force " << city[i][1]->s_wushi_atk() << endl;
		}
	}
	i = city_amount + 1;

	if (city_ys[i - 1][0] != nullptr)
	{

		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city_ys[i - 1][0]->s_wushi_group()] << " " << wushi_mode[city_ys[i - 1][0]->s_wushi_mode()] << " " << city_ys[i - 1][0]->s_wushi_num() << " reached blue headquarter";
		cout << " with " << city[i][0]->s_wushi_HP() << " elements and force " << city[i][0]->s_wushi_atk() << endl;

		silingbu_enemynum[1] += 1;
		if (silingbu_enemynum[1] >= 2)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << "blue headquarter was taken" << endl;
			win_or_lose = true;
		}
	}
}

// ÿ����ʿ�㱨����������£�
void warrior_check()
{
	for (int i = 0; i <= city_amount + 1; i++)
	{
		if (city[i][0] != nullptr)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num() << " has ";
			bool flag_114514 = false;
			for (int k = 2; k >= 0; k--)
			{
				if (city[i][0]->get_weapon(k) != nullptr)
				{
					if (flag_114514)
					{
						cout << ",";
					}
					flag_114514 = true;
					cout << weapon_mode[k];
					if (city[i][0]->get_weapon(k)->get_info() != -1)
					{
						cout << "(" << city[i][0]->get_weapon(k)->get_info() << ")";
					}
				}
			}
			if (!flag_114514)
			{
				cout << "no weapon";
			}
			cout << endl;
		}
	}
	for (int i = 0; i <= city_amount + 1; i++)
	{
		if (city[i][1] != nullptr)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num() << " has ";
			bool flag_114514 = false;
			for (int k = 2; k >= 0; k--)
			{
				if (city[i][1]->get_weapon(k) != nullptr)
				{
					if (flag_114514)
					{
						cout << ",";
					}
					flag_114514 = true;
					cout << weapon_mode[k];
					if (city[i][1]->get_weapon(k)->get_info() != -1)
					{
						cout << "(" << city[i][1]->get_weapon(k)->get_info() << ")";
					}
				}
			}
			if (!flag_114514)
			{
				cout << "no weapon";
			}
			cout << endl;
		}
	}
}

wushi *city_lion_HP[30][2];

// wolf�ɻ���
void wolf_win(wushi *wolf, wushi *loser)
{
	for (int j = 0; j < 3; j++)
	{
		if (wolf->get_weapon(j) == nullptr && loser->get_weapon(j) != nullptr)
		{
			// cout << wolf->get_weapon(j) << "wolf��ȡ����" << endl;
			wolf->have_weapon(j, loser->get_weapon(j));
		}
	}
}

// ʤ����������
void after_battle_win(int i, int winner)
{
	if (winner == 0)
	{
		city[i][0]->Iwin(true);
		if (city[i][1] != nullptr)
		{
			// ��ʨ��ս��Ѫ���Է�
			if (city[i][1]->s_wushi_mode() == 3)
			{
				city[i][0]->earnHP(city_lion_HP[i][1]->s_wushi_HP());
			}
			city[i][1]->Iwin(false);
		}
	}
	else if (winner == 1)
	{
		if (city[i][0] != nullptr)
		{
			// ��ʨ��ս��Ѫ���Է�
			if (city[i][0]->s_wushi_mode() == 3)
			{
				city[i][1]->earnHP(city_lion_HP[i][0]->s_wushi_HP());
			}
			city[i][0]->Iwin(false);
		}
		city[i][1]->Iwin(true);
	}
	else
	{
		if (city[i][0] != nullptr)
			city[i][0]->Iwin(false);
		if (city[i][1] != nullptr)
			city[i][1]->Iwin(false);
	}
	// dragon����
	if (winner != 1 && city[i][0] != nullptr && city[i][0]->s_wushi_mode() == 0 && ((i % 2 == 1 && city_flag_color[i][1] == -1) || (city_flag_color[i][1] == 0)))
	{
		if (city[i][0]->s_dragon_shiqi() > 0.8)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
			cout << " yelled in city " << i << endl;
		}
	}
	if (winner != 0 && city[i][1] != nullptr && city[i][1]->s_wushi_mode() == 0 && ((i % 2 == 0 && city_flag_color[i][1] == -1) || (city_flag_color[i][1] == 1)))
	{
		if (city[i][1]->s_dragon_shiqi() > 0.8)
		{
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
			cout << " yelled in city " << i << endl;
		}
	}

	// ����ֵ��ȡ
	if (winner == 0)
	{
		// cout << "����" << i << "���ʤ" << endl;
		if (red.HP_f() >= 8)
		{
			red.useHP(8);
			city[i][0]->earnHP(8);
		}
		red.earnHP(HP_city[i]);
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
		cout << " earned " << HP_city[i] << " elements for his headquarter" << endl;
		HP_city[i] = 0;
	}
	else if (winner == 1)
	{
		// cout << "����" << i << "b��ʤ" << endl;
		if (blue.HP_f() >= 8)
		{
			blue.useHP(8);
			city[i][1]->earnHP(8);
		}
		blue.earnHP(HP_city[i]);
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
		cout << " earned " << HP_city[i] << " elements for his headquarter" << endl;
		HP_city[i] = 0;
	}
	// else cout << "����" << i << "���˻�ʤ" << endl;

	// ��������
	if (winner == 0)
	{
		// cout << "winner0" << i << city_flag_color[i][0] << endl;

		if (city_flag_color[i][1] != 0)
		{
			if (city_flag_color[i][0] != 0)
			{
				city_flag_color[i][0] = 0;
			}
			else
			{
				city_flag_color[i][0] = -1;
				city_flag_color[i][1] = 0;
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << "red flag raised in city " << i << endl;
			}
		}
		else
		{
			city_flag_color[i][0] = -1;
		}
	}
	else if (winner == 1)
	{

		// cout << "winner1" << i <<city_flag_color[i][0]<< endl;
		if (city_flag_color[i][1] != 1)
		{
			if (city_flag_color[i][0] != 1)
			{
				city_flag_color[i][0] = 1;
			}
			else
			{
				city_flag_color[i][0] = -1;
				city_flag_color[i][1] = 1;
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << "blue flag raised in city " << i << endl;
			}
		}
		else
		{
			city_flag_color[i][0] = -1;
		}
	}
	else
	{
		city_flag_color[i][0] = -1;
	}

	if (winner == 0)
	{
		// wolf
		if (city[i][0]->s_wushi_mode() == 4)
		{
			wolf_win(city_wolfsearch[i][0], city_wolfsearch[i][1]);
		}
		city[i][1] = nullptr;
	}
	else if (winner == 1)
	{
		// wolf
		if (city[i][1]->s_wushi_mode() == 4)
		{
			wolf_win(city_wolfsearch[i][1], city_wolfsearch[i][0]);
		}
		city[i][0] = nullptr;
	}
}

// ս����������
void city_weapon_fight()
{
	// ��ʨ�ӿ���һ������
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (city[i][j] == nullptr)
			{
				city_lion_HP[i][j] = nullptr;
			}
			else
			{
				city_lion_HP[i][j] = new wushi(*city[i][j]);
			}
		}
	}

	for (int i = 1; i <= city_amount; i++)
	{
		int who_win = -1;
		if (city[i][0] != nullptr && city[i][1] != nullptr)
		{
			if ((i % 2 == 1 && city_flag_color[i][1] == -1) || (city_flag_color[i][1] == 0))
			{
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
				cout << " attacked ";
				cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
				cout << " in city " << i << " with " << city[i][0]->s_wushi_HP() << " elements and force " << city[i][0]->get_atk() << endl;
				int ttt = 0;
				if (city[i][0]->get_weapon(0) != nullptr)
				{
					ttt = city[i][0]->get_weapon(0)->get_info();
					if (city[i][0]->get_weapon(0)->after_attack_thing())
					{
						city[i][0]->delete_weapon(0);
					}
				}
				city[i][1]->hurt(ttt + city[i][0]->s_wushi_atk());
				if (city[i][1]->s_wushi_HP() <= 0)
				{
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
					cout << " was killed in city " << i << endl;
					who_win = 0;
				}
				else if (city[i][1]->s_wushi_mode() != 1)
				{ // nijia������
					ttt = 0;
					if (city[i][1]->get_weapon(0) != nullptr)
					{
						ttt = city[i][1]->get_weapon(0)->get_info();
						if (city[i][1]->get_weapon(0)->after_attack_thing())
						{
							city[i][1]->delete_weapon(0);
						}
					}
					city[i][0]->hurt(int(city[i][1]->s_wushi_atk() / 2) + ttt);
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
					cout << " fought back against ";
					cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
					cout << " in city " << i << endl;
					if (city[i][0]->s_wushi_HP() <= 0)
					{
						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
						cout << " was killed in city " << i << endl;
						who_win = 1;
					}
				}
			}
			else
			{
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
				cout << " attacked ";
				cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
				cout << " in city " << i << " with " << city[i][1]->s_wushi_HP() << " elements and force " << city[i][1]->get_atk() << endl;
				int ttt = 0;
				if (city[i][1]->get_weapon(0) != nullptr)
				{
					ttt = city[i][1]->get_weapon(0)->get_info();
					if (city[i][1]->get_weapon(0)->after_attack_thing())
					{
						city[i][1]->delete_weapon(0);
					}
				}
				city[i][0]->hurt(ttt + city[i][1]->s_wushi_atk());
				if (city[i][0]->s_wushi_HP() <= 0)
				{
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
					cout << " was killed in city " << i << endl;
					who_win = 1;
				}
				else if (city[i][0]->s_wushi_mode() != 1)
				{ // nijia������
					ttt = 0;
					if (city[i][0]->get_weapon(0) != nullptr)
					{
						ttt = city[i][0]->get_weapon(0)->get_info();
						if (city[i][0]->get_weapon(0)->after_attack_thing())
						{
							city[i][0]->delete_weapon(0);
						}
					}
					city[i][1]->hurt(int(city[i][0]->s_wushi_atk() / 2) + ttt);
					cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
					cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
					cout << " fought back against ";
					cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
					cout << " in city " << i << endl;
					if (city[i][1]->s_wushi_HP() <= 0)
					{
						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
						cout << " was killed in city " << i << endl;
						who_win = 0;
					}
				}
			}
		}
		else if (is_arrow_battle[i])
		{
			if (city[i][0] != nullptr)
			{
				who_win = 0;
			}
			else if (city[i][1] != nullptr)
			{
				who_win = 1;
			}
			else
			{
				who_win = -1;
				is_arrow_battle[i] = false;
				continue;
			}
			is_arrow_battle[i] = false;
		}
		else
		{
			continue;
		}
		after_battle_win(i, who_win);
	}
}

// ���в�������Ԫ
void HP_generate()
{
	for (int i = 1; i <= city_amount; i++)
	{
		HP_city[i] += 10;
	}
	return;
}

// ��ȡ��������Ԫ
void get_city_HP()
{
	for (int i = 1; i <= city_amount; i++)
	{
		if (city[i][0] != nullptr && city[i][1] == nullptr)
		{
			red.earnHP(HP_city[i]);
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
			cout << " earned " << HP_city[i] << " elements for his headquarter" << endl;
			HP_city[i] = 0;
		}
		else if (city[i][0] == nullptr && city[i][1] != nullptr)
		{
			blue.earnHP(HP_city[i]);
			cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
			cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
			cout << " earned " << HP_city[i] << " elements for his headquarter" << endl;
			HP_city[i] = 0;
		}
	}
	return;
}

// �ż�
void arrow_attack()
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			city_wolfsearch[i][j] = city[i][j];
		}
	}
	for (int i = 1; i <= city_amount; i++)
	{
		is_arrow_battle[i] = false;
	}
	bool deadflag_1[30][2] = {false};
	for (int i = 1; i <= city_amount; i++)
	{
		if (city[i][0] != nullptr && city[i + 1][1] != nullptr)
		{
			if (city[i][0]->get_weapon(2) != nullptr)
			{
				city[i + 1][1]->hurt(arrow_R);
				if (city[i][0]->get_weapon(2)->after_attack_thing())
				{
					city[i][0]->delete_weapon(2);
				}
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num() << " shot";
				if (city[i + 1][1]->s_wushi_HP() <= 0)
				{
					is_arrow_battle[i + 1] = true;
					deadflag_1[i + 1][1] = true;
					cout << " and killed " << group_color[city[i + 1][1]->s_wushi_group()] << " " << wushi_mode[city[i + 1][1]->s_wushi_mode()] << " " << city[i + 1][1]->s_wushi_num();
				}
				cout << endl;
			}
		}
		if (city[i][1] != nullptr && city[i - 1][0] != nullptr)
		{
			if (city[i][1]->get_weapon(2) != nullptr)
			{
				city[i - 1][0]->hurt(arrow_R);
				if (city[i][1]->get_weapon(2)->after_attack_thing())
				{
					city[i][1]->delete_weapon(2);
				}
				cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
				cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num() << " shot";
				if (city[i - 1][0]->s_wushi_HP() <= 0)
				{
					is_arrow_battle[i - 1] = true;
					deadflag_1[i - 1][0] = true;
					cout << " and killed " << group_color[city[i - 1][0]->s_wushi_group()] << " " << wushi_mode[city[i - 1][0]->s_wushi_mode()] << " " << city[i - 1][0]->s_wushi_num();
				}
				cout << endl;
			}
		}
	}
	for (int i = 0; i <= city_amount + 1; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (deadflag_1[i][j])
			{
				city[i][j] = nullptr;
			}
		}
	}
	return;
}

// bomb��������
void bomb_attack()
{
	for (int i = 1; i <= city_amount; i++)
	{
		if (city[i][0] != nullptr && city[i][1] != nullptr)
		{
			// �칥
			if ((i % 2 == 1 && city_flag_color[i][1] == -1) || (city_flag_color[i][1] == 0))
			{
				int ttt = 0;
				if (city[i][0]->get_weapon(0) != nullptr)
				{
					ttt = city[i][0]->get_weapon(0)->get_info();
				}
				if (ttt + city[i][0]->s_wushi_atk() >= city[i][1]->s_wushi_HP())
				{
					if (city[i][1]->get_weapon(1) != nullptr)
					{
						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
						cout << " used a bomb and killed ";
						cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
						cout << endl;
						city[i][0] = nullptr;
						city[i][1] = nullptr;
					}
				}
				else if (city[i][1]->s_wushi_mode() != 1)
				{ // nijia������
					ttt = 0;
					if (city[i][1]->get_weapon(0) != nullptr)
					{
						ttt = city[i][1]->get_weapon(0)->get_info();
					}
					if (ttt + int(city[i][1]->s_wushi_atk() / 2) >= city[i][0]->s_wushi_HP())
					{
						if (city[i][0]->get_weapon(1) != nullptr)
						{
							cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
							cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
							cout << " used a bomb and killed ";
							cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
							cout << endl;
							city[i][0] = nullptr;
							city[i][1] = nullptr;
						}
					}
				}
			}
			else
			{
				int ttt = 0;
				if (city[i][1]->get_weapon(0) != nullptr)
				{
					ttt = city[i][1]->get_weapon(0)->get_info();
				}
				if (ttt + city[i][1]->s_wushi_atk() >= city[i][0]->s_wushi_HP())
				{
					if (city[i][0]->get_weapon(1) != nullptr)
					{
						cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
						cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
						cout << " used a bomb and killed ";
						cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
						cout << endl;
						city[i][0] = nullptr;
						city[i][1] = nullptr;
					}
				}
				else if (city[i][0]->s_wushi_mode() != 1)
				{ // nijia������
					ttt = 0;
					if (city[i][0]->get_weapon(0) != nullptr)
					{
						ttt = int(city[i][0]->get_weapon(0)->get_info() / 2);
					}
					if (ttt + int(city[i][0]->s_wushi_atk() / 2) >= city[i][1]->s_wushi_HP())
					{
						if (city[i][1]->get_weapon(1) != nullptr)
						{
							cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
							cout << group_color[city[i][1]->s_wushi_group()] << " " << wushi_mode[city[i][1]->s_wushi_mode()] << " " << city[i][1]->s_wushi_num();
							cout << " used a bomb and killed ";
							cout << group_color[city[i][0]->s_wushi_group()] << " " << wushi_mode[city[i][0]->s_wushi_mode()] << " " << city[i][0]->s_wushi_num();
							cout << endl;
							city[i][0] = nullptr;
							city[i][1] = nullptr;
						}
					}
				}
			}
		}
	}
}

// ��ʱ����
void game_timeline()
{
	time_total = 0;
	while (time_total <= time_goal && !win_or_lose)
	{

		// ��ʿ�������£�
		if (flag_create_wushi[0] == 0)
		{
			red.silingbu_wushi_create();
		}
		if (flag_create_wushi[1] == 0)
		{
			blue.silingbu_wushi_create();
		}

		time_total += 5;
		if (time_total > time_goal || win_or_lose)
			break;
		// lion���ܣ��£�
		timeline_lion_runaway();

		time_total += 5;
		if (time_total > time_goal || win_or_lose)
			break;
		// ��ʿǰ�����£�
		wushi_forward();

		time_total += 10;
		if (time_total > time_goal || win_or_lose)
			break;
		// ��������Ԫ���£�
		HP_generate();

		time_total += 10;
		if (time_total > time_goal || win_or_lose)
			break;
		// ��ȡ��������Ԫ���£�
		get_city_HP();

		time_total += 5;
		if (time_total > time_goal || win_or_lose)
			break;
		// ��ʿ�ż����£�
		arrow_attack();

		time_total += 3;
		if (time_total > time_goal || win_or_lose)
			break;
		// bomb����+����
		bomb_attack();

		time_total += 2;
		if (time_total > time_goal || win_or_lose)
			break;
		// cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		// ս�����£�
		city_weapon_fight();

		time_total += 10;
		if (time_total > time_goal || win_or_lose)
			break;
		// ˾���������Ԫ���£�
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << red.HP_f() << " elements in red headquarter" << endl;
		cout << setw(3) << setfill('0') << time_total / 60 << ":" << setw(2) << setfill('0') << time_total % 60 << " ";
		cout << blue.HP_f() << " elements in blue headquarter" << endl;

		time_total += 5;
		if (time_total > time_goal || win_or_lose)
			break;
		// ÿ����ʿ��������������£�
		warrior_check();

		time_total += 5;
	}
}

int main()
{
	// ����ԭ�л�����
	//streambuf *orig_buf = std::cout.rdbuf();

	// ���ļ����ض������
	/*
	ofstream out("output.txt");
	if (out)
	{
		std::cout.rdbuf(out.rdbuf()); // �ؼ��ض������
	}
	*/
	int n;
	cin >> n;
	for (int mhx_tql = 0; mhx_tql < n; mhx_tql++)
	{
		cout << "Case " << mhx_tql + 1 << ":" << endl;
		game_init();
		int m;
		cin >> m;
		cin >> city_amount >> arrow_R >> lion_k >> time_goal;
		cin >> wushi_HP_init[0];
		wushi_HP_min = wushi_HP_init[0];
		for (int i = 1; i < 5; i++)
		{
			cin >> wushi_HP_init[i];
			wushi_HP_min = min(wushi_HP_init[i], wushi_HP_min);
		}
		for (int i = 0; i < 5; i++)
		{
			cin >> wushi_ATK_init[i];
		}
		red.silingbu_init(m, 0);
		blue.silingbu_init(m, 1);

		game_timeline();
	}

	return 0;
}
