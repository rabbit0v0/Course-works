//
//  transform.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/11.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: transform
 LANG: C++
 */
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
int N;
char before[15][15];
char after[15][15];
char reflect[15][15];

bool one(int n, char p[15][15]){
    if (n == (N + 1) / 2)
        return 1;
    bool whether = 1;
    for (int i = n; i < N - n; ++i){
        if (p[n][i] != after[i][N - 1 - n])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[N - 1 - n][i] != after[i][n])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][N - 1 - n] != after[N - 1 - n][N - 1 - i])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][n] != after[n][N - 1 - i])
            whether = 0;
    }
    bool next = 1;
    if (whether) {
        next = one(n + 1, p);
        if (next) return 1;
    }
    return 0;
}

bool two(int n, char p[15][15]){
    if (n == (N + 1) / 2)
        return 1;
    bool whether = 1;
    for (int i = n; i < N - n; ++i){
        if (p[n][i] != after[N - 1 - n][N - 1 - i])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[N - 1 - n][i] != after[n][N - 1 - i])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][N - 1 - n] != after[N - 1 - i][N - 1 - n])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][n] != after[N - 1 - i][n])
            whether = 0;
    }
    bool next = 1;
    if (whether) {
        next = two(n + 1, p);
        if (next) return 1;
    }
    return 0;
}

bool three(int n, char p[15][15]){
    if (n == (N + 1) / 2)
        return 1;
    bool whether = 1;
    for (int i = n; i < N - n; ++i){
        if (p[n][i] != after[N - 1 - i][n])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[N - 1 - n][i] != after[N - 1 - i][N - 1 - n])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][N - 1 - n] != after[n][i])
            whether = 0;
    }
    for (int i = n; i < N - n; ++i){
        if (p[i][n] != after[N - 1 - n][i])
            whether = 0;
    }
    bool next = 1;
    if (whether) {
        next = three(n + 1, p);
        if (next) return 1;
    }
    return 0;
}

bool four(int n){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (after[i][j] != reflect[i][j])
                return 0;
        }
    }
    return 1;
}

bool sixsixsix(int n){
    if (n == (N - 1) / 2)
        return 1;
    bool whether = 1;
    for (int i = n; i < N - n; ++i){
        for (int j = n; j < N - n; ++j){
            if (after[i][j] != before[i][j]) whether = 0;
        }
    }
    bool next = 1;
    if (whether) {
        next = sixsixsix(n + 1);
        if (next) return 1;
    }
    return 0;
}

int how(){
    bool find;
    find = one(0, before);
    if (find) return 1;
    find = two(0, before);
    if (find) return 2;
    find = three(0, before);
    if (find) return 3;
    find = four(0);
    if (find) return 4;
    if (one(0, reflect) || two(0, reflect) || three(0, reflect))
        return 5;
    find = sixsixsix(0);
    if (find) return 6;
    return 7;
}

int main(){
    freopen("transform.in", "r", stdin);
    freopen("transform.out", "w", stdout);
    cin >> N;
    getchar();
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            before[i][j] = getchar();
        }
        getchar();
    }
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            after[i][j] = getchar();
        }
        getchar();
    }
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            reflect[i][j] = before[i][N - 1 - j];
        }
    }
    int res = how();
    cout << res << '\n';
}
