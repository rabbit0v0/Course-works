//
//  stack.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/19.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

class sxystack{
public:
    
int top = -1, maxsize = 1000;
char* l = new char [maxsize];

void push(char x){
    if (top == maxsize - 1){
        char* _l = new char [2 * maxsize];
        for (int i = 0; i < maxsize; ++i){
            _l[i] = l[i];
        }
        _l[maxsize] = x;
        maxsize *= 2;
        delete []l;
        l = _l;
    }
    else
        l[++top] = x;
}

bool empty(){
    if (top == -1)
        return true;
    else
        return false;
}

char pop(){
    return l[top--];
}

char query(){
    return l[top];
}

bool match(){
    char c;
    char temp[100000];
    scanf("%s",temp);
    int len = strlen(temp);
    for(int i = 0; i < len; i++){
        c = temp[i];
        if (c == '(' || c == '[' || c == '{')
            push(c);
        if (top == -1)
            return false;
        if (c == ')' && query() == '(')
            pop();
        if (c == ']' && query() == '[')
            pop();
        if (c == '}' && query() == '{')
            pop();
    }
    if (empty())
        return true;
    return false;
}
  void makeempty()
    {
        top = -1;
    }
};

sxystack s1;
sxystack s2;

int main(){
    while(1){
    if (s1.match())
        cout << 1;
    else
    {  cout << 0;
        s1.makeempty();}
    }
}

