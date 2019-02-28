//
//  1019.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/1/30.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

int main(){
    int n, m = 0;
    cin >> n;
    while (m++ < n){
        char s[105] = {0};
        stack<char> str;
        cin >> s;
        int q = sizeof(s) / sizeof(s[0]);
        bool flag = true;
        for (int i = 0; i < q; ++i){
            if (s[i] == '('){
                str.push(s[i]);
            }
            else if (s[i] == ')' && !str.empty()){
                str.pop();
            }
            else if (s[i] == ')' && str.empty()){
                flag = false;
                break;
            }
        }
        if (str.empty() && flag)
            cout << "YES" << '\n';
        else if (!str.empty() || !flag)
            cout << "NO" << '\n';
    }
    return 0;
}