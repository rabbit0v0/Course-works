//
//  beads.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/11.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: beads
 LANG: C++
 */
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
//ifstream fin("beads.in");
//ofstream fout("beads.out");
int N;
string necklace;
int maxbead = 0, pos = 0;

int main(){
    //time_t start,end,time;
    freopen("beads.in","r",stdin);
    freopen("beads.out","w",stdout);
//    start=clock();
    cin >> N >> necklace;
    for (int i = 0; i < N; ++i)
        necklace += necklace[i];
    int leng = 0;
    maxbead = 0;
    for (int i = 0; i < 2 * N; ++i){
        int posi = 0;
        leng = 0;
        int k = i;
        if (necklace[k] == 'w'){
            posi = k;
            while (necklace[k] == 'w' && k < posi + N && k < 2 * N && leng <= N){
                leng++;
                k++;
            }
            if (leng > maxbead)
                maxbead = leng;
        }
        if (necklace[k] == 'r'){
            if (!posi) posi = k;
            if (posi == 336)
                1;
            while (necklace[k] != 'b' && k < N + posi && k < 2 * N){
                leng++;
                k++;
            }
            pos = k - 1;
            if (k == 2 * N)
                break;
            while (necklace[pos] == 'w')
                pos--;
            while (necklace[k] != 'r' && k < N + posi && k < 2 * N){
                leng++;
                k++;
            }
            if (leng > maxbead)
                maxbead = leng;
        }
        else if (necklace[k] == 'b'){
            if (!posi) posi = k;
            while (necklace[k] != 'r' && k < posi + N && k < 2 * N){
                leng++;
                k++;
            }
            pos = k - 1;
            while (necklace[pos] == 'w')
                pos--;
            while (necklace[k] != 'b' && k < posi + N && k < 2 * N){
                leng++;
                k++;
            }
            if (leng > maxbead)
                maxbead = leng;
        }
        if (leng >= N){
            maxbead = N;
            break;
        }
        i = pos;
    }
    cout << maxbead << '\n';
//    end=clock();
//    time=end-start;
//    cout << endl << "time:" << time << endl;
    return 0;
}
