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
#define maxn 51
vector<string> ss;
int sg[maxn][maxn][maxn * maxn + 2];
int n, m;

class BoardEscape {
    public:

    int dfs(int i, int j, int k) {
        set<int> s;
        if (sg[i][j][k] != -1) return sg[i][j][k];
        if (ss[i][j] == 'E') return sg[i][j][k] = 0;
        if (k == 0) return sg[i][j][k] = 0;
        int t;
        if (i+1<n && ss[i+1][j] != '#') {
            t = dfs(i+1, j, k-1);
            s.insert(t);
        }
        if (i-1>=0 && ss[i-1][j] != '#') {
            t = dfs(i-1, j, k-1);
            s.insert(t);
        }
        if (j+1<m && ss[i][j+1] != '#') {
             t = dfs(i, j+1, k-1);
             s.insert(t);
        }
        if (j-1>=0 && ss[i][j-1] != '#') {
            t = dfs(i, j-1, k-1);
            s.insert(t);
        }
        int x=0;
        while (true) {
             if (!s.count(x)) break;
             x++;
        }
        return sg[i][j][k] = x;
    }

    void init_sg() {
        n = int(ss.size());
        m = int(ss[0].size());
        int maxk = maxn*maxn + 2;
        memset(sg, -1, sizeof(sg));
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                for (int k=0; k<maxk; k++) {
                    if (sg[i][j][k] != -1) continue;
                    if (ss[i][j] == '#') continue;
                    dfs(i, j, k);
                }
    }

    string findWinner(vector<string> s, int k) {
        ss = s;
        init_sg();
        int ans = 0;
        int msk=k;
        if (k>=n*m) {
            if (k&1) msk=(n*m+1) | 1;
            else msk=(n*m+1) - (n*m+1) % 2;
        }
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++) {
                 if (ss[i][j] == 'T') ans ^= sg[i][j][msk];
            }
        return ans?"Alice":"Bob";
    }
};

// CUT begin
ifstream data("BoardEscape.sample");

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

bool do_test(vector<string> s, int k, string __expected) {
    time_t startClock = clock();
    BoardEscape *instance = new BoardEscape();
    string __result = instance->findWinner(s, k);
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
        vector<string> s;
        from_stream(s);
        int k;
        from_stream(k);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, k, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1450455410;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "BoardEscape (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
