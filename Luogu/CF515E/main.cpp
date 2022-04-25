#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + (ch - '0') * f; ch = getchar(); }
		return *this;
	}
} read;

using i64 = long long;

int main(void)
{
	read >> n >> m;
	for (int i = 1; i <= n; ++i) {
		read >> d[i];
		d[i + n] = d[i];
	}
	for (int i = 1; i <= n; ++i) {
		read >> h[i];
		h[i + n] = h[i];
	}
	for (int i = 1, l, r; i <= m; ++i) {
		read >> l >> r;
		if (r < l) r += n;
		q.emplace_back(l, r);
	}
	auto cmp = [](PII a, PII b) { return a.second != b.second : a.second < b.second : a.first < b.first; }
	std::sort(q.begin(), q.end(), cmp);
	int R = 0;
	for (int i = 0; i < m; ++i) {
		auto t = q[i];
	}
	return 0;
}
