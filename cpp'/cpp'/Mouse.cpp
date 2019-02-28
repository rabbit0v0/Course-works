//
//  Mouse.cpp
//  cpp'
//
//  Created by 施晓钰 on 2016/12/15.
//  Copyright © 2016年 施晓钰. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct m{
    int id, sc, st;
    m(int w = 0,int x = 0, int y = 0){
        id = w;
        sc = x;
        st = y;
    }
};

bool cmp(m a, m b){
    return (a.sc > b.sc) || (a.sc == b.sc && a.id < b.id) ;
}

m mouse[200005];

int main(){
    int N, R;
    scanf("%d%d", &N, &R);
    for (int i = 1; i <= 2 * N; ++i){
        scanf("%d", &mouse[i].sc);
        mouse[i].id = i;
    }
    for (int i = 1; i <= 2 * N; ++i){
        scanf("%d", &mouse[i].st);
    }
    sort(mouse + 1, mouse + 2 * N + 1, cmp);
    for (int i = 0; i < R; ++i){
        for(int j = 1; j <= N; ++j){
            if (mouse[2 * j - 1].st < mouse[2 * j].st){
                mouse[2 * j].sc += 2;
            }
            if (mouse[2 * j - 1].st > mouse[2 * j].st){
                mouse[2 * j - 1].sc += 2;
            }
            if (mouse[2 * j - 1].st == mouse[2 * j].st){
                mouse[2 * j].sc += 1;
                mouse[2 * j - 1].sc += 1;
            }
        }
        sort(mouse + 1, mouse + 2 * N + 1, cmp);
    }
    for (int i = 1; i <= 2 * N; ++i){
        printf("%d ", mouse[i].id);
    }
}
