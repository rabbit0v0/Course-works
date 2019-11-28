//
//  fence9.cpp
//  PPCA
//
//  Created by 施晓钰 on 23/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:fence9
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int n, m, p;

int gcd(int x,int y)
{
    if (x > y) swap(x, y);
    if (x == 0) return y;
    return gcd(y % x, x);
}

int main(){
    freopen("fence9.in","r",stdin);
    freopen("fence9.out","w",stdout);
    int b=0,s = 0;
    cin >> n >> m >> p;
    s = (m * p)/2;
    b += gcd(n,m);
    if (n!=p) b += gcd(abs(n-p),m);
    else b += m;
    b += p;
    cout << s + 1 - (b / 2) << '\n';
}
