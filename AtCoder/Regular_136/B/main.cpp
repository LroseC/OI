#include <set>
#include <cctype>
#include <cstdio>
#include <algorithm>

using namespace std;
using LL = long long;
const char endl = '\n';

struct FastStreamInputOutput
{
	using FSIO = FastStreamInputOutput;
	template<typename T>
	FSIO& operator>>(T &res)
	{
		res = 0; T f = 1; char ch = getchar();
		while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
		while (isdigit(ch)) { res = res * 10 + ch - '0'; ch = getchar(); }
		res *= f; return *this;
	}
	FSIO& operator<<(char x)
	{
		putchar(x);
		return *this;
	}
	FSIO& operator<<(const char x[])
	{
		for (int i = 0; x[i]; ++i) putchar(x[i]);
		return *this;
	}
	template<typename T>
	FSIO& operator<<(const T &res)
	{
		static char buf[50]; int p = -1; T x = res;
		if (x == 0) putchar('0');
		if (x < 0) { putchar('-'); x = -x; }
		while (x) { buf[++p] = x % 10; x /= 10; }
		while (~p) { putchar(buf[p] + '0'); --p; }
		return *this;
	}
} IO;

const int N = 5010;
using i64 = long long;

int Getrev(vector<int> &A)
{
	int res = 0;
	for (int i = 0; i < A.size(); ++i)
		for (int j = 0; j < i; ++j) res += A[j] > A[i];
	return res;
}

int main(void)
{
	// CHECK YOUR ARRAY TO MAKE SRUE YOUR CODE WON'T RE
	int n; IO >> n;
	vector<int> A(n), B(n);
	for (int i = 0; i < n; ++i) IO >> A[i];
	for (int i = 0; i < n; ++i) IO >> B[i];
	int revA = Getrev(A);
	int revB = Getrev(B);
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	for (int i = 0; i < n; ++i)
		if (A[i] != B[i]) {
			puts("No");
			return 0;
		}
	if (unique(A.begin(), A.end()) != A.end()) {
		puts("Yes");
		return 0;
	}
	puts((revA & 1) == (revB & 1) ? "Yes" : "No");
	return 0;
}
