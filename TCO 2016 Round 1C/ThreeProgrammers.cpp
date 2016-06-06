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
template<class T> inline T min(T a, T b, T c) {return min(min(a,b),c);}
template<class T> inline T min(T a, T b, T c, T d) {return min(min(a,b),min(c,d));}
template<class T> inline T max(T a, T b, T c) {return max(max(a,b),c);}
template<class T> inline T max(T a, T b, T c, T d) {return max(max(a,b),max(c,d));}
const int INF = 1e9;
const llong INF_LL = 4e18;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*----------------------------------------*/

class ThreeProgrammers {
    public:
    int cnt[3];

    void add(string& s, int id) {
        s += (char)('A' + id);
        cnt[id] --;
    }

    int find_illegal(string s) {
        int last = -1;
        for (int i=0; i<s.length(); i++) {
            if (s[i] == 'B') {
                if (last == -1) last = i;
                else if (i - last <= 1) return i;
                else last = i;
            }
        }
        return -1;
    }

    int find_A(string s, int l) {
        int p = -1;
        for (int i=l; i<s.length(); i++) if (s[i] == 'A') return i;
        return p;
    }

    string solve() {
        string res = "";
        string imp = "impossible";
        for (int i=0; i<cnt[2]-1; i++) {
            res += "C";
            if (cnt[0] && cnt[1]) {
                add(res, 1);
                add(res, 0);
            } else if (cnt[0] >= 2) {
                add(res, 0);
                add(res, 0);
            } else return imp;
        }
        if (cnt[2]) add(res, 2);

        //printf("cur res: %s\n", res.c_str());

        if (cnt[1]) {
            res = "B" + res;
            cnt[1]--;
        }

        int p = 0;
        while (cnt[1]) {
            p = find_A(res, p);
            if (p == -1) break;
            res.insert(++p, "B");
            cnt[1]--;
        }

        while (cnt[1]) add(res, 1);

        //printf("filled B, res: %s\n", res.c_str());

        while (true) {
            int p = find_illegal(res);
            //printf("res: %s p:%d\n", res.c_str(), p);
            if (p == -1) break;
            if (cnt[0]) {
                res.insert(p, "A");
                cnt[0]--;
            //    printf("insert A, p:%d res: %s\n", p, res.c_str());
            }
            else return imp;
        }
        while (cnt[0]) add(res, 0);
        return res;
    }

    string validCodeHistory(string code) {
        memset(cnt, 0, sizeof(cnt));
        for (char c: code) cnt[c-'A']++;
        string ans = solve();
        return ans;
    }
};

// CUT begin
ifstream data("ThreeProgrammers.sample");

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

bool do_test(string code, string __expected) {
    time_t startClock = clock();
    ThreeProgrammers *instance = new ThreeProgrammers();
    string __result = instance->validCodeHistory(code);
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
        string code;
        from_stream(code);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(code, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1465169796;
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
        cout << "ThreeProgrammers (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
