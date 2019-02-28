//
//  1029.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/2/6.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int main(){
    int n, change[101][2];
    queue<char> col[103];
    cin >> n;
    for (int i = 0; i <= n; ++i){
        char s[500];
        cin.getline(s, 500);
        //cout << s << ' ' << i << '\n';
        for (int k = 0; k < strlen(s); ++k){
            col[i].push(s[k]);
        }
    }
    for (int i = 1; i < n; ++i){
        for (int j = 0; j < 2; ++j){
            cin >> change[i][j];
            //cout << change[i][j];
        }
    }
    
    for (int i = 1; i < n; ++i){
        col[change[i][1]].push(' ');
        while (!col[change[i][0]].empty()){
            col[change[i][1]].push(col[change[i][0]].front());
            col[change[i][0]].pop();
        }
    }
    
    for (int i = n; i > 0; --i){
        if (!col[i].empty()){
            while (!col[i].empty()){
                cout << col[i].front();
                col[i].pop();
            }
        }
    }
    return 0;
}