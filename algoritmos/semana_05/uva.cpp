#include<iostream>
using namespace std;
long long int cont=0;
void Merge(int* _array,int i,int me,int d){
    int n1= me-i +1;
    int n2= d-me;
    int l[n1+1],r[n2+1];
    for(int z=0;z<n1;z++){
        l[z]=_array[i+z];
    }
    for(int z=0;z<n2;z++){
        r[z]=_array[me+1+z];
    }
    l[n1]=INF;
    r[n2]=INF;
    int z=0,x=0,k=i;
    while(z!=n1 || x!=n2){
        if(l[z]<=r[x]){
            _array[k]=l[z];
            z++;
        }else{
            _array[k]=r[x];
            x++;
        }
        k++;
    }
}
void merge_sort(int* _array,int i,int d){
    if(d>i){
        int me = (d+i)/2;
        merge_sort(_array,i,me);
        merge_sort(_array,me+1,d);
        Merge(_array,i,me,d);

    }
}
int main(){
    int N;
    while(cin>>N){
        if(N!=0){
           int* arr;
            arr=new int[N];
            for(int i=0;i<N;i++){
                cin>>arr[i];
            }
            merge_sort(arr,0,N);
            cout<<cont<<endl;
            cont=0;
            delete [] arr;
        }
        else{
            return 0;
        }
    }


}
