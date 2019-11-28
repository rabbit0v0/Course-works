//
//  area.cpp
//  PPCA
//
//  Created by 施晓钰 on 25/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
int N;
int dx[10] = {0, -1, 0, 1, -1, 0, 1, -1, 0, 1}, dy[10] = {0, -1, -1, -1, 0, 0, 0, 1, 1, 1};
struct node{
    int x, y;
} ver[1000005];

double det(int i){
    return (ver[i].x * ver[i + 1].y - ver[i].y * ver[i + 1].x);
}

double cal(int tot){
    double s = 0;
    for (int i = 0; i < tot; ++i){
        s += det(i);
    }
    return (0.5 * fabs(s));
}

int main(){
    cin >> N;
    int o = 0;
    while (o < N){
        o++;
        string poly;
        int tot = 0, nowx = 0, nowy = 0;
        cin >> poly;
        while (poly[tot] != '5'){
            nowx += dx[poly[tot] - 48];
            nowy += dy[poly[tot] - 48];
            ver[++tot].x = nowx;
            ver[tot].y = nowy;
        }
        if (tot <= 2){
            cout << 0 << '\n';
            continue;
        }
        double S = cal(tot);
        cout << S << '\n';
    }
}
