#include<iostream>
#include <sys/time.h>
using namespace std;
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void print_a(int* ar,int n){
    for(int i=0;i<n;i++){
        cout<<ar[i]<< " ";
    }
    cout<<endl;
}
int partition (int *arr, int l, int h){
    int pivot = arr[h];
    int i = (l - 1);

    for (int j = l; j <= h- 1; j++){
        if (arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}

void quickSort(int* arr, int l, int h) {
    if (l < h){
        int pivot = partition(arr, l, h);
        quickSort(arr, l, pivot-1);
        quickSort(arr, pivot + 1,h);
    }
}
void tail_quickSort(int* arr, int l, int h) {
    while (l < h){
        int pivot = partition(arr, l, h);
        quickSort(arr, l, pivot-1);
        l=pivot+1;
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
    gettimeofday(&start,0);
    quickSort(arr,0,N-1);
    gettimeofday(&finish, 0);
    compTime = (finish.tv_sec - start.tv_sec) * 1000000;
    compTime = compTime + (finish.tv_usec - start.tv_usec);
    Time = (double)compTime;

    cout<<"TIempo: "<<Time/1000000<<endl;

    return 0;
}
