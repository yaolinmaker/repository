#include<bits/stdc++.h>
using namespace std;
double a,b,c,d,e,f;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>a>>b>>c>>d>>e>>f;
    cout<<fixed<<setprecision(2)<<sqrt((c-a)*(c-a)+(d-b)*(d-b))+sqrt((c-e)*(c-e)+(d-f)*(d-f))+sqrt((e-a)*(e-a)+(f-b)*(f-b));
	return 0;
}
