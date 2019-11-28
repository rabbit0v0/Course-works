//
//  barn1.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: barn1
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int M, S, C;
bool stall[202];
int cal = 0;
int side = 0;
struct st{
    int beg, end, len;
    st(){
        beg = 0; end = 0; len = 0;
    }
};
st notin[202];
bool cmp(st a, st b){
    return a.len > b.len;
}

int main(){
    freopen("barn1.in", "r", stdin);
    freopen("barn1.out", "w", stdout);
    cin >> M >> S >> C;
    for (int i = 1; i <= C; ++i){
        int p;
        cin >> p;
        stall[p] = 1;
    }
    for (int i = 1; i <= S; ++i){
        if (!stall[i]){
            notin[cal].beg = i;
            int sum = 0;
            while (!stall[i] && i <= S)
                i++, sum++;
            notin[cal].end = i;
            if (notin[cal].beg == 1 || notin[cal].end == S + 1){
                side += sum;
                continue;
            }
            notin[cal++].len = sum;
        }
    }
    sort (notin, notin + cal, cmp);
    int res = 0;
    for (int i = 0; i < M - 1; ++i){
        res += notin[i].len;
    }
    res += side;
    cout << S - res << '\n';
}
