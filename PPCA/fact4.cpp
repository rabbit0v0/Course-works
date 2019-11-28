//
//  fact4.cpp
//  PPCA
//
//  Created by 施晓钰 on 18/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:fact4
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int N;

int main(){
    freopen("fact4.in","r",stdin);
    freopen("fact4.out","w",stdout);
    cin >> N;
    if (N == 1){
        cout << 1 << '\n';
        return 0;
    }
    int ans = 1;
    for (int i = 0; 10 * i <= N; ++i){
        int k = i;
        while (i && !(k % 10))
            k /= 10;
        while (i && !(k % 5)){
            k /= 5;
            ans /= 2;
        }
        if (k)
            ans *= k;
        for (int j = 1; j <= 9 && 10 * i + j <= N; ++j){
            if (j == 5){
                int m = 10 * i + j;
                while (m && !(m % 5)){
                    ans /= 2;
                    m /= 5;
                }
                if (m)
                    ans *= m;
                continue;
            }
            ans *= (10 * i + j) % 10000;
            ans %= 10000;
            while (!(ans % 10))
                ans /= 10;
        }
    }
    cout << ans % 10 << '\n';
}
