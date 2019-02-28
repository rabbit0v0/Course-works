//
//  回文串.cpp
//  cpp'
//
//  Created by 施晓钰 on 2016/12/18.
//  Copyright © 2016年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    int N;
    cin >> N;
    int p[1005];
    p[1] = 1;
    for (int i = 2; i <= N; ++i){
        for (int j = 1; j <= i / 2; ++j){
            p[i] += p[j];
            p[i] = p[i] % 1000000007;
        }
        p[i]++;
        p[i] = p[i] % 1000000007;
    }
    cout << p[N];
    return 0;
}
