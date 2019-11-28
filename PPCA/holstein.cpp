//
//  holstein.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/15.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: holstein
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int V, Vt[26], G, Gs[20][26];
int temp[26], res = 50, R[20];

void dfs(int x, int sum){
    for (int i = x; i < G && sum < res; ++i){
        bool flag = 1;
        for (int j = 0; j < V; ++j){
            temp[j] += Gs[i][j];
            if (temp[j] < Vt[j])
                flag = 0;
        }
        if (flag){
            res = sum;
            R[sum - 1] = i + 1;
            for (int j = 0; j < V; ++j){
                temp[j] -= Gs[i][j];
            }
            return;
        }
        else{
            int now = R[sum];
            dfs(i + 1, sum + 1);
            if (now != R[sum])
                R[sum - 1] = i + 1;
        }
        for (int j = 0; j < V; ++j){
            temp[j] -= Gs[i][j];
        }
    }
}

int main(){
    freopen("holstein.in","r",stdin);
    freopen("holstein.out","w",stdout);
    cin >> V;
    for (int i = 0; i < V; ++i)
        cin >> Vt[i];
    cin >> G;
    for (int i = 0; i < G; ++i){
        for (int j = 0; j < V; ++j){
            cin >> Gs[i][j];
        }
    }
    dfs(0, 1);
    cout << res << ' ';
    for (int i = 0; i < res - 1; ++i){
        cout << R[i] << ' ';
    }
    cout << R[res - 1] << '\n';
}
