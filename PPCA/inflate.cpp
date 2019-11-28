//
//  inflate.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/17.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:inflate
 LANG: C++
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
struct kind{
    int score, minutes;
};
kind text[10001];
int M, N;
int tot[10001];

int main(){
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);
    cin >> M >> N;
    for (int i = 0; i < N; ++i){
        cin >> text[i].score >> text[i].minutes;
    }
    for (int i = 0; i < N; ++i){
        for (int lefttime = 0; lefttime <= M; ++lefttime){
            if (lefttime >= text[i].minutes){
                tot[lefttime] = max(tot[lefttime], tot[lefttime - text[i].minutes] + text[i].score);
            }
        }
    }
    cout << tot[M] << '\n';
}
