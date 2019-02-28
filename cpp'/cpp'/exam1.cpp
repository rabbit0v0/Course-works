//
//  exam.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/7/13.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <map>
#include <queue>
using namespace std;
int K;
map<int, int> countyname;
map<int, int> anti;
struct con{
    int number, price;
    con* next;
    con(){
        number = 0; price = 0; next = NULL;
    }
};
con connect[10005];
int branch[10005];
bool visit[10005];
int totalp;

bool check(){
    for (int i = 0; i < K; ++i){
        if (!visit[i])
            return 0;
    }
    return 1;
}

void dfs(int x){
    visit[x] = 1;
    cout << countyname[x] << ' ';
    if (check())
        return;
    con* temp = connect[x].next;
    while (temp != NULL){
        if (!visit[temp->number]){
        totalp += temp->price;
        dfs(temp->number);
        if (check())
            return;
        cout << countyname[x] << ' ';
        totalp += temp->price;
        }
        temp = temp->next;
    }
}

int main(){
    int wh = 1;
//    freopen("1.in", "r", stdin);
    cin >> K;
    for (int i = 0; i < K; ++i){
        connect[i].number = i;
    }
    int m = 0, start = 0;
    while(cin){
        int tem;
        cin >> tem;
        if (!anti.count(tem)){
            countyname[m] = tem;
            anti[tem] = m;
            m++;
        }
        int to;
        cin >> to;
        if (!anti.count(to)){
            countyname[K - wh] = to;
            anti[to] = K - wh;
            wh++;
        }
        branch[anti[tem]]++;
        branch[anti[to]]++;
        int pri;
        cin >> pri;
        con* tail1 = connect[anti[tem]].next;
        connect[anti[tem]].next = new con;
        connect[anti[tem]].next->number = anti[to];
        connect[anti[tem]].next->price = pri;
        connect[anti[tem]].next->next = tail1;
        con* tail2 = connect[anti[to]].next;
        connect[anti[to]].next = new con;
        connect[anti[to]].next->number = anti[tem];
        connect[anti[to]].next->price = pri;
        connect[anti[to]].next->next = tail2;
    }
    int maxb = 0;
    for (int i = 0; i < K; ++i){
        if (branch[i] > maxb){
            maxb = branch[i];
            start = i;
        }
        if (maxb == K)
            break;
    }
    visit[2] = 1;
    dfs(2);
    cout << totalp;
}
