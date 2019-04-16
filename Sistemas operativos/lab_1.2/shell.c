#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

char delim[]=" ";
char* token(char* imput){
    char *ptr = strtok(imput,delim);
    char *pos;
    if((pos=strchr(ptr,'\n'))!=NULL){
        *pos='\0';
    }
    return ptr;
}
char* next_token(char* imput,char* ptr){
    ptr=strtok(NULL,delim);
    char *pos;
    if((pos=strchr(ptr,'\n'))!=NULL){
        *pos='\0';
    }
    return ptr;
}
void ls(){
    struct dirent *dc;
    DIR *direc=opendir(".");
    if(direc==NULL){
        printf("No se pudo abrir el directorio");
        return;
    }

    while((dc= readdir(direc)) != NULL){
        printf("%s   ",dc->d_name);
    }
    closedir(direc);
    printf("\n");
}
void pwd(){
    char dir[256];
    if (getcwd(dir,sizeof(dir))==NULL){
        perror("getcwd() error");
    }else{
        printf("%s",dir);
    }
}
void cd(char* imput,char* ptr){
    ptr=next_token(imput,ptr);
    if(ptr!=NULL){
        if(chdir(ptr)==-1){
            perror("Error: ");
            return;
        }else{
            return;
        }

    }else{
        printf("Faltan arguemntos\n");
    }
    //chdir(dir);
}
void mkdirf(char* imput,char* ptr){
    ptr=next_token(imput,ptr);
    if(mkdir(ptr,0777)==-1){
        printf("No se pudo crear el directorio");
    }else{
        return;
    }
}
void recursive_delete(char* ptr){
    struct dirent *dc;
    DIR *direc=opendir(ptr);
    if(direc==NULL){
        perror("Fallo al abrir directorio: ");
        return;
    }
    if(chdir(ptr)==-1){
        perror("Error al entrar recursivamente a directorio: ");
        return;
    }
    while((dc= readdir(direc)) != NULL){
        if(dc->d_type==DT_DIR){
            if((strcmp(dc->d_name,".")!= 0) && (strcmp(dc->d_name,"..")!= 0) ){
                recursive_delete(dc->d_name);
            }
        }else{
            if(unlink(dc->d_name)==-1){
            perror("No se pudo eliminar: ");
            return;
            }
        }

    }
    closedir(direc);
    chdir("..");
    if(rmdir(ptr)==-1){
    perror("No se pudo eliminar: ");
    }else{
        return;
    }
}
void rm(char* imput,char* ptr){
    ptr=next_token(imput,ptr);
    if(ptr!=NULL){
        if(strcmp(ptr,"-d")== 0){
            ptr=next_token(imput,ptr);
            if(rmdir(ptr)==-1){
            perror("No se pudo eliminar: ");
            }else{
                return;
            }
        }else if(strcmp(ptr,"-r")== 0){
            ptr=next_token(imput,ptr);
            recursive_delete(ptr);
        }else{
            if(unlink(ptr)==-1){
            perror("No se pudo eliminar: ");
            }else{
                return;
            }
        }
    }else{
        printf("Faltan argumentos\n");
    }
}

int main(int   argc,char *argv[] ){
    char  imput[200];// = malloc(sizeof(char) * 128);
    _Bool ciclo=1;
    system("clear");
    while(ciclo==1){
        printf("SOjorgemayna:");
        pwd();
        printf("$");
        fgets(imput,200,stdin);
        char *ptr = token(imput);
        if(strcmp(ptr,"dir")== 0){
            ls();
        }else if(strcmp(ptr,"ntd")== 0){//name this dir
            pwd();
            printf("\n");
        }else if(strcmp(ptr,"cd")== 0){
            cd(imput,ptr);
        }else if(strcmp(ptr,"crtdir")==0){
            mkdirf(imput,ptr);
        }else if(strcmp(imput,"dl")==0){
            rm(imput,ptr);
        }else{
            printf("Comando desconocido \n");
        }
    }

    return 0;

}
