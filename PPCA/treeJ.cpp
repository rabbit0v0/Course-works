

//
//  treeJ.cpp
//  PPCA
//
//  Created by 施晓钰 on 04/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include<iostream>
using namespace std;
const int N = 105;

int p[N];
bool flag[N];

void make_set(void)
{
    for(int i = 0; i < 105; i++)
    {
        p[i] = i;
        flag[i] = 0;
    }
}

int find_set(int x){
    return p[x] == x ? x : (p[x] = find_set(p[x]));
}

void union_set(int x, int y){
    x = find_set(x);
    y = find_set(y);
    if(x == y) return;
    p[y] = x;
}

int main(){
    int x, y, t = 1, first;
    while(scanf("%d %d", &x, &y) != EOF){
        if(x == -1 && y == -1)
            break;
        if(x == 0 && y == 0){
            printf("Case %d is a tree.\n", t ++);
            continue;
        }
        make_set();
        flag[x] = flag[y] = 1;
        first = x;
        bool tree = 1;
        if(x == y) tree = 0;
        
        else union_set(x, y);
        while(scanf("%d %d", &x, &y) && x != 0){
            flag[x] = flag[y] = 1;
            if(find_set(x) == find_set(y))
                tree = 0;
            union_set(x, y);
        }
        for(int i = 1; i < 105; i ++)
            if(flag[i] && find_set(i) != find_set(first)) {
                tree = 0;
                break;
            }
        if(tree)
            printf("Case %d is a tree.\n", t ++);
        else
            printf("Case %d is not a tree.\n", t ++);
    }
    return 0;
}
