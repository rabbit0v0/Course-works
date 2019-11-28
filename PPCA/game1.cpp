//
//  game1.cpp
//  PPCA
//
//  Created by 施晓钰 on 23/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:game1
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, num[101], sum[101][101], getsum[101][101];

int main(){
    freopen("game1.in","r",stdin);
    freopen("game1.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= N; ++i){
        cin >> num[i];
    }
    for (int i = 1; i <= N; ++i){
        sum[i][i] = num[i];
        getsum[i][i] = num[i];
        for (int j = 1; j < i; ++j){
            sum[j][i] = sum[j][i - 1] + num[i];
        }
    }
    for (int i = 1; i < N; ++i){
        for (int j = 1; j <= N - i; ++j){
            getsum[j][j + i] = sum[j][j + i] - min(getsum[j][j + i - 1], getsum[j + 1][j + i]);
        }
    }
    cout << getsum[1][N] << ' ' << sum[1][N] - getsum[1][N] << '\n';
}
