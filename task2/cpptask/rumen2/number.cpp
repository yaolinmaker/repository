#include <iostream>

using namespace std;
 int main()
 {
    int a;
    cin>>a;
    if(a%2==0&4<a&a<=12)
    {
        cout<<"1 ";
    }
    else
    {
        cout<<"0 ";
    
    }
    if(a%2==0||4<a&a<=12)
    {
        cout<<"1 ";
    }
    else{
        cout<<"0 ";
    }
    if((a%2==0&(4>=a||a>12))||(a%2!=0&(4<a&a<=12)))
    {
        cout<<"1 ";
    }
    else
    {
        cout<<"0 ";
    }
    if(a%2!=0&(a<=4||a>12))
    {
        cout<<"1";
    }
    else{
        cout<<"0";
    }
   
     system("pause");

     return 0;
    
}