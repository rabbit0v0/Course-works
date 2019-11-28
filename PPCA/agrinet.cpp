//
//  agrinet.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/17.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:agrinet
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, road[101][101], sum;
bool selected[101];

int main(){
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            cin >> road[i][j];
        }
    }
    selected[0] = 1;
    for (int k = 1; k < N; ++k){
        int mini = 100001, thenext = 0;;
        for (int i = 0; i < N; ++i){
            for (int j = 0; j < N; ++j){
                if (selected[i] && !selected[j]){
                    if (road[i][j] < mini){
                        thenext = j;
                        mini = road[i][j];
                    }
                }
            }
        }
        selected[thenext] = 1;
        sum += mini;
    }
    cout << sum << '\n';
}

