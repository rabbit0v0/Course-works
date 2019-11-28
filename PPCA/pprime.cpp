//
//  pprime.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/14.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: pprime
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
int a, b;
int pal[1000000], tot;
int pri[1000000], sum;

int main(){
    freopen("pprime.in", "r", stdin);
    freopen("pprime.out", "w", stdout);
    cin >> a >> b;
    for (int i = 1; i <= 9; i += 2){
        if (i == 5)
            continue;
        for (int j = 0; j <= 9; ++j){
            pal[tot++] = i * 100 + j * 10 + i;
        }
    }
    for (int i = 1; i <= 9; i += 2){
        if (i == 5)
            continue;
        for (int j = 0; j <= 9; ++j){
            for (int k = 0; k <= 9; ++k){
                pal[tot++] = i * 10000 + j * 1000 + k * 100 + j * 10 + i;
            }
        }
    }
    for (int i = 1; i <= 9; i += 2){
        if (i == 5)
            continue;
        for (int j = 0; j <= 9; ++j){
            for (int k = 0; k <= 9; ++k){
                for (int l = 0; l <= 9; ++l){
                    pal[tot++] = i * 1000000 + j * 100000 + k * 10000 + l * 1000 + k * 100 + j * 10 + i;
                }
            }
        }
    }
    pri[0] = 2, pri[1] = 3, pri[2] = 5, pri[3] = 7, pri[4] = 11;
    sum = 5;
    for (int i = 0; i < tot; ++i){
        bool flag = 1;
        for (int j = 2; j <= sqrt(pal[i]); ++j){
            if (pal[i] % j == 0)
                flag = 0;
        }
        if (flag)
            pri[sum++] = pal[i];
    }
    for (int i = 0; i < sum; ++i){
        if (pri[i] >= a && pri[i] <= b)
            cout << pri[i] << '\n';
    }
}
