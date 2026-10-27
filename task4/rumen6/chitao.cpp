#include<bits/stdc++.h>
using namespace std;
int n,ans=1;
int main(){
    cin>>n;
    for(int i=0;i<n-1;i++){
        ans+=1;
        ans*=2;
    }
    cout<<ans;
    return 0;
}
