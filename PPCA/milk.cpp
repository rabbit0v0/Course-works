//
//  milk.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: milk
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int N, M;
struct farmer{
    int P, A;
    farmer(){
        P = 0; A = 0;
    }
};
farmer farmers[5005];

bool cmp(farmer a, farmer b){
    return a.P < b.P;
}

int main(){
    freopen("milk.in", "r", stdin);
    freopen("milk.out", "w", stdout);
    cin >> N >> M;
    for (int i = 0; i < M; ++i){
        cin >> farmers[i].P >> farmers[i].A;
    }
    sort(farmers, farmers + M, cmp);
    int sum = 0, k = 0, prise = 0;
    while (sum < N){
        sum += farmers[k].A;
        prise += farmers[k].A * farmers[k].P;
        k++;
    }
    k--;
    sum -= farmers[k].A;
    prise -= farmers[k].A * farmers[k].P;
    int need = N - sum;
    prise += need * farmers[k].P;
    cout << prise << '\n';
}
