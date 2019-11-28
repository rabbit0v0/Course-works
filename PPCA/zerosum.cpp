//
//  zerosum.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:zerosum
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N;

void dfs(int now, int sum, int num, string s){
    string tem = s;
    if (now == N){
        if (sum + num == 0)
            cout << tem << '\n';
        return;
    }
    if (num > 0)
        dfs(now + 1, sum, num * 10 + now + 1, s + ' ' + char(now + 1 + 48));
    else
        dfs(now + 1, sum, num * 10 - now - 1, s + ' ' + char(now + 1 + 48));
    s = tem;
    dfs(now + 1, sum + num, now + 1, s + '+' + char(now + 1 + 48));
    s = tem;
    dfs(now + 1, sum + num, -1 * now - 1, s + '-' + char(now + 1 + 48));
}

int main(){
    freopen("zerosum.in","r",stdin);
    freopen("zerosum.out","w",stdout);
    cin >> N;
    dfs(1, 0, 1, "1");
}
