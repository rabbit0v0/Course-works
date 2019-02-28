#include <iostream>
using namespace std;

int main(){
	int n, ave = 0, step = 0;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; ++i){
		cin >> a[i];
	}
	for (int i = 0; i < n; ++i){
		ave += a[i];
	}
	ave = ave / n;

	for (int i = 0; i < n - 1; ++i){
		if (a[i] == ave) continue;
		a[i + 1] += a[i] - ave;
		step += 1;
	}
	cout << step;
	return 0;
}