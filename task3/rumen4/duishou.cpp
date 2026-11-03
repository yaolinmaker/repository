#include <bits/stdc++.h>
using namespace std;
int yw[1005],sx[1005],yy[1005],zf[1005];//拼音万岁！
int ans=0;
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>yw[i]>>sx[i]>>yy[i];
		zf[i]=yw[i]+sx[i]+yy[i]; 
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((abs(yw[i]-yw[j])<=5)&&(abs(sx[i]-sx[j])<=5)&&(abs(yy[i]-yy[j])<=5)&&(abs(zf[i]-zf[j])<=10)){//就是题目里面的意思。
                ans++;
            }
		}
	}
	cout<<ans;
	return 0;
}
