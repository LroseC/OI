#include <map>
#include <queue>
#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

const string pur = "123804765";
typedef pair<int, string> PIS;

string str;
map<string, int> dis;
map<string, string> from;

int h(string s)
{
	int res = 0;
	for (int i = 0; i < 9; ++i) res += (pur[i] != s[i] && pur[i] != 0);
	return res >> 1;
}

int Astar(void)
{
	priority_queue< PIS, vector<PIS>, greater<PIS> > q;
	q.emplace(PIS{h(str), str});
	dis[str] = 0;
	while (q.size()) {
		auto t = q.top(); q.pop();
		string s = t.second;
		string kk = s;
		int d = dis[s];
		if (h(s) == 0) return t.first;
		int k = 0;
		for (int i = 0; i < 9; ++i)
			if (s[i] == '0') { k = i; break; }
		if (k > 2) {
			swap(s[k], s[k - 3]);
			if (!dis.count(s)) {
				from[s] = kk;
				dis[s] = d + 1;
				q.emplace(PIS({h(s) + d + 1, s}));
			}
			swap(s[k], s[k - 3]);
		}
		if (k + 3 < 9) {
			swap(s[k], s[k + 3]);
			if (!dis.count(s)) {
				from[s] = kk;
				dis[s] = d + 1;
				q.emplace(PIS({h(s) + d + 1, s}));
			}
			swap(s[k], s[k + 3]);
		}
		if (k % 3) {
			swap(s[k], s[k - 1]);
			if (!dis.count(s)) {
				from[s] = kk;
				dis[s] = d + 1;
				q.emplace(PIS({h(s) + d + 1, s}));
			}
			swap(s[k], s[k - 1]);
		}
		if ((k + 1) % 3) {
			swap(s[k], s[k + 1]);
			if (!dis.count(s)) {
				from[s] = kk;
				dis[s] = d + 1;
				q.emplace(PIS({h(s) + d + 1, s}));
			}
			swap(s[k], s[k + 1]);
		}
	}
}

int main(void)
{
	cin >> str;
	cout << Astar() << endl;
	string tmp = pur;
	return 0;
}