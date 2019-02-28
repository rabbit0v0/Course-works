//
//  2202.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/2/7.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int m, n, map[1005][1005] = {0}, visit[1005][1005] = {0}, go;
bool flag;

bool in(int x, int y){
    return (x > 0 && x <= n && y > 0 && y <= n);
}

void can(int x, int y){
    if (x == n && y == m)
        go = 1;
    bool now = flag;
    for (int i = 0; i < 4; ++i){
        int xx = x + dx[i], yy = y + dy[i];
        if (visit[xx][yy] == 0 && in(xx, yy)){
            visit[xx][yy] = 1;
            if (map[xx][yy] == 0)
                can(xx, yy);
            if (map[xx][yy] == 1 && flag){
                flag = false;
                can(xx, yy);
            }
        }
        flag = now;
    }
}

int main(){
    int k, t = 0;
    cin >> k;
    while (t++ < k){
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                visit[i][j] = 0;
            }
        }
        cin >> n >> m;
        flag = true;
        go = 0;
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                cin >> map[i][j];
            }
        }
        cout << go << '\n';
    }
}
