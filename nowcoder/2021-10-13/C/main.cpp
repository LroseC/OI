#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1010;

int n, LIMIT, k;
int maxdis;
string str;
int dis[10][10];
vector<int> unknow;
vector<string> S;

inline int getint(char x)
{
	if (x == 'N') return 1;
	if (x == 'O') return 2;
	if (x == 'I') return 3;
	if (x == 'P') return 4;
}
inline char getchar(int x)
{
	if (x == 1) return 'N';
	if (x == 2) return 'O';
	if (x == 3) return 'I';
	if (x == 4) return 'P';
}

void dfs(int id)
{
	if (id == unknow.size()) {
		int val = 0;
		for (int i = 1; i < n; ++i)
			val += dis[getint(str[i - 1])][getint(str[i])];
		if (val < LIMIT) return;
		S.emplace_back(str);
		return;
	}
	int u = unknow[id];
	for (int i = 1; i <= 4; ++i) {
		str[u] = getchar(i);
		dfs(id + 1);
	}
}

int main(void)
{
	cin >> n >> LIMIT >> k >> str;
	if (LIMIT == 0) {
		for (int i = 0; i < n; ++i)
			if (str[i] == '?')
				str[i] = 'I';
		cout << str << endl;
	}
	else {
		for (int i = 0; i < n; ++i) {
			if (str[i] == '?')
				unknow.emplace_back(i);
		}
		for (int i = 1; i <= 4; ++i)
			for (int j = 1; j <= 4; ++j) {
				cin >> dis[i][j];
				maxdis = max(maxdis, dis[i][j]);
			}
		dfs(0);
		sort(S.begin(), S.end(), greater<string>());
		if (k > S.size()) {
			cout << -1 << endl;
		}
		else {
			--k;
			cout << S[k] << endl;
		}
	}
	return 0;
}
