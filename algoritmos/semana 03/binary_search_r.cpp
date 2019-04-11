#include<iostream>
using namespace std;
int binary_search_gg(int* arr,int l,int r,int co){
        if(r>=l){
            int m=(l+r)/2;
            int re=arr[m];
            if(re<co){
                return binary_search_gg(arr,m+1,r,co);
            }else if(re>co){
                return binary_search_gg(arr,l,m-1,co);
            }else{
                return m;
            }
        }
    }
int main(){
    int n,num;
    cin>>n;
    int* arr;
    arr=new int[n];
    for(int i=0;i<n;i++){
        arr[i]=i+1;
    }
    cin>>num;
    cout<<binary_search_gg(arr,0,n-1,num)<<endl;

}
