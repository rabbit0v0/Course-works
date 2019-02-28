//
//  chain.cpp
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
    node* pre;
    node (int x = 0, node* p = NULL, node* q = NULL){
        data = x;
        next = q;
        pre = p;
    }
};

node* head = NULL;

void add(int x, node* p = head){
    if (head == NULL){
        head = new node;
        head->data = x;
        head->pre = head;
        head->next = head;
        return;
    }
    node* tem = new node;
    tem->data = x;
    tem->pre = p->pre;
    p->pre->next = tem;
    tem->next = p;
    p->pre = tem;
}

void del(node* p){
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete p;
}
