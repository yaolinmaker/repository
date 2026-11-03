#include <bits/stdc++.h>
using namespace std;
#define in cin
#define out cout

signed main() {
	int t;
	in >> t;
	while (t--) {
		string s; 
		int year; 
		double score; 
		in >> s >> year >> score;
		out << s << ' ' << ++year << ' ' << min(600, int(score * 1.2)) << '\n'; 
	return 0;
}
