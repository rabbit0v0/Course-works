//
//  1605.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/26.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include<stdio.h>
#include<iostream>
using namespace std;
int top = -1, top1 = -1;
char l[1000005], l1[1000005];
bool k[1000005];

void push1(char c){
    if (top1 == -1)
        l1[++top1] = c;
    else{
        if (c == ')' && l1[top1] == '('){
            top1--;
            k[top] = 1;
        }
        else if (c == ']' && l1[top1] == '['){
            top1--;
            k[top] = 1;
        }
        else if (c == '}' && l1[top1] == '{'){
            top1--;
            k[top] = 1;
        }
        else
            l1[++top1] = c;
    }
}

void push(char c){
    l[++top] = c;
    k[top] = 0;
    push1(c);
}

void pop(){
    if (top == -1)
        return;
    if (k[top]){
        if(l[top] == ')')
            push1('(');
        else if(l[top] == ']')
            push1('[');
        else if(l[top] == '}')
            push1('{');
    }
    else
        top1--;
    
    top--;
}

void query(){
    if (top == -1)
        return;
    cout << l[top] << '\n';
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
    int n;
    read(n);
    int c;
    char a;
    
    for (int i = 0; i < n; ++i){
        read(c);
        if (c == 1){
            a = getchar();
            push(a);
        }
        if (c == 2){
            pop();
        }
        if (c == 3){
            query();
        }
        if (c == 4){
            if (top1 == -1){
                cout << "YES" << '\n';
            }
            if (top1 != -1){
                cout << "NO" << '\n';
            }
        }
    }
}