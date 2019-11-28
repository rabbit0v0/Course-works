
//
//  nocows.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:nocows
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, K;
int res[201][201], sum[201][201];

int main(){
    freopen("nocows.in","r",stdin);
    freopen("nocows.out","w",stdout);
    cin >> N >> K;
    res[1][1] = 1;
    sum[1][1] = 1;
    for (int i = 2; i <= K; i++){
        for (int j = 1; j <= N; j += 2){
            if (j >= 2 * i - 1){
                for (int m = 0; m < j; ++m){
                    res[i][j] += res[i - 1][m] * sum[i - 2][j - m - 1];
                    res[i][j] %= 9901;
                    res[i][j] += res[i - 1][j - m - 1] * sum[i - 2][m];
                    res[i][j] %= 9901;
                    res[i][j] += res[i - 1][m] * res[i - 1][j - m - 1];
                    res[i][j] %= 9901;
                }
            }
            sum[i][j] = res[i][j] + sum[i - 1][j];
        }
    }
    cout << res[K][N] << '\n';
}
