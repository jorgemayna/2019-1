#include<stdio.h>
#include<iostream>
#include <sys/time.h>
using namespace std;
int main()
{
int arr[100000];
int temp;
long int cont=0;

for(int i=0;i<100000;i++){
	cin>>arr[i];
}
timeval start;
timeval finish;
long int compTime;
double Time;
gettimeofday(&start, 0);
for(int x=0;x<100000;x++){
	for(int y=x;y>0;y--){
		if(arr[y-1]>arr[y]){
			temp=arr[y];
			arr[y]=arr[y-1];
			arr[y-1]=temp;
			cont++;
		}
	}
}
gettimeofday(&finish, 0);
compTime = (finish.tv_sec - start.tv_sec) * 1000000;
compTime = compTime + (finish.tv_usec - start.tv_usec);
Time = (double)compTime;

cout<<"Numero de swaps: "<<cont<<endl;
cout<<"TIempo: "<<Time<<endl;
return 0;
}
