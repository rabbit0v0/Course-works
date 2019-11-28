//
//  tree.cpp
//  PPCA
//
//  Created by 施晓钰 on 03/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <cstring>
#include <iostream>
#include <map>
using namespace std;
struct node{
    int no;
    node* father;
    node(){
        no = 0, father = NULL;
    }
};
int sum;
map<int, node*> done;

bool checkroot(){
    int tot = 0;
    map<int, node*> :: iterator now;
    now = done.begin();
    while (now != done.end()){
        if (now->second->father == NULL){
            tot++;
        }
        now++;
    }
    if (tot == 1)
        return 1;
    return 0;
}

int main(){
    while(1){
        done.clear();
        sum++;
        int m, n;
        cin >> m >> n;
        bool okay = 0;
        if (m < 0 && n < 0)
            break;
        if (m == 0 && n == 0){
            cout << "Case " << sum << " is a tree.\n";
            okay = 1;
        }
        while (m != 0 && n != 0){
            if (m == n){
                cout << "Case " << sum << " is not a tree.\n";
                okay = 1;
                break;
            }
            if (!done.count(m)){
                if (!done.count(n)){
                    node* M = new node;
                    node* N = new node;
                    M->no = m, N->no = n;
                    N->father = M;
                    done[m] = M;
                    done[n] = N;
                }
                else{
                    node* M = new node;
                    M->no = m;
                    if (done[n]->father != NULL){
                        cout << "Case " << sum << " is not a tree.\n";
                        okay = 1;
                        break;
                    }
                    done[n]->father = M;
                    done[m] = M;
                }
            }
            else{
                if (!done.count(n)){
                    node* N = new node;
                    N->no = n;
                    if (done[m]->father != NULL){
                        cout << "Case " << sum << " is not a tree.\n";
                        okay = 1;
                        break;
                    }
                    N->father = done[m];
                    done[n] = N;
                }
                else{
                    if (done[m]->father != NULL || done[n]->father != NULL){
                        okay = 1;
                        cout << "Case " << sum << " is not a tree.\n";
                        break;
                    }
                    done[n]->father = done[m];
                }
            }
            cin >> m >> n;
        }
        while (m != 0 || n != 0){
            cin >> m >> n;
        }
        bool flag = checkroot();
        if (flag && !okay){
            cout << "Case " << sum << " is a tree.\n";
        }
        else if (!okay)
            cout << "Case " << sum << " is not a tree.\n";
    }
}
