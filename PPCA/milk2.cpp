//
//  milk2.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/11.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: milk2
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("milk2.in");
ofstream fout("milk2.out");
int N, latest;
int begint[10000], endt[10000];
int milking[1000000];
int yes, no;

int main(){
    fin >> N;
    for (int i = 0; i < N; ++i){
        fin >> begint[i] >> endt[i];
        if (endt[i] > latest)
            latest = endt[i];
    }
    for (int i = 0; i < N; ++i){
        for (int j = begint[i] + 1; j <= endt[i]; ++j){
            milking[j]++;
        }
    }
    int pos = 0, be = 0, st = 0;
    while (pos <= latest){
        while (!milking[pos])
            pos++;
        be = pos;
        if (st){
            if (no < be - st)
                no = be - st;
        }
        while (milking[pos])
            pos++;
        st = pos;
        if (yes < st - be)
            yes = st - be;
    }
    fout << yes << ' ' << no << '\n';
}
