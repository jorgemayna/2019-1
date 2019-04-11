#include<iostream>
using namespace std;
int factorial(int n){
    int r=1;
    for(int i=1;i<=n;i++){
        r=r*i;
    }
    return r;
}
int main(){
    int n;
    cin >> n;
    cout<<factorial(n)<<endl;
}
