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
const int N = 2e5 * 2 + 10;

int main(void)
{
	int n; read >> n;
	n *= 2;
	std::vector<int> p(n), q(n);
	int last = 1, llast = 1;
	for (int i = 0; i < n; ++i) {
		read >> p[i];
		if (p[i] != last) {
			while (p[i] != llast) {
				type[llast++] = ')';
			}
			type[p[i]] = '(';
			lim.emplace_back(p[i] - 1, i / 2);
		}
		vis[p[i]] = 1;
		while (vis[last]) {
			++last;
			llast = std::max(llast, last);
		}
	}
	last = n;
	std::memset(vis, 0, sizeof vis);
	for (int i = 0; i < n; ++i) {
		read >> q[i];
		if (q[i] != last) {
			while (p[i] != llast) {
				type[llast--] = ')';
			}
			type[p[i]] = '(';
			lim.emplace_back(p[i], n / 2 - i / 2);
		}
		vis[p[i]] = 1;
		while (vis[last]) {
			--last;
			llast = std::min(llast, last);
		}
	}
	std::sort(lim.begin(), lim.end());
	int i = 1;
	for (auto t : lim) {
	}
	return 0;
}
