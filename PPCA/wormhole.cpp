//
//  wormhole.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: wormhole
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int N, sum, beginning;
struct wormhole{
    long long x, y;
    wormhole(){
        x = 0; y = 0;
    }
};
wormhole hole[15];
int inpair[15];
bool visit[15];

bool cmp(wormhole a, wormhole b){
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

bool go(int x, bool getin){
    if (x == beginning && visit[x] && !getin)
        return 1;
    visit[x] = 1;
    if (!getin){
        if (hole[x].y == hole[x + 1].y)
            return go(x + 1, 1);
        else
            return 0;
    }
    else
        return go(inpair[x], 0);
    return 0;
}

bool circle(){
    for (int i = 1; i <= N; ++i){
        for (int j = 0; j <= N; ++j)
            visit[j] = 0;
        beginning = i;
        if (go(i, 0))
            return 1;
    }
    return 0;
}

void pairit(int x){
    if (x == N + 1){
        if (circle())
            sum++;
        return;
    }
    if (inpair[x] == 0){
        for (int i = x + 1; i <= N; ++i){
            if (inpair[i] == 0){
                inpair[x] = i;
                inpair[i] = x;
                pairit(x + 1);
                inpair[x] = 0;
                inpair[i] = 0;
            }
        }
    }
    else
        pairit(x + 1);
}

int main(){
    freopen("wormhole.in", "r", stdin);
    freopen("wormhole.out", "w", stdout);
    cin >> N;
    for (int i = 1; i <= N; ++i){
        cin >> hole[i].x >> hole[i].y;
    }
    sort (hole + 1, hole + N + 1, cmp);
    pairit(1);
    cout << sum << '\n';
}
