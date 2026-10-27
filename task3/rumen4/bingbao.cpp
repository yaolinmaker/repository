#include<bits/stdc++.h>
using namespace std;
int n,a[100010],t=1;
int main(){
    cin>>n;
    a[0]=n;
    while(n!=1){
        if(n%2==1) n=n*3+1;
        else n/=2;
        a[t]=n;
        t++;
    }
    t--;
    for(int i=t;i>=0;i--) cout<<a[i]<<" ";
    return 0;
}
