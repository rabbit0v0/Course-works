//
//  lamps.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:lamps
 LANG: C++
 */
#include<iostream>
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<algorithm>
using namespace std;
string s[102];
bool off[102],on[102],ans[102],v[5];
int n,c,sum;
bool cmp(string x,string y)
{
    return x<y;
}
char find(bool f)
{
    if (f) return '1';
    return '0';
}
void check()
{
    int k=0;
    for (int i=1; i<=n; ++i){
        if (on[i]&&!ans[i]) return;
        if (off[i]&&ans[i]) return;}
    for (int i=1; i<=4; ++i) if (v[i]) k++;
    if (c<k) return;
    if ((c-k)%2!=0) return;
    for (int i=1; i<=n; ++i) s[sum]=s[sum]+find(ans[i]);
    sum++;
}
void dfs(int x)
{
    if (x>4){
        check();
        return;}
    dfs(x+1);
    if (x==1) for (int i=1; i<=n; i+=1) ans[i]=!ans[i];
    if (x==2) for (int i=1; i<=n; i+=2) ans[i]=!ans[i];
    if (x==3) for (int i=0; i<=n; i+=2) ans[i]=!ans[i];
    if (x==4) for (int i=0; i<=n/3; i++) ans[i*3+1]=!ans[i*3+1];
    v[x]=true;
    dfs(x+1);
    v[x]=false;
    if (x==1) for (int i=1; i<=n; i+=1) ans[i]=!ans[i];
    if (x==2) for (int i=1; i<=n; i+=2) ans[i]=!ans[i];
    if (x==3) for (int i=0; i<=n; i+=2) ans[i]=!ans[i];
    if (x==4) for (int i=0; i<=n/3; i++) ans[i*3+1]=!ans[i*3+1];
}
int main()
{
    freopen("lamps.in","r",stdin);
    freopen("lamps.out","w",stdout);
    cin>>n>>c;
    int k;
    sum=0;
    memset(ans,1,sizeof(ans));
    cin>>k;
    while (k>0){
        on[k]=true;
        cin>>k;}
    cin>>k;
    while (k>0){
        off[k]=true;
        cin>>k;}
    dfs(1);
    sort(s,s+sum,cmp);
    for (int i=0; i<sum; ++i) cout<<s[i]<<endl;
    if (sum==0) cout<<"IMPOSSIBLE"<<endl;
    return 0;
}
