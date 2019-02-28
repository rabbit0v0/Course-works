//
//  1046.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/27.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int n, p, q, root, t;
int node[100005][2], len[100005], fir[100005], red[100005];

int findroot(){
    for (int i = 1; i <= n; ++i){
        bool find = 1;
        for (int j = 1; j <= n; ++j){
            if (node[j][1] == i || node[j][0] == i){
                find = 0;
                break;
            }
        }
        if (find)
            return i;
    }
    return -1;
}

void dfs(int b){
    if (node[b][0] != 0){
        dfs(node[b][0]);
        len[b] += len[node[b][0]];
    }
    t++;
    fir[b] = t;
    len[b]++;
    if (node[b][0] != 0 && fir[node[b][0]] < t){
        fir[b] = fir[node[b][0]];
    }
    if (node[b][1] != 0){
        dfs(node[b][1]);
        len[b] += len[node[b][1]];
    }
}

int main(){
    scanf("%d%d%d", &n, &p, &q);
    for (int i = 0; i < n; ++i){
        int x, l, r;
        scanf("%d%d%d", &x, &l, &r);
        node[x][0] = l;
        node[x][1] = r;
    }
    
    root = findroot();
    dfs(root);
    
    for (int i = 0; i < p; ++i){
        int t, x, no;
        scanf("%d%d", &t, &x);
        no = x % len[t] + 1;
        red[fir[t] + no - 1] = 1;
    }
    
    for (int i = 0; i < q; ++i){
        int w, c = 0;
        scanf("%d", &w);
        for (int j = fir[w]; j < fir[w] + len[w]; ++j){
            if (red[j] == 1)
                c++;
        }
        printf("%d\n", c);
    }
    
}
