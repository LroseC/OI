int main()
{
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; i ++ )
	{
		scanf("%d", &a[i]);
		if (a[i] > m)
		{
			puts("-1");
			return 0;
		}
	}

	int hh = 0, tt = 0;
	LL sum = 0;
	for (int i = 1, j = 0; i <= n; i ++ )
	{
		sum += a[i];
		while (sum > m) sum -= a[ ++ j];

		while (hh <= tt && q[hh] <= j)
		{
			if (hh < tt) remove(f[q[hh]] + a[q[hh + 1]]);
			hh ++ ;
		}
		int tail = tt;
		while (hh <= tt && a[q[tt]] <= a[i])
		{
			if (tt != tail) remove(f[q[tt]] + a[q[tt + 1]]);
			tt -- ;
		}
		if (hh <= tt && tt != tail) remove(f[q[tt]] + a[q[tt + 1]]);
		q[ ++ tt] = i;
		if (hh < tt) S.insert(f[q[tt - 1]] + a[q[tt]]);

		f[i] = f[j] + a[q[hh]];
		if (S.size()) f[i] = min(f[i], *S.begin());
	}

	printf("%lld\n", f[n]);

	return 0;
}
