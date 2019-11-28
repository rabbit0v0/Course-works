//
//  聘礼.cpp
//  PPCA
//
//  Created by 施晓钰 on 31/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define inf (0x3f3f3f3f)
const int maxn = 105;

int m, n;
struct Goods{
    int p, l, v;
    int num[maxn];
    int val[maxn];
}goods[maxn];
int map[maxn][maxn];

int dijk(int x){
    int i, j;
    int level = goods[x].l;
    int cost[maxn];
    bool vis[maxn];
    memset(cost, inf, sizeof(cost));
    memset(vis, false, sizeof(vis));
    for (i = 0; i <= n; i++){
        if (goods[i].l - level <= m && goods[i].l >= level)
            cost[i] = map[0][i];
    }
    vis[0] = true;
    for (i = 0; i < n; i++){
        int min = inf, imin = 0;
        for (j = 1; j <= n; j++){
            if (!vis[j] && cost[j] < min){
                imin = j;
                min = cost[j];
            }
        }
        if (min == inf)
            break;
        vis[imin] = true;
        
        for (j = 0; j <= n; j++){
            if (goods[j].l - level <= m && goods[j].l >= level)
                if (cost[j] > cost[imin] + map[imin][j])
                    cost[j] = cost[imin] + map[imin][j];
        }
    }
    return cost[1];
}

int main(){
    while (scanf("%d %d", &m, &n) != EOF){
        memset(goods, 0, sizeof(goods));
        memset(map, inf, sizeof(map));
        int i, j;
        for (i = 1; i <= n; i++){
            scanf("%d %d %d", &goods[i].p, &goods[i].l, &goods[i].v);
            for (j = 0; j < goods[i].v; j++){
                scanf("%d %d", &goods[i].num[j], &goods[i].val[j]);
            }
            map[0][i] = goods[i].p;
        }
        for (i = 1; i <= n; i++){
            for (j = 0; j < goods[i].v; j++){
                if (abs(goods[goods[i].num[j]].l - goods[i].l) <= m){
                    if (map[goods[i].num[j]][i] > goods[i].val[j]){
                        map[goods[i].num[j]][i] = goods[i].val[j];
                    }
                }
            }
        }
        int min = inf;
        for (i = 1; i <= n; i++){
            int tmp = dijk(i);
            if (tmp < min)
                min = tmp;
        }
        printf("%d\n", min);
    }
    return 0;
}
