#include <cstdio>
#include <cstdlib>

int main(void)
{
	system("g++ interstellar.cpp -O2 -o main -DDEBUG");
	system("g++ brute.cpp -O2 -o brute");
	system("g++ rand.cpp -O2 -o rand");
	for (int T = 1; T <= 100; ++T) {
		system("./rand > test.in");
		system("./main < test.in > test.out");
		system("./brute < test.in > test.ans");
		fprintf(stderr, "Test #%d\n", T);
		if (system("diff test.out test.ans")) {
			fprintf(stderr, "WA\n");
			return -1;
		}
		fprintf(stderr, "Accepted.\n");
	}
	return 0;
}
