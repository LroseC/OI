#include <queue>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>

using namespace std;

const int N = 6;

int n;
string A, B;
string a[N], b[N];
queue<string> qa, qb;
unordered_map<string, int> ma, mb;

int bfs(queue<string> &q, unordered_map<string, int>&, unordered_map<string, int>&, string[], string[]);
int BFS(void);

int main()
{
	cin >> A >> B;
	while (cin >> a[n] >> b[n]) ++n;

	int ans = BFS();

	if (ans < 11) printf("%d\n", ans);
	else puts("NO ANSWER!");

	return 0;
}
int BFS(void)
{
	qa.push(A), qb.push(B);
	ma[A] = 0, mb[B] = 0;
	while (qa.size() && qb.size()) {
		int t;
		if (qa.size() < qb.size()) t = bfs(qa, ma, mb, a, b);
		else t = bfs(qb, mb, ma, b, a);
		if (t < 11) return t;
	}
	return 11;
}
int bfs(queue<string> &q, unordered_map<string, int>&ma, unordered_map<string, int>&mb, string a[], string b[])
{
	for (int fu = 0, tmp = q.size(); fu < tmp; ++fu) {
		string t = q.front();
		q.pop();
		for (int i = 0; i < t.size(); ++i)
			for (int j = 0; j < n; ++j)
				if (t.substr(i, a[j].size()) == a[j]) {
					string k = t.substr(0, i) + b[j] + t.substr(i + a[j].size());
					if (ma.count(k)) continue;
					if (mb.count(k)) return ma[t] + mb[k] + 1;
					ma[k] = ma[t] + 1;
					q.push(k);
				}
	}
	return 11;
}
