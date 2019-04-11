#include<iostream>
using namespace std;
int binary_search_gg(int* arr,int n,int co){
        int l=0;
        int r=n-1;
        while(r>=l){
            int m=(l+r)/2;
            int re=arr[m];
            if(re<co){
                l=m+1;
            }else if(re>co){
                r=m-1;
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
    cout<<binary_search_gg(arr,n,num)<<endl;

}
