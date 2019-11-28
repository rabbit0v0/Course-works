//
//  hamming.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/14.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: hamming
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, B, D;
long res[10000], sum = 1;

bool check(long x, long y){
    int count = 0;
    for (int i = 0; i < B; ++i){
        if (((x >> i) & 1 ) != ((y >> i) & 1))
            count++;
        if (count >= D)
            return 1;
    }
    return 0;
}

int main(){
        freopen("hamming.in","r",stdin);
        freopen("hamming.out","w",stdout);
    cin >> N >> B >> D;
    for (long i = 1; i < (1 << B); ++i){
        if (sum > N)
            break;
        bool get = 1;
        for (long j = 0; j < sum; ++j){
            if (!check(res[j], i)){
                get = 0;
                break;
            }
        }
        if (!get) continue;
        res[sum++] = i;
    }
    for (int i = 0; i < N - 1; ++i)
        cout << res[i] << ( ((i + 1) % 10 == 0)?"\n":" ");
    cout << res[N - 1] << '\n';
}
