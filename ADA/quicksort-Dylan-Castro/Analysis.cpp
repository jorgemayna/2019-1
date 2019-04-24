#include<stdio.h>
#include<iostream>
#include <sys/time.h>
#include <stdlib.h>
using namespace std; 
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] <= pivot) 
        { 
            i++; 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
void countingSort(int numbers[], int size) {
    // TODO
    int mayor=numbers[0];
    int menor=numbers[0];
    int temp[size];
    for (int i = 0; i < size; i++) {
        temp[i]=numbers[i];
        if(numbers[i]>mayor){
            mayor=numbers[i];
        }
        if(numbers[i]<menor){
            menor=numbers[i];
        }
    }
    int index[mayor+1]={};
    for (int i = 0; i < size; i++) {
        index[temp[i]]++;
    }
    int contador=0;
    for (int i = menor; i <= mayor; i++) {
        index[i]+=contador;
        contador=index[i];
    }
    for (int i = 0; i < size; i++) {
        numbers[index[temp[i]]-1]=temp[i];
        index[temp[i]]--;
    }
}
int main() 
{ 
    struct timeval start;
    struct timeval finish;
    double prom=0;
    //int arr[] = {10, 7, 8, 9, 1, 5};
    //int arr2[] = {10, 7, 8, 9, 1, 5};  
    //int n = sizeof(arr)/sizeof(arr[0]);
    for(int x=0;x<10000;x++){
    gettimeofday(&start, 0); 
    quickSort(new int[6]{6, 5, 4, 3, 2, 1}, 0, 6-1);
    gettimeofday(&finish, 0);
    prom+=(double)(((finish.tv_sec - start.tv_sec) * 1000000)+(finish.tv_usec - start.tv_usec))/1000000.0;
    }
    printf("Application time Quick Sort: %f Secs\n",prom/100);
prom=0;
for(int x=0;x<10000;x++){
    gettimeofday(&start, 0); 
    countingSort(new int[6]{6, 5, 4, 3, 2, 1}, 6);
    gettimeofday(&finish, 0);
    prom+=(double)(((finish.tv_sec - start.tv_sec) * 1000000)+(finish.tv_usec - start.tv_usec))/1000000.0;
    }
    printf("Application time Counting sort: %f Secs\n",prom/100);
    //countingSort(arr2[],n); 
    //cout << arr[0];
    return 0; 
}
