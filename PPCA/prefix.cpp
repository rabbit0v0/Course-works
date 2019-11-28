//
//  prefix.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:prefix
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int n=0;
int ans=0;
bool dp[2000005];
string s;
string p[205];

void solve(){
    memset(dp, 0, sizeof(dp));
    dp[0] = true;
    int t = s.size();
    for(int i = 0;i < t;i++){
        if(dp[i]){
            for(int j=0;j<n;j++){
                bool flag=true;
                for(int k=0;k<p[j].size();k++){
                    if(s[k+i]!=p[j][k]){
                        flag=false;
                        break;
                    }
                }
                if(flag)
                    dp[i+p[j].size()]=true;
            }
        }
    }
    for(int i = 0; i <= s.size(); i++){
        if(dp[i])
            ans=i;
    }
}

int main(){
    freopen("prefix.in","r",stdin);
    freopen("prefix.out","w",stdout);
    while(cin>>p[n]){
        if(p[n]==".") break;
        n++;
    }
    string temp;
    while(cin>>temp){
        s+=temp;
    }
    solve();
    cout << ans << '\n';
}
