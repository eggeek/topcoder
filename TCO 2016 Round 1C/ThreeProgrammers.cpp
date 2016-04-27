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
string str[28][51][51][51];
int cnt[3];

string to_str(int msk) {
    string x = "";
    x = 'A' + msk / 9; msk %= 9;
    x += 'A' + msk / 3; msk %= 3;
    x += 'A' + msk;
    return x;
}

bool possible(int msk) {
    string x = to_str(msk);
    //printf("is possible msk:%d str:%s ", msk, x.c_str());
    bool res = true;
    for (int i=0; i<3; i++) {
        if (x[i] == 'A') continue;
        if (x[i] == 'B') {
            if (i+1<3 && x[i+1] == 'B') {
                res = false;
                break;
            }
        }
        if (x[i] == 'C') {
            if (i+1<3 && x[i+1] == 'C') {
                res = false;
                break;
            }
            if (i+2<3 && x[i+2] == 'C') {
                res = false;
                break;
            }
        }
    }
    //printf("res: %s\n", res? "true": "false");
    return res;
}

int dfs(int msk, int a, int b, int c) {
    if (a == 0 && b == 0 && c == 0) {
        str[msk][a][b][c] = "";
        //printf("get ans msk:%s a:%d b:%d c:%d ans:%s\n", to_str(msk).c_str(), a, b, c, str[msk][a][b][c].c_str());
        return 1;
    }
    if (str[msk][a][b][c] != "0") return 0;

    // put a
    if (a) {
        int new_msk = (msk % 9) * 3;
        if (possible(new_msk)) {
            if (dfs(new_msk, a-1, b, c)) {
                str[msk][a][b][c] = 'A' + str[new_msk][a-1][b][c];
                //printf("get ans msk:%s a:%d b:%d c:%d ans:%s\n", to_str(msk).c_str(), a, b, c, str[msk][a][b][c].c_str());
                return 1;
            }
        }
    }

    if (b) {
        int new_msk = (msk % 9) * 3 + 1;
        if (possible(new_msk)) {
            if (dfs(new_msk, a, b-1, c)) {
                str[msk][a][b][c] = 'B' + str[new_msk][a][b-1][c];
                //printf("get ans msk:%s a:%d b:%d c:%d ans:%s\n", to_str(msk).c_str(), a, b, c, str[msk][a][b][c].c_str());
                return 1;
            }
        }
    }

    if (c) {
        int new_msk = (msk % 9) * 3 + 2;
        if (possible(new_msk)) {
            if (dfs(new_msk, a, b, c-1)) {
                str[msk][a][b][c] = 'C' + str[new_msk][a][b][c-1];
                //printf("get ans msk:%s a:%d b:%d c:%d ans:%s\n", to_str(msk).c_str(), a, b, c, str[msk][a][b][c].c_str());
                return 1;
            }
        }
    }
    str[msk][a][b][c] = "impossible";
    return 0;
}

class ThreeProgrammers {
    public:
    string validCodeHistory(string code) {
        if (SZ(code) < 3) {
            if (code == "BB") return "impossible";
            if (code == "CC") return "impossible";
            return code;
        }
        for (int i=0; i<28; i++) {
            for (int j=0; j<=50; j++)
                for (int k=0; k<=50; k++)
                    for (int r=0; r<=50; r++)
                        str[i][j][k][r] = "0";
        }
        memset(cnt, 0, sizeof(cnt));
        for (auto i: code) {
            cnt[i - 'A'] ++;
        }
        bool flag = false;
        for (int i=0; i<3; i++) if (cnt[i] - 1 >= 0){
            cnt[i]--;
            for (int j=0; j<3; j++) if (cnt[j] - 1 >= 0){
                cnt[j]--;
                for (int k=0; k<3; k++) if (cnt[k] - 1 >= 0){
                    cnt[k]--;
                    int msk = i*9 + j * 3 + k;
                    if (possible(msk)) {
                        flag = dfs(msk, cnt[0], cnt[1], cnt[2]);
                        if (flag) {
                            string res = to_str(msk) + str[msk][cnt[0]][cnt[1]][cnt[2]];
                            return res;
                        }
                    }
                    cnt[k]++;
                }
                cnt[j]++;
            }
            cnt[i]++;
        }
        return "impossible";
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
        int T = time(NULL) - 1461755775;
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
