
//
//  money.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:money
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
long long ans[10001];
int V, N;
int money[30];

int main(){
    freopen("money.in","r",stdin);
    freopen("money.out","w",stdout);
    cin >> V >> N;
    for (int i = 1; i <= V; ++i){
        cin >> money[i];
    }
    ans[0] = 1;
    for (int i = 1; i <= V; ++i){
        for (int j = money[i]; j <= N; ++j){
            ans[j] += ans[j - money[i]];
        }
    }
    cout << ans[N] << '\n';
}
