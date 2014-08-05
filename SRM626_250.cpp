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
#include <cstring>
using namespace std;

class FixedDiceGameDiv1 {
public:
	double getExpectation(int, int, int, int);
};

double pa[52][2550], pb[52][2550], suma[2550], sumb[2550];

double FixedDiceGameDiv1::getExpectation(int a, int b, int c, int d) {
	memset(pa, 0, sizeof(pa));
	memset(pb, 0, sizeof(pb));
	memset(suma, 0, sizeof(suma));
	memset(sumb, 0, sizeof(sumb));
	
	pa[0][0] = 1.0;
	pb[0][0] = 1.0;
	
	for (int i=0; i<a; i++ ) {
		for (int j=0; j<=a*b; j++ ) {
			for (int k=1; k<=b; k++ ) pa[i+1][j+k] += pa[i][j]/(double)b;
		}
	}	
	
	for (int i=0; i<c; i++ ) {
		for (int j=0; j<=c*d; j++ ) {
			for (int k=1; k<=d; k++ ) pb[i+1][j+k] += pb[i][j]/(double)d;
		}
	}	

	for (int i=1; i<=max(a*b,c*d); i++ ) suma[i] = suma[i-1] + pa[a][i];
	for (int i=1; i<=max(a*b,c*d); i++ ) sumb[i] = sumb[i-1] + pb[c][i];
	double win = 0.0;
	for (int i=a; i<=a*b; i++) {
		win += pa[a][i] * sumb[i-1];
	}
	if (win<=0.0) return -1.0;
	double ans = 0.0;
	for (int i=a; i<=a*b; i++ ) {
		ans += i * pa[a][i] * sumb[i-1] / win;
	}
	return ans;
}
