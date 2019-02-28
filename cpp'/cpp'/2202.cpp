//
//  2202.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int k, n, m;
int themap[1001][1001], dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0 ,-1, 0}, visit[1001][1001];
bool pass;

bool inside(int x, int y){
    return (x > 0 && x <= n && y > 0 && y <= m);
}

class queue{
    int l[1000000];
    int head = 0, tail = 0;
public:
    bool empty(){
        return head == tail;
    }
    void push(int x){
        l[++tail] = x;
    }
    int pop(){
        if(empty())
            return -1;
        return l[++head];
    }
};

queue stu;

int dfs(int x, int y){
    visit[x][y] = 1;
    if (x == n && y == m){
        return 1;
    }
    if (themap[x][y] == 1)
        pass = 1;
    for (int i = 0; i < 4; ++i){
        int xx = x + dx[i];
        int yy = y + dy[i];
        if(inside(xx, yy) && !visit[xx][yy] && (themap[xx][yy] == 0 || !pass)){
            int res = dfs(xx, yy);
            if (res == 1)
                return 1;
        }
    }
    return 0;
}

int main(){
    scanf("%d", &k);
    for (int o = 0; o < k; ++o){
        pass = 0;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                visit[i][j] = 0;
                scanf("%d", &themap[i][j]);
            }
        }
        int p = dfs(1, 1);
        printf("%d\n", p);
    }
}
