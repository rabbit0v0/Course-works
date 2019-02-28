#include <iostream>
using namespace std;

int n, x[105], y[105], u[105], m, L[105];

int visit[105];

void dfs(int p, int q){
	visit[p] = 1;
	if (p == q){
		return;
	}
	for (int i = 1; i < n; ++i){
		if (x[i] == p && visit[y[i]] == 0){
			L[y[i]] = L[x[i]] + u[i];
			dfs(y[i], q);
		}
		if (y[i] == p && visit[x[i]] == 0){
			L[x[i]] = L[y[i]] + u[i];
			dfs(x[i], q);
		}
	}
}

int main(){
	cin >> n;
	for (int i = 1; i < n; ++i){
		cin >> x[i] >> y[i] >> u[i];
	}
	cin >> m;
	int l = 0, q, p;
	while (l < m){
		cin >> p >> q;
		++l;
		for (int i = 0; i <= n; ++i){
			visit[i] = 0;
			L[i] = 0;
		}		
		dfs(p, q);
		cout << L[q] << '\n';
	}

}