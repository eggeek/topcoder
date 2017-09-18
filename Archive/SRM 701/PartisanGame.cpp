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
#define N 3628801
int dp[N][2];

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a%b);
}

int sg(int n, int i, vi& a, vi& b) {
  if (n == 0) return false;
  if (dp[n][i] != -1) return dp[n][i];
  if (i) {
    for (int x: b) if (x <= n) {
      if (sg(n-x, 1-i, a, b) == 0) return dp[n][i] = 1;
    }
    return dp[n][i] = 0;
  } else {
    for (int y: a) if (y <= n) {
      if (sg(n-y, 1-i, a, b) == 0) return dp[n][i] = 1;
    }
    return dp[n][i] = 0;
  }
}

int vis[1<<11];
pii find_loop(vi& a, vi& b) {
  memset(vis, -1, sizeof(vis));
  printf("\n");
  int mask = 0;
  for (int i=0; i<10; i++) {
    mask <<= 1;
    mask |= sg(i, 0, a, b);
  }
  vis[mask] = 9;
  for (int i=10; i<(1<<11); i++) {
    mask <<= 1;
    if (mask & (1<<10)) mask -= 1<<10;
    mask |= sg(i, 0, a, b);
    if (vis[mask] != -1) {
      return {i, i-vis[mask]};
    }
    vis[mask] = i;
  }
  assert(false);
  return {-1, -1};
}

class PartisanGame {
    public:
    string getWinner(int n, vector<int> a, vector<int> b) {
      memset(dp, -1, sizeof(dp));
      pii p = find_loop(a, b);
      int pos = p.first;
      int loop = p.second;
      if (n <= pos) {
        if (sg(n, 0, a, b)) return "Alice";
        else return "Bob";
      } else {
        if (sg(pos + (n-pos)%loop, 0, a, b)) return "Alice";
        else return "Bob";
      }
    }
};

// CUT begin
ifstream data("PartisanGame.sample");

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

bool do_test(int n, vector<int> a, vector<int> b, string __expected) {
    time_t startClock = clock();
    PartisanGame *instance = new PartisanGame();
    string __result = instance->getWinner(n, a, b);
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
        int n;
        from_stream(n);
        vector<int> a;
        from_stream(a);
        vector<int> b;
        from_stream(b);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, a, b, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1477534664;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "PartisanGame (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
