#include <iostream>
using namespace std;

int main(){
	int V, N;
	cin >> V >> N;
	int v[1005], w[1005], f[10005] = {0};
	for (int i = 0; i < N; ++i){
		cin >> v[i] >> w[i];
	}

	for (int i = 0; i < N; ++i){
		for (int rest = 0; rest <= V; ++rest){
			if (rest < v[i])
				continue;
			if (f[rest] < f[rest - v[i]] + w[i]){
				f[rest] = f[rest - v[i]] + w[i];
			}
		}
	}
	int c = 0;
	for (int i = 0; i <= V; ++i){
		if (f[i] > c){
			c = f[i];
		}
	}
	cout << c;
}