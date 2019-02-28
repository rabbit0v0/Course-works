//
//  1635.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, m;

struct node{
    int no;
    int cost;
    bool know;
    node* next;
    node(){
        no = 0;
        cost = 5000000;
        next = NULL;
        know = 0;
    }
};

node themap[1000001];
void push(int u, int v, int c){
    node* tem = new node;
    tem->no = v;
    tem->cost = c;
    tem->next = themap[u].next;
    themap[u].next = tem;
    node* tmp = new node;
    tmp->no = u;
    tmp->cost = c;
    tmp->next = themap[v].next;
    themap[v].next = tmp;
}

class cpile{
    node* data;
    int currentsize;
    int maxsize;
public:
    cpile(){
        data = new node[1000001];
        currentsize = 0;
        maxsize = 1000001;
    }
    ~cpile()
    {
        delete[] data;
    }
    void enqueue(node input)
    {
        int hole = ++currentsize;
        for (;hole > 1 && input.cost < data[hole / 2].cost;hole /= 2)
        {
            data[hole] = data[hole / 2];
        }
        data[hole] = input;
    }
    
    void percolatedown(int hole)
    {
        node tmp = data[hole];
        int child = 0;
        for (;hole * 2 <= currentsize;hole = child)
        {
            child = hole * 2;
            if (child < currentsize && data[child + 1].cost < data[child].cost)
                child++;
            if (data[child].cost < tmp.cost) data[hole] = data[child];
            else break;
        }
        data[hole] = tmp;
    }
    node dequeue()
    {
        node tmp = data[1];
        data[1] = data[currentsize];
        percolatedown(1);
        currentsize--;
        return tmp;
    }
};
cpile findmin;

void cal(int x){
    if (x == 0)
        return;
    node* tem = themap[x].next;
//    int min = 1000000, minnode = 0;
    while(tem != NULL){
        if(!themap[tem->no].know && themap[tem->no].cost > themap[x].cost + tem->cost){
            themap[tem->no].cost = themap[x].cost + tem->cost;
            findmin.enqueue(themap[tem->no]);
        }
        tem = tem->next;
    }
    node min = findmin.dequeue();
    while(themap[min.no].know){
        min = findmin.dequeue();
    }
    themap[min.no].know = 1;
    cal(min.no);
//    for (int i = 2;i <= n; ++i){
//        if (!themap[i].know && themap[i].cost < min){
//            min = themap[i].cost;
//            minnode = i;
//        }
//    }
//    themap[minnode].know = 1;
//    cal(minnode);
}

int main(){
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i){
        themap[i].no = i;
    }
    for (int i = 0; i < m; ++i){
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        push(u, v, c);
    }
    themap[1].cost = 0;
    themap[1].know = 1;
    cal(1);
    printf("%d", themap[n].cost);
    return 0;
}
