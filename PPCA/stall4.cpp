//
//  stall4.cpp
//  PPCA
//
//  Created by 施晓钰 on 23/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:stall4
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, M, c[500][500], v[500], h[500];
int flow, del;
bool getit;

void go(int w){
    if (w == N){
        flow += del;
        getit = 1;
        return;
    }
    int tmp = del,minh = N - 1, i;
    for (i = 1; i <= N; ++i){
        if (c[w][i] > 0){
            if (h[i] + 1 == h[w]){
                del = min(del, c[w][i]);
                go(i);
                if(h[1] >= N) return;
                if (getit) break;
                del = tmp;
            }
            minh = min(minh, h[i]);
        }
    }
    if (getit){
        c[w][i] -= del;
        c[i][w] += del;
    }
    else{
        v[h[w]]--;
        if (v[h[w]] == 0)
            h[1] = N;
        h[w] = minh + 1;
        v[h[w]]++;
    }
}

int main(){
    freopen("stall4.in","r",stdin);
    freopen("stall4.out","w",stdout);
    cin >> N >> M;
    for (int i = 1; i <= N; ++i){
        int tot;
        cin >> tot;
        for (int j = 1; j <= tot; ++j){
            int x;
            cin >> x;
            c[i + 1][N + 1 + x] = 1;
        }
    }
    for (int i = 1; i <= N; ++i) c[1][i + 1] = 1;
    for (int i = 1; i <= M; ++i) c[i + N + 1][N + M + 2] = 1;
    int all = N + M + 2;
    v[0] = all;
    while (h[1] < N){
        del = 2147483647;
        getit = 0;
        go(1);
    }
    cout << flow << '\n';
}
