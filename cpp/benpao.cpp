#include <iostream>
using namespace std;

int L, M, N;
int D[50005] = {0};

int cal(int x){
	int del = 0, l = 0;
	for (int i = 1; i <= N + 1; ++i){
		if (D[i] - D[i - 1] + l < x){
			l += D[i] - D[i - 1];
			del++;
		}
		else if (D[i] - D[i - 1] + l >= x){
			l = 0;
		}
	}
	return del;
}

int half(int min, int max){
	if (min == max - 1){
		if (cal(max) <= M)
			return max;
		else
			return min;
	}
	if (min == max)
		return min;
	int mid = (min + max) / 2;
	if (cal(mid) <= M){
		return half(mid, max);
	}
	else{
		return half(min, mid - 1);
	}

}

int main(){
	cin >> L >> N >> M;
	for (int i = 1; i <= N; ++i){
		cin >> D[i];
	}
	D[N + 1] = L;

	cout << half(0, L);
}