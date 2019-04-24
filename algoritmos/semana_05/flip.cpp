#include<iostream>
#include <sys/time.h>
using namespace std;
long int cont=0;
void print_a(int* ar,int n){
    for(int i=0;i<n;i++){
        cout<<ar[i]<< " ";
    }
    cout<<endl;
}
void flip(int* ar,int i){
    int t=ar[i];
    ar[i]=ar[i+1];
    ar[i+1]=t;
    cont++;
}
void merge_flip(int* ar,int l,int m,int r){
    for(int i=m+1;i<=r;i++){
        int j=i-1,key=ar[i];
        while(ar[j]>key && j>=l){
            flip(ar,j);

            j--;
        }
    }
}
void flip_sort(int* ar,int l,int r){
    if(r>l){
        int m=(r+l)/2;
        flip_sort(ar,l,m);
        flip_sort(ar,m+1,r);
        merge_flip(ar,l,m,r);

    }
}
int main(){
    int N;
    int* arr;
    N=100000;
    arr=new int[N];

    for(int i=0;i<N;i++){
	 cin>>arr[i];
    }
    timeval start;
    timeval finish;
    long int compTime;
    double Time;
    flip_sort(arr,0,N-1);
    gettimeofday(&finish, 0);
    compTime = (finish.tv_sec - start.tv_sec) * 1000000;
    compTime = compTime + (finish.tv_usec - start.tv_usec);
    Time = (double)compTime;
    cout<<"Minimum exchange operations : "<<cont<<endl;
    cout<<"TIempo: "<<Time<<endl;
    cont=0;
    delete [] arr;

}
