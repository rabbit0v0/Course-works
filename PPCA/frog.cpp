//
//  frog.cpp
//  PPCA
//
//  Created by 施晓钰 on 01/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
#define maxn 205
#define inf 999999.9
double ma[maxn][maxn];
double dist[maxn];
int vis[maxn];
double xy[maxn][2];
int n;
double far(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
double dijkstra(int u){
    for(int i = 1; i <= n; i++){
        dist[i] = ma[u][i];
        vis[i] = 0;
    }
    vis[u] = 1;
    dist[u] = 0;
    double mi;
    for(int i = 1; i < n; i++){
        mi = inf;
        int tm = 0;
        for(int j = 1; j <= n; j++){
            if(!vis[j] && dist[j] < mi){
                mi = dist[j];
                tm = j;
            }
        }
        vis[tm] = 1;
        if(tm == 0)
            break;
        for(int j = 1; j <= n; j++){
            if(!vis[j]){
                double maxx = max(dist[tm], ma[tm][j]);
                if(dist[j] > maxx)
                    dist[j] = maxx;
            }
        }
    }
    return dist[2];
}
int main()
{
    int ca=1;
    while(scanf("%d",&n)!=EOF)
    {
        if(n == 0)
            return 0;
        memset(ma,inf,sizeof(ma));
        memset(dist,inf,sizeof(dist));
        memset(vis,0,sizeof(vis));
        for(int i = 1; i <= n; i++){
            scanf("%lf %lf",&xy[i][0],&xy[i][1]);
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j < i; j++)
                if(i != j)
                    ma[i][j]=ma[j][i]=far(xy[i][0],xy[i][1],xy[j][0],xy[j][1]);
            ma[i][i] = 0;
        }
        double ans = dijkstra(1);
        printf("Scenario #%d\n",ca);
        ca++;
        printf("Frog Distance = %.3f\n\n",ans);
    }
}
