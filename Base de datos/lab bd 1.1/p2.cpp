#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;

class Alumno{
        public:
        char nombre[12];
        char apPaterno[12];
        char apMaterno[12];
        char carrera[15];

        void imp(){
            cout<<nombre<<endl;
        }

    };
class Aula{

    public:

    vector<Alumno*> alumnos;

    void imprimir_alumnos(){
        for(int i=0;i<alumnos.size();i++){
            cout << alumnos[i]->nombre << " ";
            cout << alumnos[i]->apPaterno << " ";
            cout << alumnos[i]->apMaterno << " ";
            cout << alumnos[i]->carrera << endl;
        }
    }

    void load(){
        Alumno* al;
        ifstream file("datos.txt");
        al=new Alumno;
        file>>al->nombre>>al->apPaterno>>al->apMaterno>>al->carrera;
        while(!file.eof()){
            alumnos.push_back(al);
            al=new Alumno;
            file>>al->nombre>>al->apPaterno>>al->apMaterno>>al->carrera;
        }
        file.close();
        imprimir_alumnos();
    }

    void add(Alumno* A1){
        alumnos.push_back(A1);
        fstream file;
        file.open("datos.txt",fstream::app | fstream::out);
        file << A1->nombre<<"      "<<A1->apPaterno<<"      "<<A1->apMaterno<<"      "<<A1->carrera<<endl;
        file.close();
    }
    bool deletes(int){
    }
};

int main(){
    Aula aula;
    aula.load();
    Alumno* alu=new Alumno;
    cin>>alu->nombre;
    cin>>alu->apPaterno;
    cin>>alu->apMaterno;
    cin>>alu->carrera;
    aula.add(alu);
    aula.imprimir_alumnos();




}
