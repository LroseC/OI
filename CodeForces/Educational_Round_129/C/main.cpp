#include <vector>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#define read std::cin
using i32 = int;
using i64 = long long;
using vi32 = std::vector<i32>;
using PII = std::pair<i32, i32>;
const int N = 10010;

i32 n;
i32 top;
PII stk[N];
i32 a[N], b[N];

void print(int x, int y)
{
	stk[++top] = std::make_pair(x, y);
}
void flush(void)
{
	printf("%d\n", top);
	for (int i = 1; i <= top; ++i) {
		printf("%d %d\n", stk[i].first, stk[i].second);
	}
	top = 0;
}

void work(void)
{
	read >> n;
	for (int i = 0; i < n; ++i) {
		read >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		read >> b[i];
	}
	std::vector<PII> tmp(n);
	for (int i = 0; i < n; ++i) {
		tmp[i] = std::make_pair(a[i], b[i]);
	}
	std::sort(tmp.begin(), tmp.end());
	bool fail = 0;
	for (int i = 1; i < n; ++i) {
		if (tmp[i].second < tmp[i - 1].second) fail = 1;
	}
	if (fail) {
		puts("-1");
		return;
	}
	for (int i = 0; i < n; ++i) {
		tmp[i] = std::make_pair(a[i], b[i]);
	}
	for (int i = 0; i < n; ++i) {
		i32 min = -1;
		for (int j = i; j < n; ++j) {
			if (min == -1 || tmp[j] < tmp[min])
				min = j;
		}
		if (i != min)
			print(i + 1, min + 1);
		std::swap(tmp[i], tmp[min]);
	}
	flush();
}

int main(void)
{
	//Think twice, code once.
	std::ios::sync_with_stdio(false);
	i32 tt; read >> tt;
	while (tt--) {
		work();
	}
	return 0;
}
