//
//  ditch.cpp
//  PPCA
//
//  Created by 施晓钰 on 23/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:ditch
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int c[201][201], h[201], v[201], flow = 0;
int N, M, del;
bool getit;

void go(int w){
    if (w == M){
        flow += del;
        getit = 1;
        return;
    }
    int tmp = del, i, minh = M - 1;
    for (i = 1; i <= M; ++i){
        if (c[w][i] > 0){
            if (h[i] + 1 == h[w]){
                del = min(del, c[w][i]);
                go(i);
                if (h[1] >= M) return;
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
        if (v[h[w]] == 0) h[1] = N;
        h[w] = minh + 1;
        v[h[w]]++;
    }
}

int main(){
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    cin >> N >> M;
    for (int i = 1; i < N; ++i){
        int x, y, z;
        cin >> x >> y >> z;
        c[x][y] += z;
    }
    v[0] = M;
    while (h[1] < M){
        del = 2147483647;
        getit = 0;
        go(1);
    }
    cout << flow << '\n';
}
