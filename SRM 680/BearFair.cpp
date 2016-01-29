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
const int INF = 1e9;
const llong INF_LL = 4e18;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
#define maxn 55

struct Query {
    int up, quan;
}query[maxn];
int q;

bool cmp(Query a, Query b) {
    if (a.up == b.up) return a.quan < b.quan;
    return a.up < b.up;
}

string solve(int n) {
    string unf = "unfair";
    string fai = "fair";
    int maxodd=0, maxeven=0, minodd=0, mineven=0;
    for (int i=0; i<=q; i++) {
        int l, r, cnt;
        if (i == 0) {
            l = 1;
            r = query[i].up;
            cnt = query[i].quan;
        }
        else {
          l = query[i-1].up + 1;
          r = query[i].up;
          cnt = query[i].quan - query[i-1].quan;
        }
        if (r-l+1 < cnt) return unf;
        if (l > r && cnt) return unf;
        if (cnt < 0) return unf;
        if (query[i].quan > n) return unf;
        int cnt_odd = 0, cnt_even = 0;
        for (int j=l; j<=r; j++) {
            if (j%2) cnt_odd++;
            else cnt_even++;
        }
        cnt_odd = min(cnt_odd, cnt);
        cnt_even = min(cnt_even, cnt);
        maxodd += cnt_odd;
        minodd += cnt - cnt_even;
        maxeven += cnt_even;
        mineven += cnt - cnt_odd;
    }
    if (n/2 >= minodd && n/2 <= maxodd && n/2 >= mineven && n/2 <= maxeven) return fai;
    return unf;
}

class BearFair {
    public:
    string isFair(int n, int b, vector<int> upTo, vector<int> quantity) {
        q = SZ(upTo);
        for (int i=0; i<q; i++) query[i] = Query{upTo[i], quantity[i]};
        query[q] = Query{b, n};
        sort(query, query+q+1, cmp);
        string ans = solve(n);
        return ans;
    }
};

// CUT begin
ifstream data("BearFair.sample");

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

bool do_test(int n, int b, vector<int> upTo, vector<int> quantity, string __expected) {
    time_t startClock = clock();
    BearFair *instance = new BearFair();
    string __result = instance->isFair(n, b, upTo, quantity);
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
        int b;
        from_stream(b);
        vector<int> upTo;
        from_stream(upTo);
        vector<int> quantity;
        from_stream(quantity);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, b, upTo, quantity, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1453996925;
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
        cout << "BearFair (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
