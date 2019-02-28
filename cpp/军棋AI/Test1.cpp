#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int TOTALNUM = 25;
const int TOTALKIND = 12;
const int UPPER_RANGE_L = 11, UPPER_RANGE_R = 16;
const int LOWER_RANGE_L = 0, LOWER_RANGE_R = 5;
const int H = 17;
const int W = 5;
const int dx[8] = {-1, 1, 0, 0, 1, 1, -1, -1};
const int dy[8] = {0, 0, -1, 1, 1, -1, 1, -1};

int rounds = 0;
int id;
int map[H][W];

bool exist(int x, int y) {
    return (LOWER_RANGE_L <= x && x <= LOWER_RANGE_R && 0 <= y && y < W)
		|| (UPPER_RANGE_L <= x && x <= UPPER_RANGE_R && 0 <= y && y < W)
		|| ((x == 6 || x == 8 || x == 10) && (y == 0 || y == 2 || y == 4));
}

void change() {
    int x, y, xx, yy, col, kind;
    cin >> x >> y >> xx >> yy >> col >> kind;
	cerr << "Get updates:"  << endl;
	cerr << x << ' ' << y << ' ' << xx << ' ' << yy << ' ' << col << ' ' << kind << endl;
    int tar = col * TOTALKIND + kind;
    if (x == xx && y == yy) map[x][y] = tar;
    else {
        map[x][y] = -2;
        map[xx][yy] = tar;
    }
}

void show_init(int id)
{
	//give a initializing map here
	//this line : kind1 kind2 ... etc
	//Imagine that the chesses are listed from the bottom to the top, left to right
	//This is a stupid start:
	int opt[25] = {9, 11, 9, 7, 6, 7, 9, 8, 7, 3, 4, 5, 10, 5, 6, 3, 2, 10, 4, 1, 2, 6, 8, 8, 0};
	for (int i = 0; i < 25; ++i)
		cout << opt[i] << ' ';
	cout << endl;
}
void get_init()
{
	int arr0[25], arr1[25];
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr0[i];
	}
	for (int i = 0; i < 25; ++i)
	{
		cin >> arr1[i];
		arr1[i] += TOTALKIND;
	}
	map[0][0] = arr0[0];
	map[0][1] = arr0[1];
	map[0][2] = arr0[2];
	map[0][3] = arr0[3];
	map[0][4] = arr0[4];
	map[1][0] = arr0[5];
	map[1][1] = arr0[6];
	map[1][2] = arr0[7];
	map[1][3] = arr0[8];
	map[1][4] = arr0[9];
	map[2][0] = arr0[10];
	map[2][2] = arr0[11];
	map[2][4] = arr0[12];
	map[3][0] = arr0[13];
	map[3][1] = arr0[14];
	map[3][3] = arr0[15];
	map[3][4] = arr0[16];
	map[4][0] = arr0[17];
	map[4][2] = arr0[18];
	map[4][4] = arr0[19];
	map[5][0] = arr0[20];
	map[5][1] = arr0[21];
	map[5][2] = arr0[22];
	map[5][3] = arr0[23];
	map[5][4] = arr0[24];

	map[16][0] = arr1[4];
	map[16][1] = arr1[3];
	map[16][2] = arr1[2];
	map[16][3] = arr1[1];
	map[16][4] = arr1[0];
	map[15][0] = arr1[9];
	map[15][1] = arr1[8];
	map[15][2] = arr1[7];
	map[15][3] = arr1[6];
	map[15][4] = arr1[5];
	map[14][0] = arr1[12];
	map[14][2] = arr1[11];
	map[14][4] = arr1[10];
	map[13][0] = arr1[16];
	map[13][1] = arr1[15];
	map[13][3] = arr1[14];
	map[13][4] = arr1[13];
	map[12][0] = arr1[19];
	map[12][2] = arr1[18];
	map[12][4] = arr1[17];
	map[11][0] = arr1[24];
	map[11][1] = arr1[23];
	map[11][2] = arr1[22];
	map[11][3] = arr1[21];
	map[11][4] = arr1[20];
}

bool inside(int x, int y){
	return x >= 0 && x < 17 && y >= 0 && y < 5; 
}

