#include<iostream>
#include<ctime>
#include<unistd.h>
//#include<windows.h>
using namespace std;
#define INF  999999999

/*double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}
*/

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
    int n;
    int * _array;
    int * _array1;
    unsigned t0,t1;
    //LARGE_INTEGER t_ini, t_fin;
    //LARGE_INTEGER t_ini1, t_fin1;
    double secs,secs1;

    cout<<"Ingrese tamaño: ";
    cin>>n;
    _array = new int[n];
    _array1 = new int[n];
    cout<<endl;

    double co1=0,co2=0;
    for(int zz=0;zz<100000;zz++){
    for(int i=0;i<n;i++){
        _array[i]=n-i;
        _array1[i]=n-i;
    }
    //cout<<"INSERTION SORT:------------------------------"<<endl;
    //print_arr(_array,n);

    //QueryPerformanceCounter(&t_ini);
    t0=clock();
    usleep(200);
    insertion_sort(_array,n);
    t1=clock();
    //QueryPerformanceCounter(&t_fin);

    //print_arr(_array,n);
    double time=(double(t1-t0)/CLOCKS_PER_SEC)*1000;
    //cout<<"Tiempo de ejecucion: "<<time<<endl;
    co1=co1+time;
    //secs = performancecounter_diff(&t_fin, &t_ini);
    //printf("%.16g millisegundos\n", secs * 1000.0);

    //cout<<"MERGE SORT:----------------------------------"<<endl;

    //print_arr(_array1,n);

    //QueryPerformanceCounter(&t_ini1);

    //insertion_sort(_array1,n);
    //QueryPerformanceCounter(&t_fin1);

    //print_arr(_array1,n);

    //secs1 = performancecounter_diff(&t_fin1, &t_ini1);
    //printf("%.16g millisegundos\n", secs1 * 1000.0);

    //cout<<"---------------------------------------------"<<endl;
    /*if(secs1<secs){
        //cout<<"Merge sort gana"<<endl;
        co1++;
    }else{
        //cout<<"Insert sort gana"<<endl;
        co2++;
    }*/
    }
    cout<<"tiempo promedio: "<<co1/100000<<endl;



    delete [] _array;
    delete [] _array1;

}
