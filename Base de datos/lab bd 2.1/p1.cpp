#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;
class Alumno
{
  public:
    int codigo_alumno;
    char nombre[12];
    char apPaterno[12];
    char apMaterno[12];
    char carrera[12];
};
class Aula
{
  private:
      char filename[100];
      vector <Alumno*> alumnos;
  public:
    void load(){
      alumnos.clear();
      ifstream file;
      file.open("data2.dat",ios::in | ios::binary);
      file.seekg(0,ios::end);
      int tamanio_fichero=file.tellg();
      file.seekg(0,ios::beg);
      int tamanio_actual=0;
      if(file.is_open()){
        while(tamanio_actual!=tamanio_fichero){
            Alumno* alu=new Alumno;
            int tam=0;
            file.read((char *)&tam,sizeof(int));
            file.read((char *)alu,tam);
            alumnos.push_back(alu);
            tamanio_actual+=56;
        }
        file.close();
      }
      imprimir_alumnos();
    };
    void add(){
      Alumno* alu=new Alumno;
      cout << "Ingrese el codigo alumno" << endl;
      cin >>alu->codigo_alumno;
      cout<<"Ingrese el nombre: "<<endl;
      cin >>alu->nombre;
      cout<<"Ingrese el apellido paterno: "<<endl;
      cin >>alu->apPaterno;
      cout<<"Ingrese el apellido apMaterno: "<<endl;
      cin >>alu->apMaterno;
      cout<<"Ingrese la carrera: "<<endl;
      cin >>alu->carrera;
      alumnos.push_back(alu);
        fstream file;
        file.open("data2.dat",ios::out | ios::app | ios::binary);
        if(file.is_open()){
            int tam= sizeof(int)+12*4;
            file.write((char *)&tam,sizeof(int));
            file.write((char *)alu,tam);
            file.close();
        }
    }
    void bulkInsert(){
      Alumno* temp;
      int position;
      for (int i = 1; i < alumnos.size(); i++) {
        position=i;
        for (int y = i-1; y >= 0; y--) {
          if(alumnos[position]->codigo_alumno<alumnos[y]->codigo_alumno){
            temp = alumnos[y];
            alumnos[y]=alumnos[position];
            alumnos[position]=temp;
            position=y;
          }
        }
      }
      fstream file;
        file.open("data2.dat",ios::in | ios::binary);
        if(file.is_open()){
            file.close();
            remove( "data2.dat" );
            file.open("data2.dat",ios::out | ios::app | ios::binary);
            int tam= sizeof(int)+12*4;
            for(int x=0;x<alumnos.size();x++){
                file.write((char *)&tam,sizeof(int));
                file.write((char *)alumnos[x],tam);
            }
            file.close();
        }
    }

    void imprimir_alumnos(){
      for(int x=0;x<alumnos.size();x++){
          cout << alumnos[x]->codigo_alumno << " ";
          cout << alumnos[x]->nombre << " ";
          cout << alumnos[x]->apPaterno << " ";
          cout << alumnos[x]->apMaterno << " ";
          cout << alumnos[x]->carrera << endl;
      }
    };
    int binary_search_gg(int co){
        int l=0;
        int r=alumnos.size()-1;
        while(r>=l){
            int m=(l+r)/2;
            int re=alumnos[m]->codigo_alumno;
            if(re<co){
                l=m+1;
            }else if(re>co){
                r=m-1;
            }else{
                return m;
            }
        }
    }
};

int main(){
  Aula aula;
  aula.load();
  int add_alumnos;
  cin >>add_alumnos;
  for (int i = 0; i < add_alumnos; i++) {
    aula.add();
  }
    aula.bulkInsert();
    aula.load();
    cout<<aula.binary_search_gg(5);
}
