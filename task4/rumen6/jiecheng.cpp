#include <bits/stdc++.h>
using namespace std;

int f(int x)
{
	if (x == 0)
		return 1;
	return f(x - 1) * x;
}

int n;

int main()
{
	cin >> n;
	cout << f(n) << endl;
	return 0;
}
