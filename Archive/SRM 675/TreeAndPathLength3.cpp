#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;
vector<int> e;

void add(int u, int v) {
    e.push_back(u);
    e.push_back(v);
}

class TreeAndPathLength3 {
    public:
    vector<int> construct(int s) {
        if (s == 1) {
            add(0, 1);
            add(1, 2);
            add(2, 3);
        } else if (s == 2) {
            add(0, 1);
            add(1, 2);
            add(2, 3);
            add(3, 4);
        } else {
            add(0, 1);
            add(1, 2);
            add(0, 3);
            add(3, 4);
            int cur = 5;
            int cnt = 2;
            int k = 2;
            while (s - cnt > 0) {
                if (s - k*(k+1) >= 0) {
                    k += 1;
                    add(0, cur);
                    add(cur, 2*k);
                    cur += 2;
                    cnt = k * (k-1);
                } else {
                    if (s - cnt >= k) {
                        add(0, cur);
                        cur ++;
                        cnt += k;
                    }
                    for (int i=1; i<=k && s-cnt>0; i++) {
                        add(2*k, cur++);
                        cnt ++;
                    }
                    break;
                }
            }
        }
        return e;
    }
};

// CUT begin
ifstream data("TreeAndPathLength3.sample");

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

bool do_test(int s, vector<int> __expected) {
    time_t startClock = clock();
    TreeAndPathLength3 *instance = new TreeAndPathLength3();
    vector<int> __result = instance->construct(s);
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
        int s;
        from_stream(s);
        next_line();
        vector<int> __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1449748804;
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
        cout << "TreeAndPathLength3 (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
