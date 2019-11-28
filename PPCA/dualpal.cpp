//
//  dualpal.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: dualpal
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, S, sum;
int s[20];

int main(){
    freopen("dualpal.in", "r", stdin);
    freopen("dualpal.out", "w", stdout);
    cin >> N >> S;
    int now = S;
    while (sum < N){
        now++;
        int cal = 9;
        for (int i = 2; i <= 10; ++i){
            int tmp = now, amo = 0;
            int tem[100] = {0};
            while (tmp != 0){
                tem[++amo] = tmp % i;
                tmp = tmp / i;
            }
            for (int j = 1; j <= amo / 2; ++j){
                if (tem[j] != tem[amo - j + 1]){
                    cal--;
                    break;
                }
            }
        }
        if (cal > 1){
            s[++sum] = now;
        }
    }
    for (int i = 1; i <= N; ++i){
        cout << s[i] << '\n';
    }
}
