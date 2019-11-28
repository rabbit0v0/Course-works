//
//  milk3.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/13.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: milk3
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int a[4]= {0};	
int fg[22][22]= {0};
int note[22]= {0};
void search(int x,int y,int z) {
    if(fg[x][y]==1) {
        return ;
    }
    fg[x][y] = 1;
    if(x == 0) {
        note[z] = 1;
    }
    int ji[4]= {0};
    ji[1]=x;
    ji[2]=y;
    ji[3]=z;
    for(int i = 1; i <= 3; ++i){
        for(int j = 1; j <= 3; ++j) {
            if(i != j) {
                if(ji[i] != 0 && ji[j] != a[j]) {
                    if(ji[i] > a[j] - ji[j]) {
                        int t1 = ji[i],t2 = ji[j];
                        ji[i] -= a[j]-ji[j];
                        ji[j] = a[j];
                        search(ji[1],ji[2],ji[3]);
                        ji[i] = t1;
                        ji[j] = t2;
                    }
                    if(ji[i] <= a[j] - ji[j]) {
                        int t1 = ji[i],t2 = ji[j];
                        ji[j] += ji[i];
                        ji[i] = 0;
                        search(ji[1],ji[2],ji[3]);
                        ji[i] = t1;
                        ji[j] = t2;
                    }
                }
            }
        }
    }
    return ;
}
int main() {
    freopen("milk3.in", "r", stdin);
    freopen("milk3.out", "w", stdout);
    cin>>a[1]>>a[2]>>a[3];
    search(0,0,a[3]);
    for(int i = 0; i <= a[3] - 1; ++i) {
        if(note[i]) {
            cout << i << ' ';
        }
    }
    cout << a[3] << endl;
    return 0;
}
