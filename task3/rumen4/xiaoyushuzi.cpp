#include<iostream>
#include<algorithm>
using namespace std;
int a[1000001],n;
int main(){
	for(int i=1;;i++){
		cin>>a[i];
		if(a[i]==0){
			n=i;
			break;
		} 
	} 
	for(int i=n-1;i>=1;i--){
		cout<<a[i]<<' ';
	}
	return 0;
}
