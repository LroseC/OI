#include <map>
#include <vector>
#include <climits>
#include <cstring>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 510, M = 1e6 + 10;

int n;
i32 a[N], nex[N], del[N];
i32 res[M][2], top;

void print(int a, int b)
{
	top += 1;
	res[top][0] = a;
	res[top][1] = b;
}
void flush(void)
{
	printf("%d\n", top);
	for (int i = 1; i <= top; ++i) {
		printf("%d %d\n", res[i][0], res[i][1]);
	}
	top = 0;
}

void work(void)
{
	read >> n;
	std::map<i32, i32> mp;
	for (int i = 1; i <= n; ++i) {
		read >> a[i];
		mp[a[i]] += 1;
	}
	bool fail = 0;
	for (auto pr : mp) {
		if (pr.second & 1) fail = 1;
	}
	if (fail) {
		puts("-1");
		return;
	}
	mp.clear();
	std::vector<i32> seg;
	for (int i = n; i >= 1; --i) {
		if (mp[a[i]] == 0) {
			nex[i] = 0;
			mp[a[i]] = i;
		}
		else {
			nex[i] = mp[a[i]];
			mp[a[i]] = 0;
		}
	}
	for (i32 i = 1, pos = 1; i <= n; ++i) {
		if (!nex[i]) continue;
		for (i32 j = i + 1; j < nex[i]; j += 1) {
			if (!del[j]) pos += 1;
		}
		pos += 1;
		for (i32 j = i + 1; j < nex[i]; j += 1) {
			if (!del[j]) {
				print(pos, a[j]);
				pos += 1;
			}
		}
		seg.emplace_back(pos);
		pos += 1;
		del[i] = del[nex[i]] = 1;
	}
	flush();
	std::sort(seg.begin(), seg.end());
	printf("%d\n", seg.size());
	for (int i = 0; i < seg.size(); ++i) {
		printf("%d ", i == 0 ? seg[i] : seg[i] - seg[i - 1]);
	}
	puts("");
	std::fill(a + 1, a + 1 + n, 0);
	std::fill(nex + 1, nex + 1 + n, 0);
	std::fill(del + 1, del + 1 + n, 0);
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
