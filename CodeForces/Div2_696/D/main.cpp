#include <cctype>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 2e5 + 10;

inline int read(void)
{
	int res = 0, f = 1; char ch;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	do res = res * 10 + ch - '0'; while (isdigit(ch = getchar()));
	return res * f;
}

int n;
int a[N];
LL b[N];
LL tmp[N];

bool check(void)
{
	for (int i = 1; i <= n; ++i) {
		if (a[i] < tmp[i - 1]) return 0;
		tmp[i] = a[i] - tmp[i - 1];
	}
	if (tmp[n]) return 0;
	return 1;
}

int main(void)
{
	ios::sync_with_stdio(0);
	int T; cin >> T;
	while (T--) {
		bool fail = 1;
		cin >> n;

		for (int i = 1; i <= n; ++i) cin >> a[i];
		
		if (check()) {
			fail = 0;
		}
		else {
			bool swp = 0;
			for (int i = 1; i <= n; ++i) {
				if (a[i] >= b[i - 1])
					b[i] = a[i] - b[i - 1];
				else {
					if (i >= 2) {
						swap(a[i - 1], a[i - 2]);
						if (check()) {
							fail = 0;
							break;
						}
						swap(a[i - 1], a[i - 2]);
					}
					if (i >= 1) {
						swap(a[i - 1], a[i]);
						if (check()) {
							fail = 0;
							break;
						}
						swap(a[i - 1], a[i]);
					}
					if (i + 1 <= n) {
						swap(a[i], a[i + 1]);
						if (check()) {
							fail = 0;
							break;
						}
						swap(a[i - 1], a[i]);
					}
					if (i + 2 <= n) {
						swap(a[i + 1], a[i + 2]);
						if (check()) {
							fail = 0;
							break;
						}
					}
					break;
				}
			}
			if (b[n]) {
				swap(a[n - 1], a[n]);
				if (check()) {
					fail = 0;
				}
				swap(a[n - 1], a[n]);
				swap(a[n - 2], a[n - 1]);
				if (check()) {
					fail = 0;
				}
				swap(a[n - 2], a[n - 1]);
			}
		}
		if (fail) cout << "NO" << '\n';
		else cout << "YES" << '\n';
	}
	return 0;
}