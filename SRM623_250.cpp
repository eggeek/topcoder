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

class UniformBoard {
public:
	int getBoard(vector <string>, int);
};
int n,ept,tota,totp;

int getvar(vector<string> board, int k, int xi, int xj, int yi, int yj) {
	int cnta = 0, cntp = 0, cnte = 0;
	for (int i=xi; i<=yi; i++ ) {
		for (int j=xj; j<=yj; j++ ) {
			if (board[i][j] == 'A') cnta ++;
			if (board[i][j] == 'P') cntp ++;
			if (board[i][j] == '.') cnte ++;
		}
	}
	if (ept==0) {
		if (cntp==0) return cnta;
		else return 0;
	} else {
		int needa = cntp + cnte;
		int exa = tota - cnta;
		if (exa < needa) return 0;
		if (cntp*2+cnte > k) return 0;
		return (cnta+cntp+cnte);
	}
}

int UniformBoard::getBoard(vector <string> board, int K) {
	n = board.size();
	int ans = 0;
	ept = 0;
	for (int i=0; i<n; i++ ) {
		for (int j=0; j<n; j++ ) {
			if (board[i][j]=='.') ept++;
			if (board[i][j]=='A') tota++;
			if (board[i][j]=='P') totp++;
		}
	}
	for (int xi=0; xi<n; xi++ ) {
		for (int xj=0; xj<n; xj++ ) {
			for (int yi=xi; yi<n; yi++ ) {
				for (int yj=xj; yj<n; yj++ ) {
					int res = getvar(board, K, xi, xj, yi, yj);
					ans = max(ans, res);	
				}
			}
		}
	}
	return ans;
}
