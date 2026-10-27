#include <bits/stdc++.h>
using namespace std;
int n, m,a[15];//定义

int main() {
	cin >> m>> n;
	for (int i = m; i <= n; i++) {//数位分离
		int x = i;
		while (x) {//计数
			int b = x % 10;
			a[b]++;
			x /= 10;
		}
	}
	for(int i=0;i<=9;i++){
		cout<<a[i]<<" ";//输出
	}
	return 0;
}

