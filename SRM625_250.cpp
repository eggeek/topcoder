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
typedef long long llong;
class PalindromePermutations {
public:
	double palindromeProbability(string);
};

int cnt[27];
llong c[51][51];

double PalindromePermutations::palindromeProbability(string word) {
	for (int i=0; i<word.size(); i++ ) cnt[word[i]-'a'] ++;
	int odd = 0;
	for (int i=0; i<26; i++ ) if (cnt[i] % 2) odd ++;
	
	if ((odd + word.size())%2 || odd>1) return 0;
	
	c[0][0] = 1;
	for (int i=1; i<51; i++ ) {
		for (int j=0; j<=i; j++ ) {
			c[i][j] = j==0?1:c[i-1][j-1] + c[i-1][j];
		}
	}
	
	double ans = 1.0;
	int n = word.size();
	
	for (int i=0; i<26; i++ ) if (cnt[i]) {
		int m = cnt[i];
		double tmp = (double)c[n/2][m/2] / (double)c[n][m];
		ans  *= (double)c[n/2][m/2] / (double)c[n][m];
		n -= m;
	}
	return ans;
}
