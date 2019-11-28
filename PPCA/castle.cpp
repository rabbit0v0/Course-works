//
//  castle.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/14.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: castle
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;
int M, N;
int wall[55][55], sizeofnum[2500];
struct wal{
    int number;
    bool e, w, n, s;
    wal(){
        number = 0;
        e = 0, w = 0, n = 0, s = 0;
    }
};
wal room[55][55];
map<int, wal> castle;

bool inside (int x, int y){
    return x > 0 && x <= N && y > 0 && y <= M;
}

void dfs(int num, int x, int y){
    room[x][y].number = num;
    sizeofnum[num]++;
    if (inside(x - 1, y) && !room[x][y].n && !room[x - 1][y].number)
        dfs(num, x - 1, y);
    if (inside(x + 1, y) && !room[x][y].s && !room[x + 1][y].number)
        dfs(num, x + 1, y);
    if (inside(x, y - 1) && !room[x][y].w && !room[x][y - 1].number)
        dfs(num, x, y - 1);
    if (inside(x, y + 1) && !room[x][y].e && !room[x][y + 1].number)
        dfs(num, x, y + 1);
}

int main(){
    freopen("castle.in","r",stdin);
    freopen("castle.out","w",stdout);
    wal tmp;
    int tot = 0;
    for (int i = 0; i < 16; ++i){
        int k = i;
        tmp.e = 0, tmp.w = 0, tmp.n = 0, tmp.s = 0;
        if (k >= 8){
            tmp.s = 1;
            k -= 8;
        }
        if (k >= 4){
            tmp.e = 1;
            k -= 4;
        }
        if (k >= 2){
            tmp.n = 1;
            k -= 2;
        }
        if (k >= 1){
            tmp.w = 1;
        }
        castle[i] = tmp;
    }
    cin >> M >> N;
    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= M; ++j){
            cin >> wall[i][j];
            room[i][j] = castle[wall[i][j]];
        }
    }
    int maxsize = 0;
    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= M; ++j){
            if (!room[i][j].number){
                dfs(++tot, i, j);
            }
            if (sizeofnum[tot] > maxsize)
                maxsize = sizeofnum[tot];
        }
    }
    cout << tot << '\n' << maxsize << '\n';
    int maxtwo = 0, xx = 0, yy = 0;
    char dire = '0';
    for (int i = 1; i <= N; ++i){
        for (int j = M - 1; j > 0; --j){
            if (room[i][j].number != room[i][j + 1].number){
                if (sizeofnum[room[i][j].number] + sizeofnum[room[i][j + 1].number] >= maxtwo){
                    maxtwo = sizeofnum[room[i][j].number] + sizeofnum[room[i][j + 1].number];
                    xx = i, yy = j;
                    dire = 'E';
                }
            }
        }
    }
    for (int i = 1; i < N; ++i){
        for (int j = M; j > 0; --j){
            if (room[i][j].number != room[i + 1][j].number){
                if (sizeofnum[room[i][j].number] + sizeofnum[room[i + 1][j].number] == maxtwo){
                    if (j < yy || (j == yy && (i + 1) >= xx)){
                        maxtwo = sizeofnum[room[i][j].number] + sizeofnum[room[i + 1][j].number];
                        xx = i + 1, yy = j;
                        dire = 'N';
                    }
                }
                else if (sizeofnum[room[i][j].number] + sizeofnum[room[i + 1][j].number] > maxtwo){
                    maxtwo = sizeofnum[room[i][j].number] + sizeofnum[room[i + 1][j].number];
                    xx = i + 1, yy = j;
                    dire = 'N';
                }
            }
        }
    }
    cout << maxtwo << '\n' << xx << ' ' << yy << ' ' << dire << '\n';
}
