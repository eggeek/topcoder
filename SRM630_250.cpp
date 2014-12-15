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

class Egalitarianism3 {
public:
	int maxCities(int, vector <int>, vector <int>, vector <int>);
};
vector<int> e[55];
int d[55][55];

void dfs(int cur, int fa, int len, vector<int> &v) {
	v.push_back(len);
	for (int i=0; i<(int)e[cur].size(); i++ ) if (e[cur][i]!=fa) { printf("root:%d son:%d\n",cur , e[cur][i]);
		dfs(e[cur][i], cur, len+d[cur][e[cur][i]], v);
	}
}

int Egalitarianism3::maxCities(int n, vector <int> a, vector <int> b, vector <int> len) {
	for (int i=0; i<n-1; i++ ) {
		e[a[i]].push_back(b[i]);
		e[b[i]].push_back(a[i]);
		d[a[i]][b[i]] = d[b[i]][a[i]] = len[i];
	}
	int ans = min(n, 2);
	for (int i=1; i<=n; i++ ) {
		vector<int> v;
		map<int, int> tot;
		map<int, int> ha;
		for (int j=0; j<(int)e[i].size(); j++ ) {
			v.clear();
			ha.clear();
			dfs(e[i][j], i, d[i][e[i][j]], v);
			for (int k=0; k<(int)v.size(); k++) { printf("root:%d v:%d\n",i, v[k]);
				if (ha[v[k]]) continue;
				ha[v[k]] = 1;
				tot[v[k]] += 1;
				ans = max(ans, tot[v[k]]);
			}       
		}
	}
	return ans;
}
