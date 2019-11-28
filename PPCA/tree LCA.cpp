//
//  tree LCA.cpp
//  PPCA
//
//  Created by 施晓钰 on 06/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define mxn 100020
#define mxe 200200
#define inf 0x3f3f3f3f

int fst[mxn], nxt[mxe], to[mxe], cost[mxe], e;
int dep[mxn], fa[22][mxn], d[mxn];

void init() {
    memset(fst, -1, sizeof fst);
    e = 0;
}
void add(int u, int v, int c) {
    to[e] = v, nxt[e] = fst[u], cost[e] = c, fst[u] = e++;
}
int n;

void dfs(int u, int p, int dis, int D) {
    dep[u] = D;
    fa[0][u] = p;
    d[u] = dis;
    for(int i = fst[u]; ~i; i = nxt[i]) {
        int v = to[i], c = cost[i];
        if(v == p) continue;
        dfs(v, u, dis + c, D + 1);
    }
}

void lca_init() {
    for(int k = 0; k < 21; ++k) {
        for(int i = 1; i <= n; ++i) {
            if(fa[k][i] == 0)
                fa[k+1][i] = 0;
            else
                fa[k+1][i] = fa[k][fa[k][i]];
        }
    }
}

int lca(int u, int v) {
    if(dep[u] > dep[v]) swap(u, v);
    for(int k = 0; k < 22; ++k)
        if((dep[v] - dep[u]) >> k & 1)
            v = fa[k][v];
    if(v == u) return u;
    for(int k = 21; k >= 0; --k)
        if(fa[k][u] != fa[k][v])
            u = fa[k][u], v = fa[k][v];
    return fa[0][u];
}

int kfa(int u, int k) {
    for(int i = 0; i < 22; ++i)
        if(k >> i & 1)
            u = fa[i][u];
    return u;
}

int main() {
    int cas;
    scanf("%d", &cas);
    while(cas--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; ++i) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            add(u, v, c);
            add(v, u, c);
        }
        dfs(1, 0, 0, 0);
        lca_init();
        char op[10];
        while(scanf("%s", op) && strcmp(op, "DONE")) {
            int u, v, w;
            scanf("%d%d", &u, &v);
            int p = lca(u, v);
            if(op[0] == 'D') {
                printf("%d\n", d[u] + d[v] - 2 * d[p]);
            }
            else {
                scanf("%d", &w);
                int x = dep[u] - dep[p];
                if(x + 1 >= w)
                    printf("%d\n", kfa(u, w - 1));
                else
                    printf("%d\n", kfa(v, dep[v] + dep[u] - 2 * dep[p] + 1 - w));
            }
        }
    }
    return 0;
}
