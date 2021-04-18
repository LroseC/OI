#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

#define reg register
#define ll long long
const int M = 20;

struct PII
{
	int dis, now;
	PII (int dis, int now) : dis(dis), now(now) {}
	bool operator<(const PII &y) const
	{
		return dis > y.dis;
	}
};
int n;
int Q;
int s[40];
int dis[1 << M];
queue<int> q;

void Dij(void);

int main()
{
	scanf("%d%d", &n, &Q);
	for (int i = 0; i < n; ++i) scanf("%d", &s[i]);
	for (int i = n, j = 0; j < M; ++i, ++j) s[i] = 1 << j;
	
	Dij();
	
	int x, y;
	while (Q--) {
		scanf("%d%d", &x, &y);
		int tmp = x ^ y;
		printf("%d\n", dis[tmp]);
	}
	return 0;
}
void Dij(void)
{
	int tmp = n + M;
	for (int i = 0; i < tmp; ++i) dis[s[i]] = 1, q.push(s[i]);
	while (q.size()) {
		int now = q.front();
		q.pop();
		dis[now] = dis[now];
		for (int i = 0; i < tmp; ++i) {
			int k = now ^ s[i];
			if (dis[k]) continue;
			dis[k] = dis[now] + 1;
			q.push(k);
		}
	}
	return;
}
