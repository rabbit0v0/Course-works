#include <iostream>
using namespace std;

int a[6][6], b[4], visit[6][6];
int sit, cost, c;
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

bool exist(int x, int y){
	return (x > -1 && x < 6 && y > -1 && y < 6);
}

void dfs(int a1, int a2, int b1, int b2, int sit){
	if (a1 == b1 && a2 == b2){
		if (c > cost) c = cost;
		return; 
	}
	for (int i = 0; i < 4; ++i){
		if (exist(a1 + dx[i],a2 + dy[i]) && visit[a1 + dx[i]][a2 + dy[i]] == 0){
			int pre = sit, precost = cost;
			cost += sit * a[a1 + dx[i]][a2 + dy[i]];
			sit = sit * a[a1 + dx[i]][a2 + dy[i]] % 4 + 1;
			visit[a1 + dx[i]][a2 + dy[i]] = 1;
			dfs (a1 + dx[i], a2 + dy[i], b1, b2, sit);
			cost = precost, sit = pre;
			visit[a1 + dx[i]][a2 + dy[i]] = 0;
		}
	}
}

int main(){
	int n, m = 0;
	cin >> n;
	while (m < n){
		for (int i = 0; i < 6; ++i){
			for (int j = 0; j < 6; ++j){
				cin >> a[i][j];
			}
		}
		for (int i = 0; i < 4; ++i){
			cin >> b[i];
		}
		m += 1;
		c = 1000000;
		dfs(b[0], b[1], b[2], b[3], 1);
		cout << c;
	}
	return 0;

}