//
//  kimbits.cpp
//  PPCA
//
//  Created by 施晓钰 on 18/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:kimbits
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
long long L, N, I;
long long c[100][100];

void C(){
    c[0][0] = 1;
    c[1][1] = 1;
    c[1][0] = 1;
    for(int i = 2; i <= 50; i ++)
    {
        for(int j = 0; j <= 50; j ++)
        {
            c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
        }
    }
}

int main(){
    freopen("kimbits.in","r",stdin);
    freopen("kimbits.out","w",stdout);
    cin >> N >> L >> I;
    C();
    for(int i = 1; i <= N; i ++){
        if(L == 0 || I == 1) {
            cout << "0";
            continue;
        }
        long long u = 0;
        for(int j = 0; j <= L; ++j)
            u += c[N - i][j];
        if(I <= u)
            cout << "0";
        else{
            cout << "1";
            L --;
            I -= u;
        }
    }
    cout << '\n';
}
