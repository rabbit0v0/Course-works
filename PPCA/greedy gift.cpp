//
//  greedy gift.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/10.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: gift1
 LANG: C++
 */
#include <stdio.h>
#include <fstream>
#include <string>
#include <map>
using namespace std;

ifstream fin("gift1.in");
ofstream fout("gift1.out");

map<string, int> person;

struct people{
    int initial, div;
    int left;
    people(){
        initial = 0; div = 0; left = 0;
    }
};
people group[1000];

int main(){
    int num;
    fin >> num;
    string names[1000];
    for (int i = 0; i < num; ++i){
        fin >> names[i];
        person[names[i]] = i;
    }
    string temper;
    for (int i = 0; i < num; ++i){
        fin >> temper;
        fin >> group[person[temper]].initial >> group[person[temper]].div;
        if (group[person[temper]].div != 0){
            group[person[temper]].left += group[person[temper]].initial % group[person[temper]].div;
            int even = group[person[temper]].initial / group[person[temper]].div;
            string temp;
            for (int j = 0; j < group[person[temper]].div; ++j){
                fin >> temp;
                group[person[temp]].left += even;
            }
            group[person[temper]].left -= group[person[temper]].initial;
        }
    }
    for (int i = 0; i < num; ++i){
        fout << names[i] << ' ' << group[i].left << '\n';
    }
}
