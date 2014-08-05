#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class DivisorsPower {
public:
	long long findArgument(long long);
};
long long check(long long m,long long p,long long n) {
	long long res = 1;
	while (p) {
		if (p%2) {
			if (res/1e18 * m > 1) return 1;
			res *= m;
		}
		p>>=1;
		if (m / 1e18 * m > 1) {
			if (p) return 1;
			else break;
		}
		m *= m;
	}
	return res-n;
}

long long getroot(long long m,long long p) {
	long long l = max( (long long)(pow(m,1.0/(double)p))-1 , 1ll);
	long long r = (long long)pow(m,1.0/(double)p) + 2;
	
	while (l<r) {
		long long mid = (l+r)/2ll;
		long long t = check(mid,p,m);
		if (t<0) l=mid;
		else if (t>0) r=mid;
		else if (t==0) return mid;
		if (l+1>=r) {
			if (check(l,p,m)==0) return l;
			if (check(r,p,m)==0) return r;
			return -1;
		}
	}
	return -1;
}

long long getdx(long long n) {
	long long ans = 0;
	for (long long i=1; i*i<=n; i++ ) if (n%i==0) {
		long long j = n/i;
		if (i<j) ans += 2;
		else if (i==j) {ans ++; break;}
		else break;
	}
	return ans;
}

long long getvar(long long m,long long p) {
	long long n = getroot(m,p);
	if (n==-1) return -1;
	long long dx = getdx(n);
	if (dx == p ) return n;
	else return -1;
}

long long DivisorsPower::findArgument(long long n) {

	long long ans = -1;
	for (int i=2; i<60; i++ ) {
		long long x = getvar(n,i);
		if (x!=-1 && (ans==-1 || ans>x)) ans = x;
	}
	return ans;
}
