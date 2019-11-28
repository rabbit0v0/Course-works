//
//  farmJ.cpp
//  PPCA
//  最小费用最大流
//  Created by 施晓钰 on 04/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include<cstring>
using namespace std;
#define esize 40055
#define nsize 2000
#define inf 99999999

int minc(int a,int b)
{
    if(a<b)
        return a;
    return b;
}

struct  node{
    int v, cap, cost, next, re;
}edge[esize];
int n, m, ans;
int k, edgeHead[nsize];
int que[nsize], pre[nsize], dis[nsize];
bool vis[nsize];
int s,t;


void addEdge(int u, int v, int ca, int co){
    edge[k].v = v;
    edge[k].cap = ca;
    edge[k].cost = co;
    edge[k].next = edgeHead[u];
    edge[k].re = k + 1;
    edgeHead[u] = k++;
    edge[k].v = u;
    edge[k].cap = 0;
    edge[k].cost = -co;
    edge[k].next = edgeHead[v];
    edge[k].re = k - 1;
    edgeHead[v] = k++;
}

bool spfa(){
    int i, head = 0, tail = 1;
    for(i = 0; i <= t; i ++){
        dis[i] = inf;
        vis[i] = false;
    }
    dis[0] = 0;
    que[0] = 0;
    vis[s] = true;
    while(tail > head){
        int u = que[head++];
        for(i = edgeHead[u]; i != 0; i = edge[i].next){
            int v = edge[i].v;
            if(edge[i].cap && dis[v]> dis[u] + edge[i].cost){
                dis[v] = dis[u] + edge[i].cost;
                pre[v] = i;
                if(!vis[v]){
                    vis[v] = true;
                    que[tail++] = v;
                }
            }
        }
        vis[u] = false;
    }
    if(dis[t] == inf) return false;
    return true;
}

void end()
{
    int u, p, sum = inf;
    for(u = t; u != 0; u = edge[edge[p].re].v){
        p = pre[u];
        sum = minc(sum, edge[p].cap);
    }
    for(u = t; u != 0; u = edge[edge[p].re].v){
        p = pre[u];
        edge[p].cap -= sum;
        edge[edge[p].re].cap += sum;
        ans += sum * edge[p].cost;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    k=1;
    ans = 0;
    s=0;
    t=n+1;
    for(int j=1;j<=m;j++){
        int u,v,cost;
        scanf("%d%d%d",&u,&v,&cost);
        addEdge(u,v,1,cost);
        addEdge(v,u,1,cost);
    }
    addEdge(s,1,2,0);
    addEdge(n,t,2,0);
    while(spfa()) end();
    printf("%d\n",ans);
    return 0;
}
