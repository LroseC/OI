#include <cctype>
#include <cstdio>

struct FSI
{
	template<typename T>
	FSI& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} read;

int n;

int main(void)
{
	read >> n;
	for (int i = 1; i <= n; ++i) {
		int op; read >> op;
		if (op == 1) {
			int l, r, val, time = i;
			read >> l >> r >> val;
			cg.emplace_back(time, l, val);
			cg.emplace_back(time, r + 1, -val);
		}
		else {
			Query tmp;
			tmp.time = i;
			read >> tmp.pos >> tmp.val;
		}
	}
	std::vector<int> ans;
	std::sort(cg.begin(), cg.end());
	std::sort(q.begin(), q.end());
	for (int pos = 1; pos <= n; ++pos) {
		while (i <= n && pos == cg[i].pos) {
			change(cg[i].time, cg[i].val); ++i;
		}
		while (pos == q[j].pos) {
			ans.emplace_back(
		}
	}
	return 0;
}
