//
//  fracdec.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:fracdec
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#define MAX_N 1000005

using namespace std;

int n,d;
int reb,ree;
int cnt=0;
int pos[MAX_N];
vector<int> v;

int get_place(int n){
    int ans=0;
    do{
        n/=10;
        ans++;
    }while(n!=0);
    return ans;
}

void print_ans(){
    int count = get_place(v[0])+1;
    cout << v[0] << ".";
    for(int i = 1; i < reb; i++){
        cout << v[i];
        count++;
        if(count == 76){
            cout << endl;
            count = 0;
        }
    }
    if(reb == ree && v[reb] == 0){
        if(reb == 1) cout<<"0"<<endl;
        else
            cout << endl;
        return;
    }
    cout << "(";
    count++;
    if(count == 76){
        cout << endl;
        count = 0;
    }
    for(int i = reb;i <= ree; i++){
        cout << v[i];
        count++;
        if(count == 76){
            cout << endl;
            count = 0;
        }
    }
    cout<<")"<<endl;
}

void division(int n,int d){
    while(1){
        v.push_back(n / d);
        n -= v.back()*d;
        n *= 10;
        if(pos[n] != -1){
            reb = pos[n]+1;
            ree = cnt;
            break;
        }
        else
            pos[n]=cnt;
        cnt++;
    }
    print_ans();
}
int main(){
    freopen("fracdec.in","r",stdin);
    freopen("fracdec.out","w",stdout);
    while(cin>>n>>d){
        memset(pos,-1,sizeof(pos));
        cnt = 0;
        v.clear();
        division(n,d);
    }
}
