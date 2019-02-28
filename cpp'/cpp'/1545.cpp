//
//  1545.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/9.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
int n = 0;
int m = 0;
int k = 0;
int x[100000];
int y[100000];
int r[100000];
char color[100000];
int R = 0;
int G = 0;
int B = 0;
int nt[1001][1001];
bool visit[1001][1001];
int main(){
    scanf("%d%d%d", &n, &m, &k);
    for(int i = 1; i <= k; ++i){
        scanf("%d%d%d", &x[i], &y[i], &r[i]);
        scanf("%c",&color[i]);
        scanf("%c",&color[i]);
    }
    for(int i = 1; i <= 1000; ++i){
        for(int j = 1; j <= 1000; ++j){
            nt[i][j] = j + 1;
        }
    }
    for(int w = k; w > 0; --w){
        int minrow = x[w] - r[w];
        if(minrow < 1)
            minrow = 1;
        int maxrow = x[w] + r[w];
        if(maxrow > n)
            maxrow = n;
        for(int i = minrow; i <= maxrow; ++i){
            int left = 0;
            int right = 0;
            int dx = (int) sqrt(r[w] * r[w] - (x[w] - i) * (x[w] - i));
            left = y[w] - dx;
            if(left < 1)
                left = 1;
            right = y[w] + dx;
            if(right > m)
                right = m;
            for(int j = left; j <= right; ){
                if(visit[i][j]) {
                    j = nt[i][j];
                    continue;
                }
                visit[i][j] = true;
                if(color[w] == 'R')
                    R++;
                if(color[w] == 'G')
                    G++;
                if(color[w] == 'B')
                    B++;
                int jbak = j;
                j = nt[i][j];
                nt[i][jbak] = nt[i][right];
            }
        }
    }
    
    printf("Red:%d\nGreen:%d\nBlue:%d\n", R, G, B);

    return 0;
}