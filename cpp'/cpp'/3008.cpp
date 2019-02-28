#include <stdio.h>
#include <iostream>
using namespace std;

char map[1001][1001];
bool visit[1001][1001];
int n, m, x1, x2, y1, y2;
int uody[2] = {0, 0}, uodx[2] = {1, -1}, lory[2] = {1, -1}, lorx[2] = {0, 0}, dy[4] = {0, 1, 0, -1}, dx[4] = {1, 0, -1, 0};

struct pos{
    int x;
    int y;
    int step;
    pos(int a = 0, int b = 0, int c = 0){
        x = a;
        y = b;
        step = c;
    }
};

pos l[1000001];
int head = 0;
int tail = 0;

void push(pos k){
    l[++tail] = k;
     visit[k.x][k.y] = 1;
}

void pop(){
    if (head == tail)
        return;
    head++;
}

bool empty(){
    return head == tail;
}

bool inside(int x, int y){
    return (x >= 1 && x <= n && y >= 1 && y <= m) && !visit[x][y] && map[x][y] != '*';
}

pos query(){
    return l[head + 1];
}

int bfs(){
        while (tail > head){
        int x = query().x, y = query().y, step = query().step;
        pop();
       
        if (x == x2 && y == y2) return step;
        if (map[x][y] == '|'){
            for (int i = 0; i < 2; ++i){
                if (inside(x + uodx[i], y + uody[i])) {
                    pos tem = pos(x + uodx[i], y + uody[i], step + 1);
                    if (map[tem.x][tem.y] == '-') continue;
                    push(tem);
                }
            }
        } else if (map[x][y] == '-') {
            for (int i = 0; i < 2; ++i) {
                if (inside(x + lorx[i], y + lory[i])){
                    pos tem = pos(x + lorx[i], y + lory[i], step + 1);
                    if (map[tem.x][tem.y] == '|') continue;
                    push(tem);
                }
            }
        } else {
            for (int i = 0; i < 4; ++i){
                if (inside(x + dx[i], y + dy[i])){
                    pos tem = pos(x + dx[i], y + dy[i], step + 1);
                    if (map[tem.x][tem.y] == '|' && (i == 1 || i == 3)) continue;
                    if (map[tem.x][tem.y] == '-' && (i == 0 || i == 2)) continue;
                    push(tem);
                }
            }
        }
        
    }
    return -1;
}

int main() {
    cin>>n>>m;
    cin>>x1>>y1>>x2>>y2;
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= m; ++j){
            cin >> map[i][j];
        }
    }
    push(pos(x1, y1, 0));
    cout << bfs();
}
