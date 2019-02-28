#include<iostream>
using namespace std;

int main(){
	int N, a[100005], K, b, c, k = 0;
	cin >> N;
	for (int i = 0; i < N; ++i){
		cin >> a[i];
	}
	cin >> K;
	while (K--){
		cin >> b >> c;
		for (int i = 0; i < N; ++i){
			if (b * b - 4 * a[i] * c >= 0){
				k++;
			}
			else
				break;
		}
		cout << k << '\n';
		k = 0;
	}
}