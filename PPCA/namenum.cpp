//
//  namenum.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: namenum
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
ifstream fin ("namenum.in");
ofstream fout ("namenum.out");
ifstream in("dict.txt");
string number;
int s;
int divide[15];

int main(){
    fin >> number;
    int k = 0;
    while (k < number.length()){
        divide[k] =  number[k] - 48;
        k++;
    }
    while (in){
        int num[15];
        string temper;
        in >> temper;
        if (temper.length() != k)
            continue;
        for (int i = 0; i < temper.length(); ++i){
            if (temper[i] >= 'A' && temper[i] <= 'C')
                num[i] = 2;
            else if (temper[i] >= 'D' && temper[i] <= 'F')
                num[i] = 3;
            else if (temper[i] >= 'G' && temper[i] <= 'I')
                num[i] = 4;
            else if (temper[i] >= 'J' && temper[i] <= 'L')
                num[i] = 5;
            else if (temper[i] >= 'M' && temper[i] <= 'O')
                num[i] = 6;
            else if (temper[i] == 'P' || temper[i] == 'R' || temper[i] == 'S')
                num[i] = 7;
            else if (temper[i] >= 'T' && temper[i] <= 'V')
                num[i] = 8;
            else if (temper[i] >= 'W' && temper[i] <= 'Y')
                num[i] = 9;
        }
        bool yes = 1;
        for (int i = 0; i < temper.length(); ++i){
            if (num[i] != divide[i])
                yes = 0;
        }
        if (yes){
            fout << temper << '\n';
            s++;
        }
    }
    if (!s) fout << "NONE" << '\n';
}
