#include<iostream>
#include<queue>
using namespace std;

int N, a[1000000], vis = 1, k;
int b[1000000][2];
bool flag;
void son(){
	for (int i = 1; i < N; ++i){
		int j = a[i];
		if (b[j][0] == 0){
			b[j][0] = i;
		}
		else
			b[j][1] = i;
	}
}

queue<int> Q;
void com(){
	Q.push (0);
	while (!Q.empty()){
		int now = Q.front();

		Q.pop();

		for (int i = 0; i < 2; ++i){
			if (b[now][i] != 0){
				Q.push(b[now][i]);
				vis++;
			}
			if (b[now][i] == 0){
				if (vis < N){
					flag = false;
					return;
				}
				if (vis == N){
					flag = true;
					return;
				}
			}
		}
	}
} 

int main(){
	cin >> N;
	for (int i = 1; i < N; ++i){
		cin >> a[i];
	}
	int d = 1;
	while (d < N){
		d = 2 * d;
		k++;
	}
	son();
	com();
	if (flag){
		cout << "true" << endl;
	}
	else
		cout << "false" << endl;
}