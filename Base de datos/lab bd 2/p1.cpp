#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;

class Alumno{
        public:
        string nombre;
        string apPaterno;
        string apMaterno;
        string carrera;

        void imprimir_alumnos(){
                cout << nombre << " ";
                cout << apPaterno << " ";
                cout << apMaterno << " ";
                cout << carrera << endl;

        }
        void load(){
            Alumno* al;
            ifstream file("datos.txt");
            al=new Alumno;
            string line,b;
            file>>line;
            getline(file,b,'|');
            nombre=b;
            getline(file,b,'|');
            apPaterno=b;
            getline(file,b,'|');
            apMaterno=b;
            getline(file,b);
            carrera=b;

            /*while(!file.eof()){
                alumnos.push_back(al);
                al=new Alumno;
                file>>al->nombre>>al->apPaterno>>al->apMaterno>>al->carrera;
            }
            */
            imprimir_alumnos();
        }

    };


int main(){
    Alumno alu;
    alu.load();







}
