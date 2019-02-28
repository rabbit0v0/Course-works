#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(){
	char a[205], b[205];
	int a1[205] = {0}, b1[205] = {0}, c[205] = {0};
	int k = 0;

	scanf ("%s%s", a, b);
	int L1 = strlen(a);
	int L2 = strlen(b);		

	for (int i = 0; i < L1; ++i){
		if (i == L1 - 3) continue;
		a1[L1 - i - 1] = a[i] - 48;
	}
	for (int i = 0; i < L2; ++i){
		if (i == L2 - 3) continue;
		b1[L2 - i - 1] = b[i] - 48;
	}

	for (int i = 0; i < max(L1, L2); ++i){
		if (i == 2) continue;
		c[i] += a1[i] + b1[i];
		if (i != 1){
			if (c[i] >= 10){
				c[i + 1] += 1;
			}
		}
		if (i == 1){
			if (c[i] >= 10){
				c[i + 2] += 1;
			}
		}
		c[i] = c[i] % 10;
	}

	for (int i = max(L1, L2); i > 0; --i){
		if (c[i] != 0){
			k = i;
			break;
		}
	}

	for (int i = k; i > 2; --i){
		cout << c[i];
	}
	cout << '.' << c[1] << c[0];

	return 0;
}
