#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/time.h>
struct timeval start;
struct timeval finish;
pthread_mutex_t lock;
pthread_t t[5];
int unidades_de_makis[5]={20,20,20,20,20};
int estados[5]={0,0,0,0,0};
int palillos_disponibles[2]={0,0};
int tiempo=0;
void *cena(void* id_arg){
  int id=(int)id_arg;
  if(unidades_de_makis[id]==0){
    pthread_exit(NULL);
  }
  if(pthread_mutex_trylock(&lock)==0){
    //pthread_mutex_lock(&lock);
    if(palillos_disponibles[0]==0 || palillos_disponibles[1]==0){
      if(palillos_disponibles[0]==0 && palillos_disponibles[1]!=0){
        palillos_disponibles[0]=1;
        estados[id]=1;
      }
      else{
        palillos_disponibles[1]=1;
        estados[id]=1;
      }
      unidades_de_makis[id]-=1;
    }
    pthread_mutex_unlock(&lock);
  }
  pthread_exit(NULL);
}
int main(){
  gettimeofday(&start, 0);
  if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
  while(unidades_de_makis[0]!=0 || unidades_de_makis[1]!=0 || unidades_de_makis[2]!=0 || unidades_de_makis[3]!=0 || unidades_de_makis[4]!=0){
    for (int rank = 0; rank < 5; rank++)
       pthread_create(&t[rank], NULL,cena ,(void*)rank);
    for (int rank = 0; rank < 5; rank++)
        pthread_join(t[rank], NULL);
    for(int x = 0; x < 5; x++){
        if(estados[x]==0){
          printf("Sabio %d esta hablando\n", x+1);
        }
        else{
          printf("Sabio %d esta comiendo\n", x+1);
          estados[x]=0;
        }
    }
    for(int x = 0; x < 5; x++){
        printf("unidades_de_makis restantes de %d es %d\n", x , unidades_de_makis[x]);
    }
    printf("--------------------------------------------------------------------------------\n");
    palillos_disponibles[0]=0;
    palillos_disponibles[1]=0;
    tiempo+=4;
  }
  gettimeofday(&finish, 0);
  printf("Application time: %f Secs\n",(double)(((finish.tv_sec - start.tv_sec) * 1000000)+(finish.tv_usec - start.tv_usec))/1000000.0);
  printf("%d\n", tiempo);
  //pthread_exit(NULL);
  return 0;
}
