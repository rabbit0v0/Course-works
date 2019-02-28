//
//  1994.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/27.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int map[505][505], n, m;
bool visit[505][505];
int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
struct node{
    int x;
    int y;
    node* next;
    node(int a = 0, int b = 0, node* k = NULL){
        x = a;
        y = b;
        next = k;
    }
};

node* head = new node;
node* tail = head;

void push(int x, int y){
    node* a = new node;
    a->x = x;
    a->y = y;
    tail->next = a;
    tail = a;
}

void pop(){
    node* p = head->next;
    head->next = head->next->next;
    if (head->next == NULL)
        tail = head;
    delete p;
}

node* query(){
    return head->next;
}

bool empty(){
    return (head->next == NULL);
}

bool inside(int x, int y){
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void bfs(){
    while (!empty()){
        node* p = query();
        int x = p->x;
        int y = p->y;
        for (int i = 0; i < 4; ++i){
            if (inside(x + dx[i], y + dy[i]) && map[x + dx[i]][y + dy[i]] == 0 && !visit[x + dx[i]][y + dy[i]])
                push(x + dx[i],y + dy[i]);
        }
        visit[x][y] = 1;
        pop();
    }
}

void read(int &x)
{
    char c = getchar(), b = 1;
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            b = -1;
    for (x = 0; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x*= b;
    
}

int main(){
    int country = 0, landx[250000] = {0}, landy[250000] = {0}, all = 0;
    read(n);
    read(m);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            read(map[i][j]);
            if(map[i][j] == 0){
                landx[all] = i;
                landy[all++] = j;
            }
        }
    }
    for (int i = 0; i < all; ++i){
        if (!visit[landx[i]][landy[i]]){
            push(landx[i], landy[i]);
            bfs();
            country++;
        }
        
    }
    printf("%d", country);
    return 0;
}