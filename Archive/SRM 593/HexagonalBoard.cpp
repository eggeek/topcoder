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
int dx[] = {-1, -1, 0, 0, 1, 1};
int dy[] = {0, 1, -1, 1, -1, 0};
/*----------------------------------------*/
class HexagonalBoard {
    public:

    vi e[2501];
    int col[2501];

    void build_graph(vector<string>& board) {
      int n = board.size();
      for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) if (board[i][j] == 'X') {
          for (int k=0; k<6; k++) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x < 0 || x >= n || y < 0 || y >= n) continue;
            if (board[x][y] != 'X') continue;
              e[i * n + j].push_back(x * n + y);
          }
        }
      }
    }

    bool dfs(int id, int c) {
      col[id] = c;
      for (int i: e[id]) {
        if (col[i] == -1) {
          if (dfs(i, 1 - c)) return true;
        }
        else if (col[i] == c) return true;
      }
      return false;
    }

    int minColors(vector<string> board) {
        build_graph(board);
        int n = board.size();
        memset(col, -1, sizeof(col));
        for (int i=0; i<n; i++) {
          for (int j=0; j<n; j++) if (board[i][j] == 'X' && col[i * n + j] == -1) {
            if (dfs(i * n + j, 0)) return 3;
          }
        }
        for (int i=0; i<n; i++)
          for (int j=0; j<n; j++) if (e[i*n + j].size() > 0) return 2;
        for (int i=0; i<n; i++)
          for (int j=0; j<n; j++) if (board[i][j] == 'X') return 1;
        return 0;
    }
};

// CUT begin
ifstream data("HexagonalBoard.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    HexagonalBoard *instance = new HexagonalBoard();
    int __result = instance->minColors(board);
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
        vector<string> board;
        from_stream(board);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468044387;
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
        cout << "HexagonalBoard (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
