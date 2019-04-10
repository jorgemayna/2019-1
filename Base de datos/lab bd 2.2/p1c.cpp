#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;
class Alumno
{
  public:
    int codigo_alumno;
    char nombre[12];
    char apPaterno[12];
    char apMaterno[12];
    char carrera[12];
    void imprimir_alumno(){
        cout << codigo_alumno << " "<< nombre << " ";
        cout << apPaterno << " "<< apMaterno << " ";
        cout << carrera << endl;
    }
};
class RandomFile{
  private:
    string filename;
    int indexname;
    fstream file;
  public:
    map<int,int> index;
    RandomFile(string file){
      filename=file;
      //leerIndice();
    }
    void busqueda(int indexname){
      Alumno* temp=new Alumno;
      this->indexname=indexname;
      file.open(filename,ios::in | ios::binary);
      if(file.is_open()){
        file.seekg(index[indexname],ios::beg);
        int tam=0;
        file.read((char *)&tam,sizeof(int));
        file.read((char *)temp,tam);
      }
      cout << temp->codigo_alumno << " ";
      cout << temp->nombre << " ";
      cout << temp->apPaterno << " ";
      cout << temp->apMaterno << " ";
      cout << temp->carrera << endl;
      delete temp;
    };
    void leerIndice(){
      file.open(filename,ios::in | ios::binary);
      file.seekg(0,ios::end);
      int tamanio_fichero=file.tellg();
      file.seekg(0,ios::beg);
      int tamanio_actual=0;
      if(file.is_open()){
        while(tamanio_actual!=tamanio_fichero){
            int codigo_alumno=0;
            int direccion=0;
            file.read((char *)&codigo_alumno,sizeof(int));
            file.read((char *)&direccion,sizeof(int));
            index[codigo_alumno]=direccion;
            tamanio_actual+=8;
        }
        file.close();
      }
    };
    void guardarIndice(){
      file.open("indice.dat",ios::out | ios::app | ios::binary);
      if(file.is_open()){
          for (std::map<int,int>::iterator it=index.begin(); it!=index.end(); ++it){
            file.write((char *)&(it->first),sizeof(int));
            file.write((char *)&(it->second),sizeof(int));
          }
          file.close();
      }
    };
    void imprimirIndices(){
      for (std::map<int,int>::iterator it=index.begin(); it!=index.end(); ++it){
        cout << "Indice: " << it->first << "Direccion" << it->second << endl;
      }
    };
};
class Aula
{
    private:
        vector <Alumno*> alumnos;
    public:
        fstream file;
        RandomFile *randomfile;
        Aula(string file){
            randomfile=new RandomFile(file);
        }
        void load(){
        alumnos.clear();
        file.open("data2.dat",ios::in | ios::binary);
        //file.seekg(0,ios::end);
        //int tamanio_fichero=file.tellg();
        //file.seekg(0,ios::beg);
        int tamanio_actual=0;
        if(file.is_open()){
            while(!file.eof()){
                Alumno* alu=new Alumno;
                int tam=0;
                file.read((char *)&tam,sizeof(int));
                file.read((char *)alu,tam);
                alumnos.push_back(alu);
                //tamanio_actual+=56;
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
        file.open("data2.dat",ios::out | ios::app | ios::binary);
        if(file.is_open()){
            int tam= sizeof(int)+12*4;
            file.write((char *)&tam,sizeof(tam));
            cout<<sizeof(alu);
            file.write((char *)alu,tam);
            file.close();
            //randomfile->index[alu->codigo_alumno]=(alumnos.size()-1)*56;
        }
        }

        void imprimir_alumnos(){
        for(int x=0;x<alumnos.size();x++){
            alumnos[x]->imprimir_alumno();
        }
        };
};
int main(){
  Aula aula("indice.dat");
  aula.load();
  int add_alumnos;
  cin >>add_alumnos;
  for (int i = 0; i < add_alumnos; i++) {
    aula.add();
  }
  aula.imprimir_alumnos();
  /*
  int indice;
  aula.randomfile->imprimirIndices();
  cout << "Insertar Indice" << endl;
  cin >> indice;
  */
  return 0;
}
