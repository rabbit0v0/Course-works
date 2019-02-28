#include <iostream>
#include <cmath>
using namespace std;

bool prime(int n){
	bool flag = true;
	for (int i = 2; i <= sqrt(n); ++i){
		if (n % i == 0){
			flag = false;
			break;
		}
	}
	return flag;
}

int main(){
	int N, k1, k2;
	cin >> N;

	if (prime(N)){
		cout << 0;
	}
	else {
		for (int i = N - 1; i > 1; --i){
			if (prime(i)){
				k1 = i;
				break;
			}
		}
		for (int i = N + 1; true; ++i){
			if (prime(i)){
				k2 = i;
				break;
			}
		}
		cout << k2 - k1;
	}
	return 0;
}
