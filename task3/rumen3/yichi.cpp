#include<bits/stdc++.h>
using namespace std;

int main(){
	int n,sum=0;
	cin>>n;
	while(n!=1){
		n=n/2;
		sum++;
	}
	cout<<sum+1;
	return 0;
}
