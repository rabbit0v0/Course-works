//
//  heritage.cpp
//  PPCA
//
//  Created by 施晓钰 on 23/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:heritage
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
string s1, s2;
int now;

void makenode(int start, int ending){
    if (start > ending)
        return;
    for (int i = start; i <= ending; ++i){
        if (s1[i] == s2[now]){
            now++;
            makenode(start, i - 1);
            makenode(i + 1, ending);
            cout << s1[i];
            return;
        }
    }
}

int main(){
    freopen("heritage.in","r",stdin);
    freopen("heritage.out","w",stdout);
    cin >> s1 >> s2;
    makenode(0, s1.size() - 1);
    cout << '\n';
}
