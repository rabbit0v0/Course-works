//
//  concom.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:concom
 LANG: C++
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int N, ctrl[101][101], wt[101];
bool flag[101], cont[101];

void dfs(int x){
    if (flag[x]) return;
    flag[x] = 1;
    for (int i = 1; i <= 100; ++i){
        wt[i] += ctrl[x][i];
        if (wt[i] > 50){
            cont[i] = 1;
            dfs(i);
        }
    }
}

int main(){
    freopen("concom.in","r",stdin);
    freopen("concom.out","w",stdout);
    cin >> N;
    for (int i = 1; i <= N; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        ctrl[a][b] += c;
    }
    for (int i = 1; i <= 100; ++i){
        memset(wt, 0, sizeof(wt));
        memset(flag, 0,  sizeof(flag));
        memset(cont, 0, sizeof(cont));
        dfs(i);
        for (int j = 1; j <= 100; ++j){
            if (cont[j] && i != j)
                cout << i << ' ' << j << '\n';
        }
    }
}
