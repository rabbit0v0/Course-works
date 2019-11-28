//
//  contact.cpp
//  PPCA
//
//  Created by 施晓钰 on 17/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:contact
 LANG: C++
 */
#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iostream>
#include <algorithm>
#define CLEAR(a,val) memset(a,val,sizeof (a))
#define FOR(i,a,b)   for(int i=(a);i<(b);i++)
#define FORE(i,a,b)  for(int i=(a);i<=(b);i++)
#define FORC(c,it)   for(typeof((c).begin()) i=(c).begin();i!=(c).end();i++)
#define ALL(a)       (a).begin(),(a).end()
typedef long long LL;
using namespace std;
map<string,int> mp;
vector<pair<int,string> > vt;
bool cmp(const pair<int,string> &a,const pair<int,string> &b){
    if (a.first > b.first) return true;
    if (a.first < b.first) return false;
    int an = a.second.size();
    int bn = b.second.size();
    if (an < bn) return true;
    if (an > bn) return false;
    return a.second < b.second;
}
int A,B,N;
int main()
{
    freopen("contact.in","r",stdin);
    freopen("contact.out","w",stdout);
    string str="";
    string line;
    scanf("%d %d %d%*c",&A,&B,&N);
    while(getline(cin,line)){
        str+=line;
    }
    mp.clear();
    vt.clear();
    FORE(len,A,B){
        for(int i=0;i+len<=str.size();i++){
            mp[str.substr(i,len)]++;
        }
    }
    map<string,int> ::iterator it=mp.begin();
    while(it!=mp.end()){
        vt.push_back(make_pair(it->second,it->first));
        ++it;
    }
    sort(ALL(vt),cmp);
    int Pt=0;
    int Old=-1;
    int counter=0;
    int re=0;
    while(Pt<vt.size()){
        if (vt[Pt].first != Old){
            if (re==N) break;
            if (re!=0) printf("\n");
            ++re;
            counter=0;
            printf("%d\n%s",vt[Pt].first,vt[Pt].second.c_str());
            Old=vt[Pt++].first;
        }
        else{
            counter++;
            if (counter%6==0){
                printf("\n%s",vt[Pt].second.c_str());
            }else printf(" %s",vt[Pt].second.c_str());
            ++Pt;
        }		
    }
    printf("\n");
    return 0;
}
