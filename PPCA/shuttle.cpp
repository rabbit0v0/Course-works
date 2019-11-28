//
//  shuttle.cpp
//  PPCA
//
//  Created by 施晓钰 on 30/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

/*
 ID:yy_20161
 LANG:C++
 PROB:shuttle
 */
#include <iostream>
#include <string.h>
using namespace std;
#define Limit 150001
struct eq
{
    char s[30];
    int p;
    int last;
}q[Limit];
char begin1[30],end1[30];
int ans[1000],ans_n;
int n;
void init()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        begin1[i]='W';
        end1[i]='B';
    }
    begin1[n+1]=' ';
    end1[n+1]=' ';
    for(int i=n+2;i<=n*2+1;i++)
    {
        begin1[i]='B';
        end1[i]='W';
    }
}
void print(int x)
{
    if(q[x].last==0)
    {
        ans_n++;
        ans[ans_n]=q[x].p;
        return;
    }
    print(q[x].last);
    ans_n++;
    ans[ans_n]=q[x].p;
}
void bfs()
{
    int l=0,r=1;
    q[1].last=0;
    q[1].p=n+1;
    memcpy(q[1].s,begin1,sizeof(q[1].s));
    while(l<r)
    {
        l++;
        char s[30];
        int p=q[l].p;
        if(p-1>0&&q[l].s[p-1]=='W')
        {
            memcpy(s,q[l].s,sizeof(s));
            s[p]='W';
            s[p-1]=' ';
            r++;
            memcpy(q[r].s,s,sizeof(q[r].s));
            q[r].p=p-1;
            q[r].last=l;
            if(memcmp(q[r].s,end1,sizeof(q[r].s))==0)
            {
                print(r);
                return;
            }
        }
        if(p+2<=2*n+1&&q[l].s[p+2]=='B'&&q[l].s[p+1]=='W')
        {
            memcpy(s,q[l].s,sizeof(s));
            s[p]='B';
            s[p+2]=' ';
            r++;
            memcpy(q[r].s,s,sizeof(q[r].s));
            q[r].p=p+2;
            q[r].last=l;
            if(memcmp(q[r].s,end1,sizeof(q[r].s))==0)
            {
                print(r);
                return;
            }
        }
        if(p+1<=2*n+1&&q[l].s[p+1]=='B')
        {
            memcpy(s,q[l].s,sizeof(s));
            s[p]='B';
            s[p+1]=' ';
            r++;
            memcpy(q[r].s,s,sizeof(q[r].s));
            q[r].p=p+1;
            q[r].last=l;
            if(memcmp(q[r].s,end1,sizeof(q[r].s))==0)
            {
                print(r);
                return;
            }
        }
        if(p-2>0&&q[l].s[p-2]=='W'&&q[l].s[p-1]=='B')
        {
            memcpy(s,q[l].s,sizeof(s));
            s[p]='W';
            s[p-2]=' ';
            r++;
            memcpy(q[r].s,s,sizeof(q[r].s));
            q[r].p=p-2;
            q[r].last=l;
            if(memcmp(q[r].s,end1,sizeof(q[r].s))==0)
            {
                print(r);
                return;
            }
        }
    }
}
int main(){
    freopen("shuttle.in","r",stdin);
    freopen("shuttle.out","w",stdout);
    init();
    bfs();
    int c=0;
    for(int i=2;i<=ans_n;i++)
    {
        cout<<ans[i];
        c++;
        if(c%20==0||i==ans_n)cout<<endl;
        else
            cout<<' ';
    }
    return 0;
}
