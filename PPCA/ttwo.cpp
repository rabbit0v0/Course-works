//
//  ttwo.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:ttwo
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;

const int dx[] = {-1,0,1,0}, dy[] = {0,-1,0,1};
char a[12][12];
struct mov{
    int x, y, d, cycle, state[11][11][4];
};
mov john, cow;

int main()
{
    int t = 0;
    freopen("ttwo.in", "r", stdin);
    freopen("ttwo.out", "w", stdout);
    for (int j = 1; j <= 10; ++j, getchar())
    {
        a[0][j] = '*'; a[11][j] = '*';
        a[j][0] = '*'; a[j][11] = '*';
        for (int i = 1; i <= 10; ++i){
            a[j][i] = getchar();
            if (a[j][i] == 'F') john.x = i, john.y = j, john.d = 1;
            else if (a[j][i] == 'C') cow.x = i, cow.y = j, cow.d = 1;
        }
    }
    do{
        if (!john.state[john.y][john.x][john.d])
            john.state[john.y][john.x][john.d] = t;
        else if (!john.cycle)
            john.cycle = t - john.state[john.y][john.x][john.d];
        if (!cow.state[cow.y][cow.x][cow.d])
            cow.state[cow.y][cow.x][cow.d] = t;
        else if (!cow.cycle)
            cow.cycle = t - cow.state[cow.y][cow.x][cow.d];
        ++t;
        if (a[john.y+dy[john.d]][john.x+dx[john.d]] == '*')
            john.d = (john.d + 1) % 4;
        else
            john.x += dx[john.d], john.y += dy[john.d];
        if (a[cow.y+dy[cow.d]][cow.x+dx[cow.d]] == '*')
            cow.d = (cow.d + 1) % 4;
        else
            cow.x += dx[cow.d], cow.y += dy[cow.d];
        if (john.x == cow.x && john.y == cow.y){
            cout << t << '\n';
            return 0;
        }
    }while (!john.cycle || !cow.cycle || t % john.cycle || t % cow.cycle);
    cout << 0 << '\n';
}
