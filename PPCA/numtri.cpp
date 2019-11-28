//
//  numtri.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/14.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: numtri
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int R;
int tri[1005][1005];
int sum[1005][1005];

bool inside(int x, int y){
    return x >= 0 && y >= 0 && x < R && y <= x;
}

int main(){
    freopen("numtri.in", "r", stdin);
    freopen("numtri.out", "w", stdout);
    cin >> R;
    for (int i = 0; i < R; ++i){
        for (int j = 0; j <= i; ++j){
            cin >> tri[i][j];
        }
    }
    sum[0][0] = tri[0][0];
    for (int i = 1; i < R; ++i){
        for (int j = 0; j <= i; ++j){
            if (j == 0)
                sum[i][j] = sum[i - 1][j] + tri[i][j];
            else
                sum[i][j] = tri[i][j] + max(sum[i - 1][j - 1], sum[i - 1][j]);
        }
    }
    int max = 0;
    for (int i = 0; i < R; ++i){
        if (sum[R - 1][i] > max)
            max = sum[R - 1][i];
    }
    cout << max << '\n';
}
