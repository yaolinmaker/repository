#include<bits/stdc++.h>
using namespace std;
int n,a[110];
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    cout<<a[1];
    return 0;
}