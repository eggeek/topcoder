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

class BuildingHeights {
public:
	int minimum(vector <int>);
};

int getvar(int m,vector<int> h) {
	int ans = 1e9, cur = 0;
	for (int i=0; i<m; i++ ) {
		cur += h[m-1]-h[i];
	}
	ans = cur;
	for (int i=m; i<h.size(); i++ ) {
		cur -= h[i-1] - h[i-m];
		cur += (h[i] - h[i-1]) * (m-1);
		ans = min(ans,cur);
	}
	return ans;
}

int BuildingHeights::minimum(vector <int> h) {
	int ans = 0;
	sort(h.begin(), h.end());
	for (int i=1; i<=h.size(); i++ ) {
		int res = getvar(i,h);
		ans ^= res;
	}
	return ans;
}
