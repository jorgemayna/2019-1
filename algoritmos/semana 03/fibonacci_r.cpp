#include<iostream>
using namespace std;
int fibo_num(int n){
    if(n<=1){
        return n;
    }else{
        return fibo_num(n-2)+ fibo_num(n-1);
    }
}
int main(){
    int n;
    cin>>n;
    cout<<fibo_num(n);


}
