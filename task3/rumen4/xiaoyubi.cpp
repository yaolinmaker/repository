#include<iostream>
#include<math.h>
using namespace std;
int main(){
	int x,a[100000],s=0;
	cin>>x;
	for(int i=1;i<=x;i++){
		cin>>a[i];
	}
	cout<<0<<" ";
	for(int j=2;j<=x;j++){
		for(int k=j-1;k>=1;k--){
			if(a[j]>a[k]){
				s=s+1;
			}
		}
		cout<<s<<" ";
		s=0;
	} 
}
