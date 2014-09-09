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

class BuildingRoutes {
public:
	int build(vector <string>, int);
};
#define maxn 55
int sp[maxn][maxn], cnt[maxn][maxn];

int BuildingRoutes::build(vector <string> dist, int T) {
	int n = dist.size();
	memset(cnt, 0, sizeof(cnt));
	
	for (int i=0; i<n; i++ ) 
	for (int j=0; j<n; j++ ) sp[i][j] = dist[i][j]-'0';
	
	for (int k=0; k<n; k++ )
	for (int i=0; i<n; i++ )
	for (int j=0; j<n; j++ ) {
		if (sp[i][j]>sp[i][k]+sp[k][j]) {
			sp[i][j] = sp[i][k] + sp[k][j];
		}
	}
	
	for (int i=0; i<n; i++ )
	for (int j=0; j<n; j++ ) if (j!=i)
	for (int k=0; k<n; k++ ) 
	for (int x=0; x<n; x++ ) {
		if (sp[k][i] + dist[i][j]-'0' + sp[j][x] == sp[k][x]) cnt[i][j]++;
	}
	int ans = 0;
	for (int i=0; i<n; i++ ) for (int j=0; j<n; j++ ) if (cnt[i][j]>=T) ans += dist[i][j]-'0';
	return ans;
}
