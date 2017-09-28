#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <random>
#include <cmath>
#include <ctime>
#include <functional>
#include <algorithm>
#include <complex>
#include <numeric>
#include <limits>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <map>
#include <set>

using namespace std;
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define MP(x, y) make_pair((x),(y))
#define x first
#define y second
#define LOWB(x) (x & (-x))
#define UNIQUE(a) sort(ALL(a)), (a).erase(unique(ALL(a)), (a).end())
#define HEIGHT(n) (sizeof(int) * 8 - __builtin_clz(n)) //height of range n segment tree
#ifndef ONLINE_JUDGE
#define dbg(x) cerr << #x << " = " << x << endl;
#else
#define dbg(x)
#endif
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<class T> inline T min(T a, T b, T c) {return min(min(a,b),c);}
template<class T> inline T min(T a, T b, T c, T d) {return min(min(a,b),min(c,d));}
template<class T> inline T max(T a, T b, T c) {return max(max(a,b),c);}
template<class T> inline T max(T a, T b, T c, T d) {return max(max(a,b),max(c,d));}
const int INF = 1e9;
const ll INF_LL = 4e18;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*----------------------------------------*/
//yoyo

class WolvesAndSheep {
    public:
    int n, m;
    int check[16][16][16][2];
    vi row, dp, col;

    bool checkCol(int u, int b, int c, char ch, vector<string> &f) {
      if (check[u][b][c][ch == 'W'] != -1) return check[u][b][c][ch == 'W'];
      if (c >= m) return false;
      for (int i=u; i<=b; i++) if (f[i][c] == ch) return true;
      return false;
    }

    int solve(int mask, vector<string> &f) {
      fill(ALL(row), 0);
      fill(ALL(col), 0);
      fill(ALL(dp), 0);
      for (int i=0; i<n; i++) if (mask & (1<<i)) row[i] = 1;
      for (int i=0; i<n; i++) {
        int j = i;
        while (j+1 < n && !row[j]) j++;
        for (int k=0; k<m; k++) {
          if (checkCol(i, j, k, 'S', f) && checkCol(i, j, k, 'W', f)) return n + m;
          if (checkCol(i, j, k, 'S', f)) {
            for (int x=k-1; x>=0; x--) if (checkCol(i, j, x, 'W', f)) {
              col[k] = max(col[k], x+1);
              break;
            }
          } else if (checkCol(i, j, k, 'W', f)) {
            for (int x=k-1; x>=0; x--) if (checkCol(i, j, x, 'S', f)) {
              col[k] = max(col[k], x+1);
            }
          }
        }
        i = j;
      }
      for (int i=1; i<m; i++) col[i] = max(col[i], col[i-1]);
      dp[0] = 0;
      for (int i=1; i<m; i++) {
        if (col[i] == 0) dp[i] = 0;
        else {
          dp[i] = dp[i-1] + 1;
          for (int j=i-1; j>=col[i]; j--) dp[i] = min(dp[i], dp[j-1] + 1);
        }
      }
      int res = dp[m-1];
      for (int i=0; i<n; i++) res += row[i];
      return res;
    }

    void init(vector<string> &f) {
      memset(check, -1, sizeof(check));
      for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
          for (int k=0; k<m; k++) {
            check[i][j][k][0] = checkCol(i, j, k, 'S', f);
            check[i][j][k][1] = checkCol(i, j, k, 'W', f);
          }
        }
      }
    }

    int getmin(vector<string> f) {
        n = (int)f.size();
        m = (int)f[0].size();
        init(f);
        row.resize(n);
        dp.resize(m);
        col.resize(m);
        int ans = n + m;
        for (int i=0; i<(1<<(n-1)); i++) {
          ans = min(ans, solve(i, f));
        }
        return ans;
    }
};

// CUT begin
ifstream data("WolvesAndSheep.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<string> field, int __expected) {
    time_t startClock = clock();
    WolvesAndSheep *instance = new WolvesAndSheep();
    int __result = instance->getmin(field);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<string> field;
        from_stream(field);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(field, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1506602629;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "WolvesAndSheep (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
