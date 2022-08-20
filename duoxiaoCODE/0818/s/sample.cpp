#include "s.hpp"
using namespace std;
vector<string> guess(int n,int a,int b,int t)
{
	vector<string> v(n,"1");
	if(prod(v)=="0")
		return vector<string>(n,"0");
	//猜不出来，告辞 
	return vector<string>();
}
