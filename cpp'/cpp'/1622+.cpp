//
//  1622+.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
int n;
bool rev;
int zero[400005];
int zeros = 0, zerotail = 200000, zerohead = 200000;

class stack{
    int l[400005];
    int size, head, tail;
public:
    stack(){
        size = 0;
        head = 200001;//nothing at head
        tail = 200001;
    }
    bool empty(){
        return size == 0;
    }
    void push(int x){
        size++;
        if(!rev){
            l[++tail] = x;
            if(x == 0){
                zeros++;
                zero[++zerotail] = tail;
            }
        }
        else{
            l[head--] = x;
            if(x == 0){
                zeros++;
                zero[zerohead--] = head + 1;
            }
        }
    }
    void pop(){
        if (empty())
            return;
        size--;
        if (!rev){
            if (l[tail] == 0){
                zeros--;
                --zerotail;
            }
            --tail;
        }
        else{
            if (l[head + 1] == 0){
                zeros--;
                ++zerohead;
            }
            ++head;
        }
    }
    
    void cal(){
        if (size == 1){
            printf("%d\n", l[tail]);
            return;
        }
        if (zeros == 0){
            printf("%d\n", size & 1);
            return;
        }
        if(!rev){
            int tot = zero[zerohead + 1] - head - 1;
            if(tot == size - 1){
                printf("%d\n", tot & 1);
                return;
            }
            else{
                printf("%d\n", !(tot & 1));
                return;
            }
        }
        else{
            int tot = tail - zero[zerotail];
            if(tot == size - 1){
                printf("%d\n", tot & 1);
                return;
            }
            else{
                printf("%d\n", !(tot & 1));
                return;
            }
        }
    }
    
    void query(){
        if (empty())
            puts("Invalid.\n");
        else
            cal();
    }
};

stack s;

int main(){
    scanf("%d", &n);
    getchar();
    char str[105];
    for (int i = 0; i < n; ++i){
        scanf("%s", str);
        int len = (int)strlen(str);
        char b = str[len - 1];
        if (b == 'H'){
            int k;
            scanf("%d", &k);
            getchar();
            s.push(k);
        }
        else if (b == 'Y'){
            s.query();
        }
        else if (b == 'E'){
            rev = 1 - rev;
        }
        else if (b == 'P'){
            s.pop();
        }
    }
}
