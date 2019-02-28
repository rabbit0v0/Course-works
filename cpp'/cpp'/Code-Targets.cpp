#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
Add more functions as you need,
but DO NOT change the main function
or any given code.
*/

int maxCoins(vector<int>& nums) {
	// Create two virtual targets
	vector<int> B(1, 1);
	for (int i = 0; i < nums.size(); i++)
		B.push_back(nums[i]);
	B.push_back(1);
    int size_B = B.size();
    int coin[size_B][size_B];
    memset(coin, 0, sizeof(coin));
    for (int i = 1; i < size_B-1; ++i)
        coin[i][i] = B[i]*B[i+1]*B[i-1];
    for(int n = 1; n < size_B-2; ++n){
        for(int i = 1; i + n < size_B-1; ++i){
            for(int p = i; p <= i + n; ++p){//let p be the latest shot
                if (p == i){
                    coin[i][i+n] = max(coin[p+1][i+n]+B[p]*B[i-1]*B[i+n+1], coin[i][i+n]);
                    continue;
                }
                if (p == i+n){
                    coin[i][i+n] = max(coin[i][p-1]+B[p]*B[i-1]*B[i+n+1], coin[i][i+n]);
                    continue;
                }
                coin[i][i+n] = max(coin[i][p-1]+coin[p+1][i+n]+B[p]*B[i-1]*B[i+n+1], coin[i][i+n]);
            }
            //cout << i << ' ' << i+n << ' ' << coin[i][i+n] << '\n';
        }
    }
	/*
	Implement your algorithm here
	and return the maximum number
	of coins you can collect.
	*/
    return coin[1][B.size()-2];
}

int main() {
	int N;
	vector<int> nums;

	cin >> N;
	for (int tmp, i = 0; i < N; i++) {
		cin >> tmp;
		nums.push_back(tmp);
	}

	cout << maxCoins(nums) << endl;

	return 0;
}
