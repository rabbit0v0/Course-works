//
//  1002.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/1/23.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    int l, w, n[1005][1005] = {0}, a, b, m = 0;
    cin >> l >> w;
    for (int i = 1; i <= l; ++i){
        for (int j = 1; j <= w; ++j){
            cin >> n[i][j];
        }
    }
    cin >> a >> b;
    
    int amo[1004][1004] = {0};
    amo[1][1] = n[1][1];
    for (int i = 2; i <= w; ++i){
        amo[1][i] = amo[1][i - 1] + n[1][i];
    }
    for (int i = 2; i <= l; ++i){
        for (int j = 1; j <= w; ++j){
            amo[i][j] = amo[i - 1][j] + amo[i][j - 1] + n[i][j] - amo[i - 1][j - 1];
        }
    }
    
    int now;
    for (int i = a; i <= l; ++i){
        for (int j = b; j <= w; ++j){
            now = amo[i][j] - amo[i - a][j] - amo[i][j - b] + amo[i - a][j - b];
          //  cout << amo[i][j] << ' ' << amo[i - a][j] << '\n';
            if (now > m)
                m = now;
        }
    }
    cout << m;
}