int tmap[17][5] = {
	{1, 0, 1, 0, 1},
	{3, 3, 3, 3, 3},
	{3, 2, 1, 2, 3},
	{3, 1, 2, 1, 3},
	{3, 2, 1, 2, 3},
	{3, 3, 3, 3, 3},
	{3, 5, 3, 5, 3},
	{5, 5, 5, 5, 5},
	{3, 5, 3, 5, 3},
	{5, 5, 5, 5, 5},
	{3, 5, 3, 5, 3},
	{3, 3, 3, 3, 3},
	{3, 2, 1, 2, 3},
	{3, 1, 2, 1, 3},
	{3, 2, 1, 2, 3},
	{3, 3, 3, 3, 3},
	{1, 0, 1, 0, 1}
};
//一格格走，没判工兵,没判铁路。
int canmove(int x, int y, int k){
	if (tmap[x][y] == 0){
		return 0;
	}
	if (inside(x + dx[k], y + dy[k]) && tmap[x + dx[k]][y + dy[k]] == 5){
		if (exist(x, y) && exist(x + 2 * dx[k], y + 2 * dy[k])){
		if (k >= 0 && k < 4)
			return 2;
		else
			return 0;
		}
	}

	if (exist(x, y) && exist(x + dx[k], y + dy[k])){
		if (tmap[x][y] == 2 || tmap[x + dx[k]][y + dy[k]] == 2)
			return 1;
		else if (k >= 0 && k < 4 && tmap[x + dx[k]][y + dy[k]] != 0)
			return 1;
		else
			return 0;
	}	
	return 0;
}

struct decisions
{
	int x, y, xx, yy;
	decisions(){}
	decisions(int a, int b, int c, int d){
		x = a; y = b; xx = c; yy = d;
	}
};

decisions w[200];
int total = 0;

int visit[17][5] = {0};
//工兵能走的路径
void sold(int sx, int sy,int x, int y, int col){
	if (x != sx || y != sy){
		w[total] = decisions(sx, sy, x, y);
		total += 1;
	}
	visit[x][y] = 1;
	for (int i = 0; i < 4; ++i){
		int xx = x + dx[i]; int yy = y + dy[i];
		if (!inside(xx, yy))
			continue;
		if (tmap[xx][yy] == 5){
			xx += dx[i];
			yy += dy[i];
		}
		if (exist(xx, yy) && tmap[xx][yy] == 3 && visit[xx][yy] == 0){
			if (map[xx][yy] != -2){
				if (map[xx][yy] / 12 != col && map[xx][yy] % 12 >= 8){
					w[total] = decisions (sx, sy, xx, yy);
					++total;
				}
				continue;
			}
		sold(sx, sy, xx, yy, col);
		}
	}
}

//司令-0 军长-1 师长-2 旅长-3 团长-4 营长-5 连长-6 排长-7 工兵-8 地雷-9 炸弹-10 军棋-11
//会吃营里的子！！！
int caneat(int x, int y, int xx, int yy, int col){
	if (tmap[x][y] != 0 && (tmap[xx][yy] != 2 || tmap[xx][yy] == 2 && map[xx][yy] == -2)){
		//正常子不管工兵挖地雷和双方炸弹
		if (map[x][y] > -1 && map[x][y] < 9 && map[x][y] / 12 == col){
			if (map[xx][yy] == -2 || (map[xx][yy] / 12 == 1 - col && map[xx][yy] % 12 > map[x][y] % 12 && (map[xx][yy] < 9 || map[xx][yy] == 11))){
				return map[x][y];
			}
		}
		//我方工兵挖地雷
		if (map[x][y] / 12 == col && map[x][y] % 12 == 8 && map[xx][yy] / 12 == 1 - col && map[xx][yy] % 12 == 9){
			return map[x][y];
		}
		//我方炸弹
		if (map[x][y] / 12 == col && map[x][y] % 12 == 10){
			if (map[xx][yy] == -2 || map[xx][yy] / 12 == 1 - col)
				return -2;
		}
		//并
		if (map[x][y] / 12 == col && map[xx][yy] / 12 == 1 - col){
			if (map[x][y] % 12 == map[xx][yy] % 12)
				return -2;
		}
	}
	//不自杀
	else
		return -5;
}

