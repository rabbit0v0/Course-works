//
//  preface.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/15.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:preface
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
int N;
int len, res[7];
int one[10][7], two[10][7], three[10][7], four[10][7];
string k[7] = { "I ", "V ", "X ", "L ", "C ", "D ", "M "};

int main(){
    freopen("preface.in","r",stdin);
    freopen("preface.out","w",stdout);
    cin >> N;
    one[1][0] = 1;
    one[6][0] = 1;
    one[2][0] = 2;
    one[7][0] = 2;
    one[3][0] = 3;
    one[8][0] = 3;
    one[4][0] = 1;
    one[9][0] = 1;
    one[9][2] = 1;
    for (int i = 4; i < 9; ++i)
        one[i][1] = 1;
    two[1][2] = 1;
    two[6][2] = 1;
    two[2][2] = 2;
    two[7][2] = 2;
    two[3][2] = 3;
    two[8][2] = 3;
    two[4][2] = 1;
    two[9][2] = 1;
    two[9][4] = 1;
    for (int i = 4; i < 9; ++i)
        two[i][3] = 1;
    three[1][4] = 1;
    three[6][4] = 1;
    three[2][4] = 2;
    three[7][4] = 2;
    three[3][4] = 3;
    three[8][4] = 3;
    three[4][4] = 1;
    three[9][4] = 1;
    three[9][6] = 1;
    for (int i = 4; i < 9; ++i)
        three[i][5] = 1;
    four[1][6] = 1;
    four[2][6] = 2;
    four[3][6] = 3;
    for (int i = 1; i <= N; ++i){
        int n = i;
        if (n / 1000){
            int tmp = n / 1000;
            for (int i = 0; i < 7; ++i)
                res[i] += four[tmp][i];
        }
        n %= 1000;
        if (n / 100){
            int tmp = n / 100;
            for (int i = 0; i < 7; ++i)
                res[i] += three[tmp][i];
        }
        n %= 100;
        if (n / 10){
            int tmp = n / 10;
            for (int i = 0; i < 7; ++i)
                res[i] += two[tmp][i];
        }
        n %= 10;
        if (n){
            int tmp = n / 1;
            for (int i = 0; i < 7; ++i)
                res[i] += one[tmp][i];
        }
    }
    for (int i = 0; i < 7; ++i){
        if (res[i])
            cout << k[i] << res[i] << '\n';
    }
}
