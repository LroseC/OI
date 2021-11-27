#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll

const int N=20;
const char name[]="ka";

inline int myrand(reg int l,reg int r){
	return rand()%(r-l+1)+l;
}
char c[]={"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

int a[15],b[15],ol[15],la[15];
int n,m,k,T=10;
int n[] = {};
int m[] = {};
inline void create(reg int id,reg FILE* in){

	for (int t=1;t<=10;t++)
	{
		n=10;
		m=10;
		memset(ol,0,sizeof(ol));
		memset(la,0,sizeof(la));
		ol[5]=ol[10]=2;
		la[5]=la[10]=2;
		for (int i=1;i<=n;i++)
		{
			a[i]=myrand(1,13);
			while (ol[a[i]]+1>2)
			a[i]=myrand(1,13);
			ol[a[i]]++;
		}
		for (int i=1;i<=m;i++)
		{
			b[i]=myrand(1,13);
			while (la[b[i]]+1>2)
			b[i]=myrand(1,13);
			la[b[i]]++;
		}
	fprintf(in,"%lld %lld\n",n,m);
	for(reg int i=1;i<=n;++i)
	{
		if (a[i]==1)
			fprintf(in,"%c%c",'A',i==n?'\n':' ');
		if (a[i]>=2 && a[i]<=10)
			fprintf(in,"%lld%c",a[i],i==n?'\n':' ');
		if (a[i]==11)
			fprintf(in,"%c%c",'J',i==n?'\n':' ');
		if (a[i]==12)
			fprintf(in,"%c%c",'Q',i==n?'\n':' ');
		if (a[i]==13)
			fprintf(in,"%c%c",'K',i==n?'\n':' ');
	}
	for(reg int i=1;i<=m;++i)
	{
		if (b[i]==1)
			fprintf(in,"%c%c",'A',i==m?'\n':' ');
		if (b[i]>=2 && b[i]<=10)
			fprintf(in,"%lld%c",b[i],i==m?'\n':' ');
		if (b[i]==11)
			fprintf(in,"%c%c",'J',i==m?'\n':' ');
		if (b[i]==12)
			fprintf(in,"%c%c",'Q',i==m?'\n':' ');
		if (b[i]==13)
			fprintf(in,"%c%c",'K',i==m?'\n':' ');
	}
	}
	fprintf(in,"%lld %lld\n",0ll,0ll);
	/*fprintf(in,"%lld %lld\n",n,q);
	for(reg int i=1;i<=n;++i)
		fprintf(in,"%lld%c",a[i],i==n?'\n':' ');
	for(reg int i=1;i<=q;++i)
		fprintf(in,"%lld %lld %lld\n",type[i],x[i],y[i]);*/
	
	return;
}

signed main(void){
	srand(time(0));

	static char complier[1048576];
	sprintf(complier,"g++ std.cpp -o std -Wall -Wextra -O2");
	system(complier);
	puts("complie successfully.");

	for(reg int id=1;id<=N;++id){
		static char istr[1024];
		static char ostr[1024];
		sprintf(istr,"%s%lld.in",name,id);
		sprintf(ostr,"%s%lld.out",name,id);

		printf("id=%lld :\n",id);

		FILE* in=fopen(istr,"w");
		puts("open file successfully.");
		puts("creating...\n");
		create(id,in);
		puts("created.\n");
		fclose(in);
		puts("close file successfully.");

		puts("solving.");
		static char call[1048576];
		sprintf(call,"./std < %s > %s",istr,ostr);
		system(call);
		
	}
	return 0;
}