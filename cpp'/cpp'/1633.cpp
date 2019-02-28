//
//  1633.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/23.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#define INT_MAX 1000000
using namespace std;
int m, n;

class disjointset
{
private:
    int size;
    int* parent;
public:
    disjointset(int i_size = 30001)
    {
        size = i_size;
        parent = new int[size];
        for (int i = 0; i < size; i++)
            parent[i] = -1;
    }
    int Find(int x)
    {
        if (parent[x] < 0 || parent[x] == -INT_MAX) return x;
        return parent[x] = Find(parent[x]);
    }
    void Union(int root1, int root2)
    {
        if (root1 == root2) return;
        if (parent[root1] > parent[root2])
        {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else
        {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
    void Unionelement(int elem1, int elem2)
    {
        int root1 = Find(elem1);
        int root2 = Find(elem2);
        if (parent[root1] == -INT_MAX || parent[root2] == -INT_MAX) return;
        Union(root1, root2);
    }
    void removesubtree(int elem)
    {
        parent[Find(elem)] = -INT_MAX;
    }
    int querysize(int elem)
    {
        return -parent[Find(elem)];
    }
};
disjointset l;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i){
        int k;
        scanf("%d", &k);
        int q[k];
        for (int j = 0; j < k; ++j){
            scanf("%d", &q[j]);
        }
        for (int j = 0; j < k; ++j){
            l.Unionelement(q[0], q[j]);
        }
    }
    int root = l.Find(0);
    int res = l.querysize(root);
    printf("%d", res);
    return 0;
}
