#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
long long M, N, map[1000][1000], map0[1000][1000], xx, yy, l;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int visit[1000][1000];

struct w
{
	int x, y;
	w(int a, int b){
		x = a;
		y = b;
	}
};

bool inside(int x, int y){
	return x >= 0 && x < M && y >= 0 && y < N;
}

bool go(long long h){
	queue<w> Q;
	int x0, y0, l0 = l;
	Q.push(w(xx, yy));
	for (int i = 0; i < 500; ++i){
		for (int j = 0; j < 500; ++j){
			visit[i][j] = 0;
		}
	}
	visit[xx][yy] = 1;
	while (!Q.empty()){
		w now = Q.front();
		Q.pop();
		if (map0[now.x][now.y] == 1){
			l0--;
		}
		if (l0 == 0){
			return true;
		}
		for (int i = 0; i < 4; ++i){
			x0 = now.x + dx[i];
			y0 = now.y + dy[i];
			if (inside(x0, y0) && !visit[x0][y0] && abs(map[now.x][now.y] - map[x0][y0]) <= h){
				Q.push (w(x0, y0));
				visit[x0][y0] = 1;
			}
		}
	}
	return false;
}

int main(){
	long long m = 0, n = 0;
	cin >> M >> N;
	for (int i = 0; i < M; ++i){
		for (int j = 0; j < N; ++j){
			cin >> map[i][j];
			if (map[i][j] > m)
				m = map[i][j];
			if (map[i][j] < n)
				n = map[i][j];
		}
	}
	for (int i = 0; i < M; ++i){
		for (int j = 0; j < N; ++j){
			cin >> map0[i][j];
			if (map0[i][j] == 1){
				l++;
				xx = i;
				yy = j;
			}
		}
	}
	if (l == 0){
		cout << 0;
		return 0;
	}
	//cout<<go(0);
	long long maxh, minh = 0, midh;
	maxh = m - n;
	while (true){
		midh = (maxh + minh) / 2;
		//cout << midh;
		if (go(midh))
			maxh = midh;
		else 
			minh = midh + 1;
		if (maxh == minh)
			break;
	}
	cout << minh;
	return 0;
}