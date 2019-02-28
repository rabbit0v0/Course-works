#include <iostream>

using namespace std;

int main(){
	int n, a[10005], m, q1, q2;
	cin >> n;
	for (int i = 1; i <= n; ++i){
		cin >> a[i];
	}
	int sums[10005];
	sums[1] = a[1];
	for (int i = 2; i <= n; ++i){
		sums[i] = sums[i - 1] + a[i];
	}
	cin >> m;
	int k = 0;
	while (k < m){
		cin >> q1 >> q2;
		k++;
		int c = sums[q2] - sums[q1 - 1];
		cout << c << '\n';
	}
}