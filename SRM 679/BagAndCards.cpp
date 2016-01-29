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
const llong MOD = 1e9 + 7L;
const double pi = acos(-1.0);
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
/*----------------------------------------*/
#define maxn 555
#define maxm 1001
llong sum[maxn][maxn];
llong cnt[maxn][maxn];

class BagAndCards {
    public:
        void init(int n, int m, llong x, llong a, llong b, llong c, string isGood) {
            for (int i=0; i<n; i++) {
                for (int j=0; j<m; j++) {
                    cnt[i][j] = x;
                    x = ((x * a + b) ^ c) % MOD;
                }
            }
            memset(sum, 0, sizeof(sum));
            for (int i=0; i<n; i++) {
                for (int j=0; j<m; j++) {
                    for (int k=0; k<m; k++) if (isGood[j+k] == 'Y') {
                        sum[i][k] = (sum[i][k] + cnt[i][j]) % MOD;
                    }
                }
            }
        }

        llong calc(int i, int j, int m) {
            llong ans = 0;
            for (int k=0; k<m; k++) {
                ans += sum[i][k] * cnt[j][k] % MOD;
                if (ans >= MOD) ans %= MOD;
            }
            return ans % MOD;
        }

        int getHash(int n, int m, int x, int a, int b, int c, string isGood) {
            init(n, m, x, a, b, c, isGood);
            llong ans = 0;
            for (int i=0; i<n; i++) {
                for (int j=i+1; j<n; j++) {
                    llong tmp = calc(i, j , m);
                    ans ^= tmp;
                }
            }
            return ans;
        }
};

// CUT begin
ifstream data("BagAndCards.sample");

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

bool do_test(int n, int m, int x, int a, int b, int c, string isGood, int __expected) {
    time_t startClock = clock();
    BagAndCards *instance = new BagAndCards();
    int __result = instance->getHash(n, m, x, a, b, c, isGood);
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
        int m;
        from_stream(m);
        int x;
        from_stream(x);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        int c;
        from_stream(c);
        string isGood;
        from_stream(isGood);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, m, x, a, b, c, isGood, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1454036850;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BagAndCards (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
