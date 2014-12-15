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

class TaroJiroGrid {
public:
	int getNumber(vector <string>);
};

int n;

int checkcol(vector<string> g, int c) {
	int cnt = 0;
	for (int i=0; i<n; i++ ) {
		if (i==0 || g[i][c]==g[i-1][c]) cnt++;
		else cnt = 1;
		if (cnt>n/2) return 0;
	}
	return 1;
}

int check(vector<string> g) {
	for (int i=0; i<n; i++ ) if (!checkcol(g, i)) return 0;
	return 1;
}

vector<string> operate(vector<string> g, int row, int op) {
	vector<string> res;
	for (int i=0; i<n; i++ ) res.push_back(g[i]);
	for (int i=0; i<n; i++ ) {
		if (op == 0 && res[row][i]=='B') res[row][i]='W';
		else if (op==1 && res[row][i]=='W') res[row][i]='B';
	}
	return res;
}

int TaroJiroGrid::getNumber(vector <string> g) {
	n = g.size();
	if (check(g)) return 0;
	for (int i=0; i<n; i++ ) {
		vector<string> x;
		x = operate(g, i, 0);
		if (check(x)) return 1;
		x = operate(g, i, 1);
		if (check(x)) return 1;
	}
	return 2;
	for (int i=0; i<n; i++ ) {
		for (int j=i+1; j<n; j++ ) {
			for (int k=0; k<2; k++ ) {
				for (int r=0; r<2; r++ ) {
					vector<string> x;
					x = operate(g, i, k);
					x = operate(x, j, r);
					if (check(x)) return 2;
				}
			}
		}
	}
}
