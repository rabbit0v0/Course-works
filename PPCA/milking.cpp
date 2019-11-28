//
//  milking.cpp
//  PPCA
//
//  Created by 施晓钰 on 02/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
int K, C, M;
int themap[300][300], been[300][20];
bool visit[300], connect[300][300];

void build(int x){
    memset(connect, 0, sizeof(connect));
    for (int i = K + 1; i <= K + C; ++i)
        for (int j = 1; j <= K; ++j)
            if (themap[i][j] <= x)
                connect[i - K][j] = 1;
}

bool DFS(int x){
    for (int i = 1; i <= K; ++i){
        if (connect[x][i] && !visit[i]){
            visit[i] = 1;
            if (been[i][0] < M){
                been[i][++been[i][0]] = x;
                return 1;
            }
            for (int j = 1; j <= M; ++j){
                if (DFS(been[i][j])){
                    been[i][j] = x;
                    return 1;
                }
            }
        }
    }
    return 0;
}

bool maxm(){
    memset(been, 0, sizeof(been));
    for (int i = 1; i <= C; ++i){
        memset(visit, 0, sizeof(visit));
        if (!DFS(i))
            return 0;
    }
    return 1;
}

void bi(int h, int l){
    if (h <= l){
        cout << l << '\n';
        return;
    }
    int mid = (l + h) / 2;
    build(mid);
    if (maxm())
        bi(mid, l);
    else
        bi(h, mid + 1);
}

int main(){
    cin >> K >> C >> M;
    for (int i = 1; i <= K + C; ++i)
        for (int j = 1; j <= K + C; ++j){
            cin >> themap[i][j];
            if (i != j && themap[i][j] == 0)
                themap[i][j] = 9999999;
        }
    for (int k = 1; k <= K + C; ++k)
        for (int i = 1; i <= K + C; ++i)
            for (int j = 1; j <= K + C; ++j)
                if (themap[i][k] + themap[k][j] < themap[i][j])
                    themap[i][j] = themap[i][k] + themap[k][j];
    bi(200 * (K + C), 0);
}
