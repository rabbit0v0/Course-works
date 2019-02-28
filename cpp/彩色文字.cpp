#include <iostream>
#include <cstring>
#include <cstdio>
#include <stack>
using namespace std;
stack<int> l;
int yellow, red, blue;
int main(){
	char s[1005];
	gets(s);
	int len = strlen(s);
	for (int i = 0; i < len; ++i){
		if (s[i] == '<' && s[i + 1] == 'y' && s[i + 2] == 'e' && s[i + 3] == 'l' && s[i + 4] == 'l' && s[i + 5] == 'o' && s[i + 6] == 'w' && s[i + 7] == '>'){
			l.push(2);
			i += 7;
		}
		else if (s[i] == '<' && s[i + 1] == 'r' && s[i + 2] == 'e' && s[i + 3] == 'd' && s[i + 4] == '>'){
			l.push(1);
			i += 4;
		}
		else if (s[i] == '<' && s[i + 1] == 'b' && s[i + 2] == 'l' && s[i + 3] == 'u' && s[i + 4] == 'e' && s[i + 5] == '>'){
			l.push(3);
			i += 5;
		}
		else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){
			l.push(0);
		}
		else if (s[i] == '<' && s[i + 1] == '/' && s[i + 1 + 1] == 'y' && s[i + 2 + 1] == 'e' && s[i + 3 + 1] == 'l' && s[i + 4 + 1] == 'l' && s[i + 5 + 1] == 'o' && s[i + 6 + 1] == 'w' && s[i + 7 + 1] == '>'){
			while (l.top() != 2){
				yellow++;
				l.pop();
			}
			l.pop();
			i += 8;
		}
		else if (s[i] == '<' && s[i + 1] == '/' && s[i + 1 + 1] == 'r' && s[i + 2 + 1] == 'e' && s[i + 3 + 1] == 'd' && s[i + 4 + 1] == '>'){
			while (l.top() != 1){
				red++;
				l.pop();
			}
			l.pop();
			i += 5;
		}
		else if (s[i] == '<' && s[i + 1] == '/' && s[i + 1 + 1] == 'b' && s[i + 2 + 1] == 'l' && s[i + 3 + 1] == 'u' && s[i + 4 + 1] == 'e' && s[i + 5 + 1] == '>'){
			while (l.top() != 3){
				blue++;
				l.pop();
			}
			l.pop();
			i += 6;
		}

	}
	cout << red << ' ' << yellow << ' ' << blue;
}