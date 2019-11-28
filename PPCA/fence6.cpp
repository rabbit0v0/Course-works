//
//  fence6.cpp
//  PPCA
//
//  Created by 施晓钰 on 24/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:fence6
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N, minlen = 2147483647;
struct node{
    int len, left, right;
    int l[101], r[101];
};
node fence[101];
int visit[101];

void dfs(int x0, int x, int pre, int nowlen){
    if (visit[x]++)
        return;
    if (nowlen > minlen)
        return;
    nowlen += fence[x].len;
    bool flag = 0;
    for (int i = 1; i <= fence[x].left; ++i){
        if (fence[x].l[i] == pre){
            flag = 1;
            break;
        }
    }
    if (flag){
        if (x == x0)
            return;
        for (int i = 1; i <= fence[x].right; ++i){
            dfs(x0, fence[x].r[i], x, nowlen);
            visit[fence[x].r[i]]--;
        }
    }
    else{
        if (x == x0){
            if (nowlen < minlen)
                minlen = nowlen;
            return;
        }
        for (int i = 1; i <= fence[x].left; ++i){
            dfs(x0, fence[x].l[i], x, nowlen);
            visit[fence[x].l[i]]--;
        }
    }
}

int main(){
    freopen("fence6.in", "r", stdin);
    freopen("fence6.out", "w", stdout);
    cin >> N;
    for (int i = 1; i <= N; ++i){
        int s;
        cin >> s;
        cin >> fence[s].len >> fence[s].left >> fence[s].right;
        for (int j = 1; j <= fence[s].left; ++j){
            cin >> fence[s].l[j];
        }
        for (int j = 1; j <= fence[s].right; ++j){
            cin >> fence[s].r[j];
        }
    }
    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= fence[i].left; ++i){
            for (int k = 0; k <= 100; ++k)
                visit[k] = 0;
            dfs(i, fence[i].l[j], i, 0);
        }
    }
    cout << minlen << '\n';
}
