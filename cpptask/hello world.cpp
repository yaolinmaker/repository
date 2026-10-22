#include<iostream>

using namespace std;

int main(){
    //算术运算符
    int a1=10;
    int b1=3;

    cout<<a1+b1<<endl;
    cout<<a1-b1<<endl;
    cout<<a1*b1<<endl;
    cout<<a1/b1<<endl;//两个整数相除 结果还是整数 将小数部分去掉

    cout<<a1%b1<<endl;

    int a2 = 10;
    int b2 = 20;
    cout << a2%b2<<endl;//娶不到就是本身  小数不能取余 

    //1，前置递增
    int a= 10;
    ++a;
    cout<<"a="<<a<<endl;

    //2，后置递增
    int b = 10;
    b++;
    cout<<"b="<<b<<endl;

    //3，前后置的区别
    //先让变量加一 再算后面
    int a3=10;
    int b3=++a3 *10;
    cout<<"a3="<<a3<<endl;
    cout<<"b3="<<b3<<endl;

    //先计算 再加一
    int a4=10;
    int b4 =a4++*10;
    cout<<a4<<endl;
    cout<<b4<<endl;

    //赋值运算符
    //1.加等于 +=
    int e = 10;
    e+=2;
    cout<<e <<endl;
    //2.-=

    //3.*=

    //4./=

    //5.%=

    //比较运算符

    //1. ==

    int d= 10 ;
    int f =2;

    cout<<(e==f)<<endl;

    //2.!=

    //3. <  >

    //4. <=   >=

    //逻辑运算符

    //三种  ！非     &&与     ||或    c++除了0 都是真

    int a5= 3;
    int b5= 5;
    cout<<(a5&&b5)<<endl;







 system("pause");

    return 0;
}