//
//  comehome.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:comehome
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int ord(char c){
    if ((c>='a')&&(c<='z')) return (c-'a'+27);
    if ((c>='A')&&(c<='Z')) return (c-'A'+1);
    return  0;
}

int main(){
    freopen("comehome.in", "r", stdin);
    freopen("comehome.out", "w", stdout);
    int p,map[53][53];
    cin>>p;
    for (int i=1;i<=52;i++)
        for (int j=1;j<=52;j++)
            map[i][j]=1000000000;
    for (int i=1;i<=p;i++){
        char c;
        int x,y,d;
        cin>>c;
        x=ord(c);
        cin>>c;
        y=ord(c);
        cin>>d;
        if (d<map[x][y]){
            map[x][y]=d;
            map[y][x]=d;
        }
    }
    for (int k=1;k<=52;k++)
        for (int i=1;i<=52;i++)
            for (int j=1;j<=52;j++)
                if (map[i][k] + map[k][j] < map[i][j])
                    map[i][j] = map[i][k] + map[k][j];
    int res=2147483647, k = 0;
    for (int i = 1; i <= 25; i++)
        if (map[i][26] < res){
            res = map[i][26];
            k = i;
        }
    cout << (char)(k + 'A' - 1) << " " << res << '\n';
    return 0;
}
