//
//  1622‘.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/4.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, head = 250000, tail = 250000;
int l[500000];
bool rev;

bool empty(){
    return head == tail;
}


int main(){
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i){
        char c, b = 0;
        c = getchar();
        while(c != '\n' && c != ' '){
            b = c;
            c = getchar();
        }
        if (b == 'H'){
            int k;
            scanf("%d", &k);
            getchar();
            push(k);
        }
        else if (b == 'Y'){
            query();
        }
        else if (b == 'E'){
            rev = 1 - rev;
        }
        else if (b == 'P'){
            pop();
        }
    }
}
