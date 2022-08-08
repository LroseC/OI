#include"grader.h"
#include<cstdio>

int32_t main(void){
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	uint32_t subId,n,opt,t;
	scanf("%u%u%u%u",&subId,&n,&opt,&t);
	vector<pair<uint32_t,uint32_t>> V;
	V.resize(t);
	for(uint32_t i=0;i<t;++i){
		static uint32_t x,y;
		scanf("%u%u",&x,&y);
		V[i]=make_pair(x,y);
	}
	bool res;
	if(opt)
		res=solve2(subId,n,V);
	else{
		vector<vector<bool>> M;
		M.resize(n,{});
		for(uint32_t i=0;i<n;++i)
			M[i].resize(n,false);
		for(const pair<uint32_t,uint32_t>& x:V)
			M[x.first][x.second]=true;
		res=solve1(subId,n,M);
	}
	printf("%d\n",res);
	return 0;
}
