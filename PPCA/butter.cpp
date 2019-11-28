//
//  butter.cpp
//  PPCA
//
//  Created by 施晓钰 on 18/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:butter
 LANG: C++
 */
#include<iostream>
#include<queue>
#include<vector>
#include<cstdio>
using namespace std;
int dobco[501];
int spfa[801];
int hashit[801];
int n,p,c;
queue<int> a;
const int MAXINT=2147483647;
vector<pair<int,int> > winco[801];
int SPFA(int t)
{
    int r = 0;
    for(int i = 1; i <= p; i++)
        spfa[i] = MAXINT;
    spfa[t] = 0;
    int judge;
    a.push(t);
    while(!a.empty())
    {
        judge = a.front();
        a.pop();
        hashit[judge]=0;
        for(int i = 0; i <= winco[judge].size() - 1; i++)
        {
            if(winco[judge].at(i).second + spfa[judge] < spfa[winco[judge].at(i).first])
            {
                spfa[winco[judge].at(i).first] = winco[judge].at(i).second + spfa[judge];
                if(hashit[winco[judge].at(i).first] == 0)
                {
                    a.push(winco[judge].at(i).first);
                    hashit[winco[judge].at(i).first] = 1;
                }
            }
        }
    }
    for(int i = 0; i <= n-1; i++)
        r += spfa[dobco[i]];
    return r;
}
int main()
{
    freopen("butter.in","r",stdin);
    freopen("butter.out","w",stdout);
    cin>>n>>p>>c;
    int js, min = MAXINT;
    for(int i = 0; i < n; i++)
        cin >> dobco[i];
    int t,m,d;
    for(int i = 0; i < c; i++)
    {
        cin>> t >> m >> d;
        winco[t].push_back(make_pair(m, d));
        winco[m].push_back(make_pair(t, d));
    }
    for(int i = 1; i <= p; i++)
    {
        js = SPFA(i);
        if(min > js)min = js;
    }
    cout << min << endl;
    return 0;
}
