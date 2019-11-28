//
//  race3.cpp
//  PPCA
//
//  Created by 施晓钰 on 24/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:race3
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
bool cross[55][55], visit[55], yes;
int N = 0, sum = 0, necessary[50], start, ending;
int gethere[55], res[50], tot;

void dfs(int x){
    if (visit[x])
        return;
    if (x == N){
        yes = 0;
        return;
    }
    visit[x] = 1;
    for (int i = 1; i <= N; ++i){
        if (cross[x][i])
            dfs(i);
    }
}

void searchit(int x, int e, int col){
    if (gethere[x] == col){
        yes = 0;
        return;
    }
    if (x == e || visit[x])
        return;
    gethere[x] = col + 1;
    visit[x] = 1;
    for (int i = 0; i <= N; ++i){
        if (cross[x][i])
            searchit(i, e, col);
    }
}

int main(){
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);
    while (cin){
        int x;
        cin >> x;
        if (x == -1)
            break;
        while (x != -2){
            cross[N][x] = 1;
            cin >> x;
        }
        N++;
    }
    N--;
    for (int i = 1; i < N; ++i){
        for (int j = 0; j <= N; ++j)
            visit[j] = 0;
        visit[i] = 1;
        yes = 1;
        dfs(0);
        if (yes)
            necessary[sum++] = i;
    }
    cout << sum;
    for (int i = 0; i < sum; ++i){
        cout << ' ' << necessary[i];
    }
    cout << '\n';
    
    for (int i = 0; i < sum; ++i){
        for (int j = 0; j <= N; ++j){
            visit[j] = 0;
            gethere[j] = 0;
        }
        yes = 1;
        searchit(0, necessary[i], 1);
        searchit(necessary[i], N, 2);
        if (yes)
            res[tot++] = necessary[i];
    }
    cout << tot;
    for (int i = 0; i < tot; ++i){
        cout << ' ' << res[i];
    }
    cout << '\n';
}
