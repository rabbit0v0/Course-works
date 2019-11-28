//
//  maze1.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:maze1
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;

int W, H, step[205][100];
char G [205][100];
bool visit[205][100];
int EXIT [2][2];
int DIRE [4][2] = {1,0, -1,0, 0,1, 0, -1};

void DFS(int st, int i, int j){
    visit[i][j] = 1;
    step[i][j] = st;
    int x, y;
    for (int m = 0; m < 4; ++m){
        x = i + DIRE[m][0];
        y = j + DIRE[m][1];
        if (G[x][y] == 'c' && (!visit[x][y] || step[x][y] > st + 1))
            DFS(st + 1, x, y);
    }
}

int main(){
//    freopen("maze1.in", "r", stdin);
//    freopen("maze1.out", "w", stdout);
//    for (int i = 0; i < 205; ++i){
//        for (int j = 0; j < 100l; ++j){
//            step[i][j] = 10000000;
//        }
//    }
    cin >> W >> H;
    W = W * 2 + 1;
    H = H * 2 + 1;
    char newl[W + 1];
    cin.getline(newl, 1);
    for (int i = 0 ; i < H ; i ++){
        cin.getline(newl, W + 1);
        for (int j = 0 ; j < W ; ++j){
            if (newl[j] == ' ')
                G[i][j] = 'c';
            if ((i == 0 || i == H - 1 || j == 0 || j == W - 1) && G [i][j] == 'c'){
                if (EXIT [0][0] || EXIT [0][1]){
                    EXIT [1][0] = i ;
                    EXIT [1][1] = j ; 
                }
                else{
                    EXIT [0][0] = i ;
                    EXIT [0][1] = j ; 
                }
            }
        }
    }
    DFS(1, EXIT[0][0], EXIT[0][1]);
//    for (int i = 0; i < 205; ++i){
//        for (int j = 0; j < 100; ++j){
//            visit[i][j] = 0;
//        }
//    }
    int max = 0;
    DFS(1, EXIT[1][0], EXIT[1][1]);
    for (int i = 1; i < H; i += 2){
        for (int j = 1; j < W; j += 2){
            if (step[i][j] > max)
                max = step[i][j];
        }
    }
    cout << max / 2 << '\n';
}

