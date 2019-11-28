//
//  friday.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/10.
//  Copyright © 2017年 幺幺. All rights reserved.
//

/*
 ID: yy_20161
 PROG: friday
 LANG: C++
 */
#include <stdio.h>
#include <fstream>
#include <iostream>
using namespace std;
ifstream fin ("friday.in");
ofstream fout ("friday.out");
int N;
int sum[7];

int calplain(int day){
    sum[(day + 13) % 7]++;
    int days = 13;
    for (int i = 1; i <= 11; ++i){
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10)
            days += 31;
        else if (i == 2)
            days += 28;
        else if (i == 4 || i == 6 || i == 9 || i == 11)
            days += 30;
        sum[(day + days) % 7]++;
    }
    return (day + 365) % 7;
}

int calleap(int day){
    sum[(day + 13) % 7]++;
    int days = 13;
    for (int i = 1; i <= 11; ++i){
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10)
            days += 31;
        else if (i == 2)
            days += 29;
        else if (i == 4 || i == 6 || i == 9 || i == 11)
            days += 30;
        sum[(day + days) % 7]++;
    }
    return (day + 366) % 7;
}

int main(){
    fin >> N;
    int k = 0, lastday = 0;
    while (k < N){
        if (k == 0)
            lastday = calplain(0);
        else if (k == 200 || k == 300)
            lastday = calplain(lastday);
        else{
            if (k % 4 == 0)
                lastday = calleap(lastday);
            else
                lastday = calplain(lastday);
        }
        k++;
    }
    fout << sum[6] << ' ' << sum[0] << ' ' << sum[1] << ' ' << sum[2] << ' ' << sum[3] << ' ' << sum[4] << ' ' << sum[5] << '\n';
}
