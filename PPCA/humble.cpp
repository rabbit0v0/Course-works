
//
//  humble.cpp
//  PPCA
//
//  Created by 施晓钰 on 17/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:humble
 LANG: C++
 */
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
int K, N, sum, alr[100005];
long long S[1005];
long long ugly[100005];

int main(){
    freopen("humble.in", "r", stdin);
    freopen("humble.out", "w", stdout);
    cin >> K >> N;
    for (int i = 0; i < K; ++i){
        cin >> S[i];
    }
    ugly[0] = 1;
    sum = 1;
    long long tmp ;
    while (sum <= N){
        tmp = 11ll<<61;
        for (int j = 0; j < K; ++j){
            for (int k = alr[j]; k < sum; ++k){
                if (S[j] * ugly[k] > ugly[sum - 1]){
                    if (S[j] * ugly[k] < tmp)
                        tmp = S[j] * ugly[k];
                    alr[j] = k;
                    break;
                }
            }
        }
        ugly[sum++] = tmp;
    }
    cout << ugly[N] << '\n';
}
