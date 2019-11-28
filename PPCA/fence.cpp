//
//  fence.cpp
//  PPCA
//
//  Created by 施晓钰 on 20/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:fence
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <stack>
#include <queue>
using namespace std;
int F;
priority_queue<int, vector<int>, greater<int> > u[501];
int nodes[501][501], start, ending;
stack<int> res;

void road(int x){
    while (!u[x].empty()){
        int go = u[x].top();
        u[x].pop();
        if (nodes[x][go]){
            nodes[x][go]--;
            nodes[go][x]--;
            road(go);
            res.push(go);
        }
    }
}

int main(){
    freopen("fence.in","r",stdin);
    freopen("fence.out","w",stdout);
    cin >> F;
    for (int i = 0; i < F; ++i){
        int v1, v2;
        cin >> v1 >> v2;
        u[v1].push(v2);
        u[v2].push(v1);
        nodes[v1][v2]++;
        nodes[v2][v1]++;
    }
    for (int i = 0; i < 500; ++i){
        if (nodes[i] && ending == 0)
            ending = i;
        if (u[i].size() % 2 && start == 0)
            start = i;
        if (u[i].size() % 2 && start)
            ending = i;
    }
    if (start == 0)
        start = ending;
    road(start);
    res.push(start);
    while (!res.empty()){
        cout << res.top() << '\n';
        res.pop();
    }
    
}