int cal(int col){
	int c = 0;
	for (int i = 0; i < 17; ++i){
		for (int j = 0; j < 5; ++j){
			if (map[i][j] != -2 && map[i][j] / 12 == col){
				if (map[i][j] % 12 == 11)
					c += 100;
				if (map[i][j] % 12 < 8)
					c += 20 - (map[i][j] % 12) * 2;
				if (map[i][j] % 12 == 8)
					c += 10;
				if (map[i][j] % 12 == 10)
					c += 8;
			}
			if (map[i][j] != -2 && map[i][j] / 12 != col){
				if (map[i][j] % 12 == 11)
					c -= 100;
				if (map[i][j] % 12 < 8)
					c -= 20 - (map[i][j] % 12) * 2;
				if (map[i][j] % 12 == 8)
					c -= 15;
				if (map[i][j] % 12 == 10)
					c -= 8;
			}
		}
	}
	return c;
}

decisions all[3][200];
decisions ifind[3];
int DFS(int depth, int col){
	if (depth == 2){
		return cal(col);
	}
	int tol = 0;
	for (int i = 0; i < 17; ++i){
		for (int j = 0; j < 5; ++j){
			for (int k = 0; k < 8; ++k){
				if (map[i][j] % 12 != 8 || (map[i][j] == 8 && tmap[i][j] != 3)){
					int m = canmove(i, j, k);
					if (map[i][j] / 12 == col && canmove(i, j, k) != 0 && caneat(i, j, i + m * dx[k], j + m * dy[k],col) != -5){
						all[depth][tol] = decisions (i, j, i + m * dx[k], j + m * dy[k]);
						++tol;
					}
				}
				if (map[i][j] % 12 == 8 && tmap[i][j] == 3){
					if (map[i][j] / 12 == col){
						for (int c = 0; c < 17; ++c){
							for (int v = 0; v < 5; ++v){
								visit[c][v] = 0;
							}
						}
						sold(i, j, i, j, col);
						int l = 0;
						for (int o = 0; o < total + tol; ++o){
							if (caneat(w[o].x, w[o].y, w[o].xx, w[o].yy, col) != -5){
								all[depth][tol + l] = w[o];
								++l;
							}
						}
					}
				}
			}
		}
	}
	int bestscore = -1000, p, q;
	for (int i = 0; i < tol + total; ++i){
		for (int m = 0; m < 17; ++m){
			for (int n = 0; n < 5; ++n){
				if (m == all[depth][i].x && n == all[depth][i].y){
					p = map[m][n];
					map[m][n] = -2;
				}
				else if (m == all[depth][i].xx && n == all[depth][i].yy){
					q = map[m][n];
					map[m][n] = caneat(all[depth][i].x, all[depth][i].y, all[depth][i].xx, all[depth][i].yy, col);
				}
			}
		}
		int now = DFS(depth + 1, 1 - col);
		if (now > bestscore){
			bestscore = now;
			ifind[depth] = all[depth][i];
		}
		map[all[depth][i].x][all[depth][i].y] = p;
		map[all[depth][i].xx][all[depth][i].yy] = q;
	}
	return bestscore;
}

void make_decision(int &x, int &y, int &xx, int &yy) {
	DFS(0, id);
	x = ifind[0].x;
	y = ifind[0].y;
	xx = ifind[0].xx;
	yy = ifind[0].yy;
}

inline void end() {
    std::cout << "END\n" << std::flush;
}


int main(int argc, char** argv) {
    unsigned seed = time(0);
    if (argc == 2) {
        cerr << "Excited! Get given seed = " << argv[1] << endl;
        seed = 0;
        for (char *pc = argv[1]; *pc; ++pc)
            seed = seed * 10 + (*pc - '0');
    }
    srand(seed);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            map[i][j] = -2;
        }
    }
    string op;
    while (true) {
        cin >> op;
        if (op == "id") {
            cin >> id;
			cerr << id << endl;
            cout << "Sample AI" << endl;
            end();
		} else if (op == "refresh") {
			get_init();
        } else if (op == "init") {
			show_init(id);
			end();
		} else if (op == "message") {
            change();
        } else if (op == "action") {
            int x, y, xx, yy;
            make_decision(x, y, xx, yy);
			cerr << x << " " << y << " " << xx << " " << yy << endl;
            cout << x << " " << y << " " << xx << " " << yy << endl;
            end();
        }
    }
}