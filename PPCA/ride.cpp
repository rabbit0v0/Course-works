//
//  ride.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/10.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: ride
 LANG: C++
 */
#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

ifstream fin ("ride.in");
ofstream fout ("ride.out");

int main(){
    string comet;
    string group;
    fin >> comet >> group;
    int res1 = 1, res2 = 1;
    for (int i = 0; i < comet.length(); ++i)
        res1 *= comet[i] - 'A' + 1;
    for (int i = 0; i < group.length(); ++i)
        res2 *= group[i] - 'A' + 1;
    if (res1 % 47 == res2 % 47)
        fout << "GO\n";
    else
        fout << "STAY\n";
}
