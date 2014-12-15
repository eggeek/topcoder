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

class RectangleCovering {
public:
	int minimumNumber(int, int, vector <int>, vector <int>);
};

bool cmp(int a, int b) { return a > b;}

int RectangleCovering::minimumNumber(int h, int w, vector <int> bh, vector <int> bw) {
	int n = bh.size();
	vector<int> p, q;
	for (int i=0; i<n; i++ ) {
		int a = bh[i], b = bw[i];
		if (a < b) swap(a, b);
		
		if (b > h) p.push_back(a);
		else if (a > h) p.push_back(b);
		
		if (b > w) q.push_back(a);
		else if (a > w) q.push_back(b);
	}
	sort(p.begin(), p.end(), cmp);
	sort(q.begin(), q.end(), cmp);
	
	int ans = -1, cntp = 0, cntq = 0, ansp = 0, ansq = 0;
	
	for (int i=0; i<(int)p.size(); i++ ) { printf("p %d\n", p[i]);
		cntp += p[i];
		ansp ++;
		if (cntp >= w) break;
	}
	if (cntp >= w) ans = ansp;
	for (int i=0; i<(int)q.size(); i++ ) { printf("q %d\n", q[i]);
		cntq += q[i];
		ansq ++;
		if (cntq >= h) break;
	}
	if (cntq >= h) {
		ans = ans==-1?ansq:min(ans, ansq);
	}
	return ans;
}
