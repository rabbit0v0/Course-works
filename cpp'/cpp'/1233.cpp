//
//  1233.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/7.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, m, start, M, ways;
bool visit[11];
int con[11][11], tail[11];

void way(int dot, int depth){
    if (depth == M){
        ways++;
        return;
    }
    visit[dot] = 1;
    for (int i = 0; i < 10; ++i){
        if (con[dot][i] != 0 && !visit[con[dot][i]]){
            way(con[dot][i], depth + 1);
        }
    }
    visit[dot] = 0;
}

int main(){
    cin >> n >> m >> start >> M;
    for (int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        con[a][tail[a]] = b;
        tail[a]++;
    }
    way(start, 0);
    cout << ways;
    return 0;
}

