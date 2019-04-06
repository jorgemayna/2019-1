#include<iostream>
#include<ctime>
#include<unistd.h>
#include<fstream>
//#include<windows.h>
using namespace std;
#define INF  999999999



void print_arr(int* _array,int n){
    for(int i=0;i<n;i++){
        cout<<" "<<_array[i];

    }
    cout<<endl;
}
void insertion_sort(int* _array,int n){
    int key,j;
    for(int i=1;i<n;i++){
        key=_array[i];
        j=i-1;
        while(j>=0 && _array[j]>key){
            _array[j+1]=_array[j];
            j=j-1;
        }
        _array[j+1]=key;
    }
}
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
    int n,total=20000;
    int * _array;
    ofstream file;
    file.open("record.txt");

    cout<<"Ingrese tamaño: ";
    cin>>n;

    cout<<endl;
    for(int num=1;num<=n;num++){
    unsigned t0,t1;
    double co1=0;
    for(int zz=0;zz<total;zz++){
        _array = new int[num];
        for(int i=0;i<num;i++){
            _array[i]=num-i;
        }
        //cout<<"INSERTION SORT:------------------------------"<<endl;
        //print_arr(_array,n);

        t0=clock();
        usleep(200);
        if(zz<total/2){
            insertion_sort(_array,num);
        }else{
            merge_sort(_array,0,num);
        }
        t1=clock();

        //print_arr(_array,n);
        double time=(double(t1-t0)/CLOCKS_PER_SEC)*1000;
        //cout<<"Tiempo de ejecucion: "<<time<<endl;
        co1=co1+time;


        //cout<<"MERGE SORT:----------------------------------"<<endl;

        //print_arr(_array1,n);

        //insertion_sort(_array1,n);

        //print_arr(_array1,n);


        //cout<<"---------------------------------------------"<<endl;
        delete [] _array;
        if(zz==total/2-1){
            cout<<"insertion sort de "<<num<<": "<<co1/(total/2)<<endl;
            file<<num<<"   "<<co1/(total/2)<< "   ";
            co1=0;
        }
    }

    cout<<"merge sort de "<<num<<": "<<co1/(total/2)<<endl<<endl;
    file<<co1/(total/2)<<endl;


    }




}
