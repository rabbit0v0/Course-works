//
//  check.cpp
//  cpp'
//
//  Created by 施晓钰 on 09/08/2017.
//  Copyright © 2017 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
long long now;

int main(){
    cin >> now;
    for (int i = 2; i <= sqrt(now); ++i){
        while (now % i == 0){
            cout << i << ' ';
            now /= i;
        }
    }
    if (now != 1)
        cout << now;
}
