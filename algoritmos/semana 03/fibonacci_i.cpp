#include<iostream>
using namespace std;
int fibo_num(int n){
    int f=0,s = 1,r,t;
    if(n<=1)return n;
    for(int i=2;i<=n;i++){
        r=f+s;
        f=s;
        s=r;
    }
    return r;
}
int main(){
int n;
    cin>>n;
    cout<<fibo_num(n);
}
