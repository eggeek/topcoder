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
#define FI first
#define SE second
#define LOWB(x) (x & (-x))
#define UNIQUE(a) sort(ALL(a)), (a).erase(unique(ALL(a)), (a).end())
#define HEIGHT(n) (sizeof(int) * 8 - __builtin_clz(n)) //height of range n segment tree
typedef long long llong;
typedef pair<int, int> pii;
typedef vector<int> vi;
template<class T> inline T min(T a, T b, T c) {return min(min(a,b),c);}
template<class T> inline T min(T a, T b, T c, T d) {return min(min(a,b),min(c,d));}
template<class T> inline T max(T a, T b, T c) {return max(max(a,b),c);}
template<class T> inline T max(T a, T b, T c, T d) {return max(max(a,b),max(c,d));}
const int INF = 1e9 + 7;
const llong MOD = 1e9 + 7;
const llong INF_LL = 4e18;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
#define maxn 100010
llong t[maxn<<1];

class TheEmpireStrikesBack {
    public:
    vector<pair<int, int>> p, seq;

    bool check(llong t, int m) {
        int cnt = 0;
        for (int i=0; i<SZ(seq); i++) {
            int j = i;
            llong h = seq[i].SE;
            while (j+1 < SZ(seq) && seq[i].FI - seq[j+1].FI <= t) {
                h = max(h, (llong)seq[j+1].SE);
                j++;
            }
            cnt++;
            while (j+1 < SZ(seq) && seq[j+1].SE <= h + t) j++;
            i = j;
        }
        return cnt <= m;
    }

    int bsearch(int M) {
        llong l = 0, r = INF;
        while (l < r) {
            llong mid = (l + r) >> 1L;
            if (check(mid, M)) r = mid;
            else l = mid;
            if (l + 1 >= r) {
                if (check(l, M)) return l;
                return r;
            }
        }
        return r;
    }

    int find(int AX, int BX, int CX, int AY, int BY, int CY, int N, int M) {
        llong x = AX, y = AY;
        for (int i=0; i<N; i++) {
            p.push_back(MP(x, y));
            x = (x * (llong)BX + CX) % MOD;
            y = (y * (llong)BY + CY) % MOD;
        }
        auto cmp = [] (pair<int, int> a, pair<int, int> b) {
            if (a.FI== b.FI) return a.SE> b.SE;
            else return a.FI > b.FI;
        };
        sort(ALL(p), cmp);
        for (int i=0; i<SZ(p); i++) {
            if (!SZ(seq)) seq.push_back(p[i]);
            else if (p[i].SE > seq[SZ(seq)-1].SE) {
                seq.push_back(p[i]);
            }
        }
        int ans = bsearch(M);
        return ans;
    }
};

// CUT begin
ifstream data("TheEmpireStrikesBack.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int AX, int BX, int CX, int AY, int BY, int CY, int N, int M, int __expected) {
    time_t startClock = clock();
    TheEmpireStrikesBack *instance = new TheEmpireStrikesBack();
    int __result = instance->find(AX, BX, CX, AY, BY, CY, N, M);
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
        int AX;
        from_stream(AX);
        int BX;
        from_stream(BX);
        int CX;
        from_stream(CX);
        int AY;
        from_stream(AY);
        int BY;
        from_stream(BY);
        int CY;
        from_stream(CY);
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(AX, BX, CX, AY, BY, CY, N, M, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1452675452;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TheEmpireStrikesBack (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
