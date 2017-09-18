#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <cassert>
#include <fstream>

using namespace std;
typedef long long llong;
const int maxn = 5000000;
const int maxm = 31623;
const llong MOD = 1000000007;
int c[maxm], c2[maxm];
llong block_sz;

class LimitedMemorySeries1 {
    public:

    llong getVar(int idx, int q, llong x0, llong a, llong b, int n) {
        int cnt = 0;
        memset(c2, 0, sizeof(c2));
        if (x0>=(llong)idx*block_sz && x0<(llong)(idx+1)*block_sz) {
            c2[x0-(llong)idx*block_sz]++;
            cnt++;
        }
        for (int i=1; i<n; i++) {
            llong x1 = (long long)(x0*a + b) % MOD;
            x0 = x1;
            if (x0>=(llong)idx*block_sz && x0<(llong)(idx+1)*block_sz) {
                c2[x0-(llong)idx*block_sz]++;
                cnt++;
            }
            if (cnt == c[idx]) break;
        }
        for (int i=0; i<block_sz; i++) {
             if (q-c2[i]>=0) q-=c2[i];
             else return i+idx*block_sz;
        }
        return -1;
    }

    long long getSum(int n, int x0, int a, int b, vector<int> query) {
        memset(c, 0, sizeof(c));
        block_sz = MOD / (llong)maxm + ((MOD % maxm)?0:1);
        llong x = x0;
        c[x / block_sz]++;
        for (int i=1; i<n; i++) {
            llong x1 = (long long)(x * a + b) % MOD;
            x = x1;
            c[x / block_sz]++;
        }
        long long ans = 0;
        for (auto q: query) {
             int idx=0;
             while (q-c[idx]>=0) {
                 q -= c[idx];
                 idx++;
             }
             llong val = getVar(idx, q, x0, a, b, n);
             assert(val != -1);
             ans += (long long)val;
        }
        return ans;
    }
};

// CUT begin
ifstream data("LimitedMemorySeries1.sample");

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

bool do_test(int n, int x0, int a, int b, vector<int> query, long long __expected) {
    time_t startClock = clock();
    LimitedMemorySeries1 *instance = new LimitedMemorySeries1();
    long long __result = instance->getSum(n, x0, a, b, query);
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
        int x0;
        from_stream(x0);
        int a;
        from_stream(a);
        int b;
        from_stream(b);
        vector<int> query;
        from_stream(query);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(n, x0, a, b, query, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1450936522;
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
        cout << "LimitedMemorySeries1 (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
