#include<stdio.h>
#include <sys/time.h>
#include<unistd.h>
#include <time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>



struct timespec diff(struct timespec start, struct timespec end);
void vacia(){}
double half_life_3(){
    struct timespec time1, time2;
    int temp;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

    vacia();

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    return (double)diff(time1,time2).tv_nsec;
}
double t_getpid(){
    struct timespec time1, time2;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

    getpid();

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    return (double)diff(time1,time2).tv_nsec;
}
double u_pipe(){
    struct timespec time1, time2;
    char* c="a";
    int g=2;
    int* nn=&g;
    int p[2];
    pid_t n_pipe;
    char lec;
    if(pipe(p)==-1){
        perror("Error : ");
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    n_pipe=fork();
    if (n_pipe == 0) {
        close(p[1]);
        /*
        while(read(p[0], &lec, 1)>0){
            write(STDOUT_FILENO, &lec, 1);
        }
        */
        read(p[0], &lec, 1);
        close(p[0]);
        _exit(EXIT_SUCCESS);

    } else {
        close(p[0]);
        write(p[1],c, strlen(c));
        close(p[1]);
        wait(NULL);
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
        return (double)diff(time1,time2).tv_nsec;
        exit(EXIT_SUCCESS);
    }

}

int main()
{
    double time=0;
    for(int i=0;i<20;i++){
        time=time+half_life_3();
    }
    printf("Funcion minima : %f \n",time/20);
    time=0;

    for(int i=0;i<20;i++){
        time=time+t_getpid();
    }
    printf("Syscall : %f \n",time/20);
    time=0;

    for(int i=0;i<20;i++){
        time=time+u_pipe();
    }
    printf("Context switch : %f \n",time/20);
    return 0;
}

struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}
