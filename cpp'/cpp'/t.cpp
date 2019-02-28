//
//  t.cpp
//  cpp'
//
//  Created by 施晓钰 on 19/07/2017.
//  Copyright © 2017 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int a, b;

int arithmeticShift(int x, int n)
{
    return (x >> n);
}

int negates(int x)
{
    return (~x + 1);
}

int divpwr2(int x, int n)
{
    int res = x;
    res = res >> n;
    return res;
}

int bitCount(int x)
{
    int sum = 0;
    for (int i = 0; i < 32; ++i){
        sum += (x & 1);
        x = x >> 1;
    }
    return sum;
}

int getByte(int x, int n)
{
    int tmp;
    tmp = ((x >> (n - 1)) & 1);
    return tmp;
}

int bang(int x)
{
    int tmp = 0^x;
    return 1^tmp;
}

int main(){
    cin >> a >> b;
    int res = arithmeticShift(a, b);
    cout << res << '\n';
}
