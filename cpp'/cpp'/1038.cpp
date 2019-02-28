//
//  1038.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/19.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

struct node{
    int data;
    node* next;
    node(int x = 0, node* p = NULL){
        data = x;
        next = p;
    }
};

node* a = NULL;
node* e = new node;


void add(int x){
    if (a == NULL){
        a = new node;
        a->next = a;
        a->data = x;
        e->next = a;
        return;
    }
    node* tem = new node;
    tem->data = x;
    tem->next = a;
    e->next->next = tem;
    e->next = tem;
}

void del(int x){
    node* tem1 = e->next;
    node* tem2 = e->next;
    for (int i = 1; i < x; ++i){
        tem1 = tem1->next;
    }
    for (int i = 0; i < x; ++i){
        tem2 = tem2->next;
    }
    tem1->next = tem2->next;
    delete tem2;
    e->next = tem1;
    return;
}

int main(){
    int M, k[10000],c;
    cin >> M;
    for (int i = 1; i < M; ++i){
        cin >> c;
        k[i] = c % (M - i + 1);
        if (k[i] == 0){
            k[i] += M - i + 1;
        }
    }
    for (int i = 1; i <= M; ++i){
        add(i);
    }
    for (int i = 1; i < M; ++i){
        del(k[i]);
    }
    cout << e->next->data;
    return 0;
}