//
//  combo.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: combo
 LANG: C++
 */

#include <stdio.h>
#include <iostream>
using namespace std;
int N;
int right1[3], right2[3];
int flag[105];
int same1, same2, same3;

int main(){
    freopen("combo.in", "r", stdin);
    freopen("combo.out", "w", stdout);
    cin >> N;
    cin >> right1[0] >> right1[1] >> right1[2];
    cin >> right2[0] >> right2[1] >> right2[2];
    for (int i = right1[0] - 2; i <= right1[0] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        flag[k] = 1;
    }
    for (int i = right2[0] - 2; i <= right2[0] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        if (flag[k]) same1++;
    }
    for (int i = 1; i <= N; ++i){
        flag[i] = 0;
    }
    for (int i = right1[1] - 2; i <= right1[1] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        flag[k] = 1;
    }
    for (int i = right2[1] - 2; i <= right2[1] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        if (flag[k] == 1) same2++;
    }
    for (int i = 1; i <= N; ++i){
        flag[i] = 0;
    }
    for (int i = right1[2] - 2; i <= right1[2] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        flag[k] = 1;
    }
    for (int i = right2[2] - 2; i <= right2[2] + 2; ++i){
        int k = i;
        if (k <= 0)
            k += N;
        else if (k > N)
            k -= N;
        if (flag[k] == 1) same3++;
    }
    int biggest, res = 0;
    if (N >= 5){
        biggest = 250;
        res = biggest - same1 * same2 * same3;
    }
    else
        res = N * N * N;
    
    cout << res << '\n';
}
