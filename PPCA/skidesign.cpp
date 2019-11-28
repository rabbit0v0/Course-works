//
//  skidesign.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/13.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: skidesign
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int N;
int h[1011];
int main(){
    freopen("skidesign.in","r",stdin);
    freopen("skidesign.out","w",stdout);
    cin >> N;
    for(int i = 0; i < N; ++i)
        cin >> h[i];
    int ans = 99999999;
    for(int i = 0; i < 100 - 17 + 1; ++i){
        int tans = 0;
        for(int j = 0; j < N; ++j){
            if(h[j] < i)tans += (i - h[j]) * (i - h[j]);
            if(h[j] > i + 17)tans += (h[j] - i - 17) * (h[j] - i - 17);
        }
        if (tans == 22946)
            cout << i;
        ans = min(ans, tans);
    }
    //cout << ans << endl;
    return 0;
}
