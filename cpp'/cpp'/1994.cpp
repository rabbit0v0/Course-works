//
//  1994.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int map[505][505], n, m, head, tail;
bool visit[505][505];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
struct node{
    int x;
    int y;
    node(int a = -1, int b = -1){
        x = a;
        y = b;
    }
};
node l[500000];

void push(int x, int y){
    l[tail].x = x;
    l[tail++].y = y;
    visit[x][y] = 1;
}

void pop(){
    head++;
}

bool empty(){
    return (head == tail);
}

bool inside(int x, int y){
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void bfs(){
    while (!empty()){
        int x = l[head].x;
        int y = l[head].y;
        for (int i = 0; i < 4; ++i){
            if (inside(x + dx[i], y + dy[i]) && map[x + dx[i]][y + dy[i]] == 0 && !visit[x + dx[i]][y + dy[i]])
                push(x + dx[i],y + dy[i]);
        }
        pop();
    }
}
void read(int &x)
{
    char c = getchar(), b = 1;
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            b = -1;
    for (x = 0; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x*= b;
    
}

int main(){
    int country = 0;
    read(n);
    read(m);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j)
            read(map[i][j]);
    }
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            if (!visit[i][j] && map[i][j] == 0){
                push(i, j);
                bfs();
                country++;
            }
        }
    }
    printf("%d", country);
    return 0;
}