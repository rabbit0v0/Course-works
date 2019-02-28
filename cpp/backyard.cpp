#include <iostream>
#include <cstdio>
using namespace std;

int n, m, N;
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
char map[1005][1005];

struct ani{
	int d, c, m;
	ani(int x = 0, int y = 0, int z = 0){
		d = x; c = y; m = z;
	}
};
ani amount;
ani animal[1005][1005];

bool inside(int x, int y){
	return (x > -1 && x < n && y > -1 && y < m);
}

ani see(int x, int y, int go){
	amount = ani(0, 0, 0);
	if (go == 0){
		int l = y - 1, L = y;
		while (x > -1){
			if (L >= m){
				L = m - 1;
			}
			if (l < 0){
				amount.c += animal[x][L].c;
				amount.d += animal[x][L].d;
				amount.m += animal[x][L].m;

			}
			else{
				amount.c += (animal[x][L].c - animal[x][l].c);
				amount.d += (animal[x][L].d - animal[x][l].d);
				amount.m += (animal[x][L].m - animal[x][l].m);
			}
			L++;
			l--;
			x--;
		}
		return amount;
	}

	if (go == 1){
		int l = y - 1, l1 = y - 1;
		int L = x;
		while (x > -1 && l < m){
			if (l < 0){
				amount.c += animal[x][m - 1].c;
				amount.d += animal[x][m - 1].d;
				amount.m += animal[x][m - 1].m;
			}
			else{
				amount.c += (animal[x][m - 1].c - animal[x][l].c);
				amount.d += (animal[x][m - 1].d - animal[x][l].d);
				amount.m += (animal[x][m - 1].m - animal[x][l].m);
			}
			l++;
			x--;
		}
		while (L < n - 1 && l1 < m - 1){
			amount.c += (animal[++L][m - 1].c - animal[L][++l1].c);
			amount.d += (animal[L][m - 1].d - animal[L][l1].d);
			amount.m += (animal[L][m - 1].m - animal[L][l1].m);
		}
		return amount;
	}

	if (go == 2){
		int l = y - 1, L = y;
		while (x < n){
			if (L >= m){
				L = m - 1;
			}
			if (l < 0){
				amount.c += animal[x][L].c;
				amount.d += animal[x][L].d;
				amount.m += animal[x][L].m;
			}
			else {
				amount.c += (animal[x][L].c - animal[x][l].c);
				amount.d += (animal[x][L].d - animal[x][l].d);
				amount.m += (animal[x][L].m - animal[x][l].m);
			}
			L++;
			l--;
			x++;
		}
		return amount;
	}

	if (go == 3){
		int l = y, l1 = y, L = x;
		while (x > -1 && l > -1){
			amount.c += animal[x][l].c;
			amount.d += animal[x][l].d;
			amount.m += animal[x][l].m;
			l--;
			x--;
		}
		while (L < n - 1 && l1 > 0){
			amount.c += animal[++L][--l1].c;
			amount.d += animal[L][l1].d;
			amount.m += animal[L][l1].m;
		}
		return amount;
	}
}

int main(){
	//freopen("in.txt", "r", stdin);
	int i0, j0;
	scanf ("%d%d", &n, &m);
	char p = getchar();
	for (int i = 0; i < n; ++i){
		for (int j = 0; j <= m; ++j){
			map[i][j] = getchar();
			if (map[i][j] == 'H'){
				i0 = i; 
				j0 = j;
			}
		}
	}

	scanf ("%d", &N);
	char Go[1005];
	for (int i = 0; i < N; ++i){
		scanf ("%s", &Go[i]);
	}
	int go[1005];
	for (int i = 0; i < N; ++i){
		if (Go[i] == 'N')
			go[i] = 0;
		if (Go[i] == 'E')
			go[i] = 1;
		if (Go[i] == 'S')
			go[i] = 2;
		if (Go[i] == 'W')
			go[i] = 3;
		//cout << go[i] << endl;
	}

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			if (j == 0){
				if(map[i][j] == 'D')
					animal[i][j].d = 1;
				if(map[i][j] == 'C')
					animal[i][j].c = 1;
				if(map[i][j] == 'M')
					animal[i][j].m = 1;
				continue;
			}
			if (map[i][j] == 'D'){
				animal[i][j].d = animal[i][j - 1].d + 1;
				animal[i][j].c = animal[i][j - 1].c;
				animal[i][j].m = animal[i][j - 1].m;
			}
			else if (map[i][j] == 'C'){
				animal[i][j].d = animal[i][j - 1].d;
				animal[i][j].c = animal[i][j - 1].c + 1;
				animal[i][j].m = animal[i][j - 1].m;
			}
			else if (map[i][j] == 'M'){
				animal[i][j].d = animal[i][j - 1].d;
				animal[i][j].c = animal[i][j - 1].c;
				animal[i][j].m = animal[i][j - 1].m + 1;
			}
			else{
				animal[i][j] = ani(animal[i][j - 1].d, animal[i][j - 1].c, animal[i][j - 1].m);
			}
			//cout << animal[i][j].d;
		}
		//cout << endl;
	}

	for (int i = 0; i < N; ++i){
		if (inside(i0 + dx[go[i]], j0 + dy[go[i]])){
			i0 += dx[go[i]];
			j0 += dy[go[i]];
			ani c = ani(0, 0, 0);
			c = see(i0, j0, go[i]);
			cout << c.c << ' ' << c.d << ' ' << c.m << endl;
		}
	}

}