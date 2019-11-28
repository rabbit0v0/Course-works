//
//  stamps.cpp
//  PPCA
//
//  Created by 施晓钰 on 17/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:stamps
 LANG: C++
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
int K, N, cents[55], res;
int num[2000005];
int main(){
    freopen("stamps.in", "r", stdin);
    freopen("stamps.out", "w", stdout);
    cin >> K >> N;
    for (int i = 0; i < N; ++i){
        cin >> cents[i];
    }
    sort(cents, cents + N);
    int mon = 0;
    while (1){
        if ((num[mon] && num[mon] <= K) || mon == 0)
            for (int i = 0; i < N; ++i){
                if (num[mon + cents[i]])
                    num[mon + cents[i]] = min(num[mon + cents[i]], num[mon] + 1);
                else num[mon + cents[i]] = num[mon] + 1;
            }
        else{
            cout << mon - 1 << '\n';
            return 0;
        }
        mon++;
    }
}
