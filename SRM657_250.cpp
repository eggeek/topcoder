#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class HappyLetterDiv1 {
public:
	string getHappyLetters(string);
};
int cnt[30];

int check(char c) {
	int cnt2[30];
	printf("char %c\n",c);
	for (int i=0; i<30; i++ ) cnt2[i] = cnt[i];
	int cur = 0, cut = 0, sum = 0;
	for (int i=0; i<26; i++ ) if (cnt2[i] && i+'a'!=c) {
		if (cur==0) cur = cnt2[i], cut = 0;
		else {
			if (cnt2[i]==cur) {
				sum += cur*2;
				cur = cut = 0;
			} else if (cnt2[i]>cur) {
				sum += cur*2;
				cut = cur;
				cur = cnt2[i]-cur;
			} else {
				sum += cnt2[i]*2;
				cut += cnt2[i];
				cur -= cnt2[i]; 
			}
			}
		}
		printf("%c%d cur:%d cut:%d sum:%d\n",i+'a',cnt2[i],cur,cut,sum);
	}
	int t = min(sum - cut*2, (sum-2*cut)/2);
	int x = (t>=cur/2)?cur/2:t;
	printf("t:%d x:%d cur-x:%d\n",t,x,cur-x);
	if (cur-2*x<cnt2[c-'a']) return 1;
	return 0;
}
string HappyLetterDiv1::getHappyLetters(string l) {
	for (int i=0; i<30; i++ ) cnt[i] = 0;
	for (int i=0; i<l.size(); i++ ) cnt[l[i]-'a'] ++;
	string ans = "";
	for (int i=0; i<26; i++ ) if (cnt[i] && check(i+'a')) ans += i+'a';
	return ans;
}
