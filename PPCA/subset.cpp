//
//  subset.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:subset
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
int N, sumofn;
long long tmp[10000];

int main(){
    freopen("subset.in","r",stdin);
    freopen("subset.out","w",stdout);
    cin >> N;
    sumofn = (1 + N) * N / 2;
    if (sumofn % 2){
        cout << '0' << '\n';
        return 0;
    }
    tmp[0] = 1;
    for (int i = 1; i <= N; ++i){
        for (int j = (N + 1) * N / 4; j >= i; j--){
            tmp[j] += tmp[j - i];
        }
    }
    cout << tmp[(N + 1) * N / 4] / 2 << '\n';
}
