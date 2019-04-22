#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int** init(int** matriz,int f,int c){
    matriz= (int **)malloc (f*sizeof(int *));
    for (int i=0;i<f;i++)matriz[i]=(int *) malloc (c*sizeof(int));
    for (int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            matriz[i][j]=rand()%6;
        }
    }
    return matriz;
}
void print_m(int** matriz,int f,int c){
    for (int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}
int** multi_s(int** m_a,int** m_b,int l,int m,int r){
    int **matriz= (int **)malloc (l*sizeof(int *));
    for (int i=0;i<l;i++)matriz[i]=(int *) malloc (r*sizeof(int));
    for(int i=0;i<l;i++){
        for(int j=0;j<r;j++){
            matriz[i][j]=0;
            for(int z=0;z<m;z++){
                matriz[i][j]=matriz[i][j]+ m_a[i][z]*m_b[z][j];
            }
        }
    }
    return matriz;
}
int main(){
    srand(time(NULL));
    int fa,ca,fb,cb;
    printf("filas de a: ");
    scanf("%d",&fa);
    printf("columnas de a: ");
    scanf("%d",&ca);
    printf("filas de b: ");
    scanf("%d",&fb);
    printf("columnas de b: ");
    scanf("%d",&cb);
    if(ca!=fb){
        printf("No se pueden multiplicar las matrices");
        return 0;
    }
    int** matriz_a;
    matriz_a=init(matriz_a,fa,ca);
    int** matriz_b;
    matriz_b=init(matriz_b,fb,cb);
    int** matriz_c;

    struct timeval start;
	struct timeval finish;
	long compTime;
	double Time=0;
	for(int i=0;i<20;i++){



        gettimeofday(&start, 0);

        matriz_c=multi_s(matriz_a,matriz_b,fa,ca,cb);

        gettimeofday(&finish, 0);
        compTime = (finish.tv_sec - start.tv_sec) * 1000000;
        compTime = compTime + (finish.tv_usec - start.tv_usec);
        Time = (double)compTime + Time;

	}
	Time=Time/20;
	printf("Application time: %f Secs\n",(double)Time/1000000.0);
/*
    print_m(matriz_a,fa,ca);
    printf("\n");
    print_m(matriz_b,fb,cb);
    printf("\n");
    print_m(matriz_c,fa,cb);
*/


}
