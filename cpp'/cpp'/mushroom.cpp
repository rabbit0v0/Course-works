//
//  mushroom.cpp
//  cpp'
//
//  Created by 施晓钰 on 2016/12/18.
//  Copyright © 2016年 施晓钰. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;

int t[1005], w[1005], q[1005];

int main(){
    int T, M;
    cin >> T >> M;
    for (int i = 0; i < M; ++i){
        cin >> t[i] >> w[i];
    }
    for (int i = 0; i < M; ++i){
        for (int k = T; k >= 0; --k){
            if (k < t[i])
                continue;
            q[k] = max(q[k], q[k - t[i]] + w[i]);
        }
    }
    cout << q[T];
    return 0;
}