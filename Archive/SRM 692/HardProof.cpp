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
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int INF = 1e9;
const llong INF_LL = 4e18;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*----------------------------------------*/
#define N 55

int mp[N][N], n;
bool vis[N];

void dfs0(int p, int sml, int dif) {
    vis[p] = true;
    for (int i=0; i<n; i++) if (!vis[i] && mp[p][i] >= sml && mp[p][i] <= sml + dif) {
        dfs0(i, sml, dif);
    }
}

void dfs1(int p, int sml, int dif) {
    vis[p] = true;
    for (int i=0; i<n; i++) if (!vis[i] && mp[i][p] >= sml && mp[i][p] <= sml + dif) {
        dfs1(i, sml, dif);
    }
}

bool check_first(int a, int b, int dif) {
    int sml = mp[a][b];
    memset(vis, 0, sizeof(vis));
    dfs0(a, sml, dif);
    for (int i=0; i<n; i++) if (!vis[i]) return false;

    memset(vis, 0, sizeof(vis));
    dfs1(a, sml, dif);
    for (int i=0; i<n; i++) if (!vis[i]) return false;

    return true;
}

bool check(int dif) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) if (j != i && check_first(i, j, dif)) return true;
    }
    return false;
}

int bsearch(int l, int r) {
    while (l < r) {
        int m = (l + r) >> 1;
        if (check(m)) r = m;
        else l = m+1;
        if (l + 1 >= r) {
            if (check(l)) return l;
            else return r;
        }
    }
    return l;
}

class HardProof {
    public:
    int minimumCost(vector<int> D) {
        int len = SZ(D), big = 0;
        n = 0;
        while (n * n != len) n++;
        if (n == 1) return 0;

        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                mp[i][j] = D[i*n + j];
                big = max(big, mp[i][j]);
            }
        }

        int ans = bsearch(0, big);
        return ans;
    }
};

// CUT begin
ifstream data("HardProof.sample");

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

bool do_test(vector<int> D, int __expected) {
    time_t startClock = clock();
    HardProof *instance = new HardProof();
    int __result = instance->minimumCost(D);
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
        vector<int> D;
        from_stream(D);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(D, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1465520408;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "HardProof (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
