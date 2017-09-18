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
bool vis[55];
vector<int> e[55];

void add_edge(int u, int v) {
  vis[u] = true; vis[v] = true;
  e[u].push_back(v);
  e[v].push_back(u);
  printf("add edge(%d, %d)\n", u, v);
}

int find_d(int dis, vector<int> d) {
  for (int i=0; i<SZ(d); i++) if (!vis[i] && d[i] == dis) return i;
  return -1;
}

void dfs(int cur, int h, vector<int> d) {
  int v;
  if (h == 0) return;
  while ((v = find_d(d[cur]+1, d)) != -1) add_edge(cur, v);
  for (int i: e[cur]) if (d[i] == d[cur]+1) dfs(i, h-1, d);
}

void dfs_ans(int cur, int pre, vector<int>& ans) {
  for (int i: e[cur]) if (i != pre) {
    ans.push_back(cur);
    ans.push_back(i);
    dfs_ans(i, cur, ans);
  }
}

class TreeDistanceConstruction {
    public:
    vi ans;
    vector<int> construct(vector<int> d) {
      int cnt = 0, minD = 55, u, v;
      for (int i: d) minD = min(minD, i);
      for (int i: d) if (i == minD) cnt++;
      if (cnt > 2) return vector<int>();
      if (cnt == 1) {
        int minArg = -1;
        for (int i=0; i < SZ(d); i++) if (d[i] == minD) minArg = i;
        u = minArg;
        for (int i=1; i<=minD; i++) {
          int v = find_d(d[u]+1, d);
          if (v == -1) return vector<int>();
          add_edge(u, v);
          u = v;
        }
        u = minArg;
        for (int i=1; i<=minD; i++) {
          v = find_d(d[u]+1, d);
          if (v == -1) return vector<int>();
          add_edge(u, v);
          u = v;
        }
        assert(minArg != -1);
        dfs(minArg, minD, d);
        for (int i=0; i<SZ(d); i++) if (!vis[i]) return vector<int>();
        dfs_ans(minArg, -1, ans);
        return ans;
      } else {
        int minArg1 = -1, minArg2 = -1;
        for (int i=0; i < SZ(d); i++) if (d[i] == minD) {
          minArg1 = i;
          break;
        }
        for (int i=minArg1+1; i<SZ(d); i++) if (d[i] == minD) {
          minArg2 = i;
          break;
        }
        u = minArg1;
        for (int i=1; i<=minD-1; i++) {
          v = find_d(d[u]+1, d);
          if (v == -1) return vector<int>();
          add_edge(u, v);
          u = v;
        }
        u = minArg2;
        for (int i=1; i<=minD-1; i++) {
          v = find_d(d[u]+1, d);
          if (v == -1) return vector<int>();
          add_edge(u, v);
          u = v;
        }
        assert(minArg1 != -1);
        assert(minArg2 != -1);
        add_edge(minArg1, minArg2);
        dfs(minArg1, minD-1, d);
        for (int i=0; i<SZ(d); i++) if (!vis[i]) return vector<int>();
        dfs_ans(minArg1, -1, ans);
        return ans;
      }
    }
};

// CUT begin
ifstream data("TreeDistanceConstruction.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(vector<int> d, vector<int> __expected) {
    time_t startClock = clock();
    TreeDistanceConstruction *instance = new TreeDistanceConstruction();
    vector<int> __result = instance->construct(d);
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
        vector<int> d;
        from_stream(d);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1484179534;
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
        cout << "TreeDistanceConstruction (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
