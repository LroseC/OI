#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;

struct FastStreamInput
{
	using FSI = FastStreamInput;
	template<typename T>
	FSI& operator >> (T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res = res * f; return *this;
	}
} cin;

const int N = 1e5 + 10;

int n, m;
int A[N];
int b[N];

int main(void)
{
	cin >> n >> m;
	int cnt = 0;
	for (int i = 1; i <= m; ++i) {
		cin >> A[i];
		cnt += A[i] & 1;
	}
	if (m == 1) {
		if (A[1] == 1) printf("1\n1\n1\n");
		else printf("%d\n2\n%d %d\n", A[1], 1, A[1] - 1);
	}
	else {
		if (cnt > 2) puts("Impossible");
		else {
			sort(A + 1, A + 1 + m, [](int a, int b) { return (a & 1) > (b & 1); });
			printf("%d ", A[1]);
			for (int i = 3; i <= m; ++i) printf("%d ", A[i]);
			printf("%d\n", A[2]);
			printf("%d\n", m - (A[1] <= 1));
			if (A[1] > 1)
				printf("%d ", A[1] - 1);
			for (int i = 3; i <= m; ++i) printf("%d ", A[i]);
			printf("%d\n", A[2] + 1);
		}
	}
	return 0;
}