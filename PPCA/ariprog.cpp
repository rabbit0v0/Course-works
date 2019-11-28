//
//  ariprog.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/13.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: ariprog
 LANG: C++
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int M, N;
int bis[70000], tot, sum;
bool exist[126000];
struct two{
    int distance, begin;
    two(){
        distance = 0; begin = 0;
    }
};
two res[10001];

bool cmp(two a, two b){
    if (a.distance == b.distance)
        return a.begin < b.begin;
    return a.distance < b.distance;
}

int main(){
    freopen("ariprog.in","r",stdin);
    freopen("ariprog.out","w",stdout);
    cin >> N >> M;
    for (int i = 0; i <= M; ++i){
        for (int j = 0; j <= M; ++j){
            int tem = i * i + j * j;
            if (!exist[tem]){
                bis[tot++] = tem;
                exist[tem] = 1;
            }
        }
    }
    sort (bis, bis + tot);
    int dis = 1;
    int beg = 0;
    int len = 0;
    while (beg < tot - 2){
        int now = 1;
        dis = bis[beg + now] - bis[beg];
        while ((N - 1) * dis + bis[beg] <= bis[tot - 1]){
            len = 2;
            while (exist[bis[beg] + len * dis]){
                len++;
                if (len == N){
                    res[sum].distance = dis;
                    res[sum++].begin = bis[beg];
                    break;
                }
            }
            ++now;
            if (now == tot)
                break;
            dis = bis[beg + now] - bis[beg];
        }
        beg++;
    }
    sort(res, res + sum, cmp);
    if (sum ==  0){
        cout << "NONE" << '\n';
        return 0;
    }
    for (int i = 0; i < sum; ++i){
        cout << res[i].begin << ' ' << res[i].distance << '\n';
    }
}
