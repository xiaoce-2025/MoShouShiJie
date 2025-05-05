#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


const string wushi_mode[5] = { "dragon","ninja","iceman","lion","wolf" };//��ʿ��������
const string group_color[2] = { "red","blue" };//��Ӫ��ɫ
const int the_num_of_group_color = 2;//��Ӫ������
const int the_num_of_wushi_mode=5;//��ʿ���������
const string weapon_mode[3] = { "sword","bomb","arrow" };
const int the_create_num_of_the_slb_to_wushi[2][5] = { {2,3,4,1,0},{3,0,1,2,4} };
bool flag_create_wushi[2] = { 0 };
int wushi_HP_init[5], wushi_HP_min;//������ʿ��ʼ����ֵ
int time_total=0;//��Ϸ��ʱ��

class silingbu;
void wushi_create_sum(int i,int j,int k,int m,int l);


class silingbu {
private:
	int HP;
	int name;
	int wushi_num[the_num_of_wushi_mode] = { 0 }, wushi_sum = 0;//��ʾ������ʿ��������ʿ������
	int wushi_num_create = 0;//��ʾ�����������ɵ���ʿ��ţ�ӳ��ǰ��
public:
	void silingbu_init(int i, int j) {//HP��ʾ˾�ʣ������ֵ,name��ʾ˾����
		HP = i;
		name = j;
		wushi_num_create = 0;
		wushi_sum = 0;
		for (int i = 0; i < the_num_of_wushi_mode; i++) {
			wushi_num[i] = 0;
		}
	}

	int HP_f() { return HP; }


	void silingbu_wushi_create() {//��ʿ����
		if (HP < wushi_HP_min) {
			cout << setw(3) << setfill('0') << time_total << " " << group_color[name] << " headquarter stops making warriors" << endl;
			flag_create_wushi[name] = 1;
			return;
		}
		while (wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]] > HP) {
			wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
		}
		wushi_create_sum(wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]], name, the_create_num_of_the_slb_to_wushi[name][wushi_num_create], time_total, wushi_sum + 1);
	}

	void after_wushi_create() {
		wushi_sum++; wushi_num[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]]++; HP -= wushi_HP_init[the_create_num_of_the_slb_to_wushi[name][wushi_num_create]];
		slb_ws_create_debug(the_create_num_of_the_slb_to_wushi[name][wushi_num_create]);
		wushi_num_create = (wushi_num_create + 1) % the_num_of_wushi_mode;
	}


	void slb_ws_create_debug(int wushi_num_create) {//�����ǰ��Ӫ��ĳ����ʿ������
		cout << wushi_num[wushi_num_create] << " " << wushi_mode[wushi_num_create] << " in " << group_color[name] << " headquarter" << endl;
	}

};


silingbu red,blue;




class wushi {
private:
	int HP, group, mode,time_appear,num;
public:
	wushi(int i, int j, int k,int m,int l):HP(i),group(j),mode(k),time_appear(m),num(l) 
	{//HP����ֵ��group��Ӫ��0��1����mode��ʾ��������,time_appear��ʾ��ʿ����ʱ��,numΪ���
		wushi_appear_debug(i, j, k, m,l);
	}

	void wushi_appear_debug(int i, int j, int k, int m,int l) {//����ո����ɵ���ʿ��Ϣ+ִ��˾���������
		cout << setw(3) << setfill('0') << time_appear << " " << group_color[group] << " " << wushi_mode[mode] << " " << num << " born with strength " << HP << ",";


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
};

class wushi_dragon :public wushi {
private:
	int weapon;
	float shiqi;
public:
	wushi_dragon(int i, int j, int k, int m, int l) :wushi(i,j,k,m,l){
		//HP����ֵ��group��Ӫ��0��1����mode��ʾ��������,time_appear��ʾ��ʿ����ʱ��,numΪ���
		weapon = l % 3;
		shiqi = float(j == 0 ? red.HP_f() : blue.HP_f()) / float(wushi_HP_init[0]);

		wushi_dragon_appear_debug();
	}

	void wushi_dragon_appear_debug() {
		cout << "It has a " << weapon_mode[weapon] << ",and it's morale is " << fixed << setprecision(2) << shiqi << endl;
	}
};

class wushi_ninja :public wushi {
private:
	int weapon_1, weapon_2;
public:
	wushi_ninja(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		weapon_1 = l % 3;
		weapon_2 = (l + 1) % 3;
		
		wushi_ninja_appear_debug();
	}

	void wushi_ninja_appear_debug() {
		cout << "It has a " << weapon_mode[weapon_1] << " and a " << weapon_mode[weapon_2] << endl;
	}
};

class wushi_iceman :public wushi {
private:
	int weapon;
public:
	wushi_iceman(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		weapon = l % 3;

		wushi_iceman_appear_debug();
	}

	void wushi_iceman_appear_debug() {
		cout << "It has a " << weapon_mode[weapon] << endl;
	}
};

class wushi_lion :public wushi {
private:
	int loyalty;
public:
	wushi_lion(int i, int j, int k, int m, int l) :wushi(i, j, k, m, l) {
		loyalty = (j == 0 ? red.HP_f() : blue.HP_f());

		wushi_lion_appear_debug();
	}

	void wushi_lion_appear_debug() {
		cout << "It's loyalty is " << loyalty << endl;
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



void wushi_create_sum(int i, int j, int k, int m, int l) {
	if (k == 0) {
		wushi_dragon w(i, j, k, m, l);
	}
	else if (k == 1) {
		wushi_ninja w(i, j, k, m, l);
	}
	else if (k == 2) {
		wushi_iceman w(i, j, k, m, l);
	}
	else if (k == 3) {
		wushi_lion w(i, j, k, m, l);
	}
	else if (k==4){
		wushi_wolf w(i, j, k, m, l);
	}
	else {
		cout << "ERROR #1" << endl;
	}
}





void game_init() {//ȫ����Ϸ��ʼ��
	time_total = 0;
	flag_create_wushi[0] = 0;
	flag_create_wushi[1] = 0;
}

int main() {
	int n;
	cin >> n;
	for (int mhx_tql = 0; mhx_tql < n; mhx_tql++) {
		cout << "Case:" << mhx_tql + 1 << endl;
		game_init();
		int m;
		cin >> m;
		cin >> wushi_HP_init[0];
		wushi_HP_min = wushi_HP_init[0];
		for (int i = 1; i < 5; i++) {
			cin >> wushi_HP_init[i];
			wushi_HP_min = min(wushi_HP_init[i], wushi_HP_min);
		}
		red.silingbu_init(m,0);
		blue.silingbu_init(m,1);
		while (flag_create_wushi[0]==0 || flag_create_wushi[1]==0) {
			if (flag_create_wushi[0] == 0) {
				red.silingbu_wushi_create();
			}
			if (flag_create_wushi[1] == 0) {
				blue.silingbu_wushi_create();
			}
			time_total++;
		};
	}
}
