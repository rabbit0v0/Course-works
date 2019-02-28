#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int a[10000];
int n = 8;

void fs(int h, int t){
    if (t-h == 2) {
        return;
    }
    int b[10000];
    for (int i = 0; i < t-h; ++i){
        if (i % 2 == 1) b[i/2] = a[i+h];
        else b[(t-h)/2+i/2] = a[i+h];
    }
    for (int i = 0; i < t-h;++i)
        a[i+h] = b[i];
    int mid = (h+t)/2;
    fs(h, mid-1);
    fs(mid, t);
}

int main(){
    for (int i = 0; i < n; ++i) a[i] = i;
    fs(0,8);
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    return 0;
}
