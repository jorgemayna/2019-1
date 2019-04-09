#include<iostream>
#include<string>
#include<fstream>
#include<unistd.h>
using namespace std;
int main(){
	string a;
	ifstream file;
	double mt,md;
	file.open("/proc/meminfo");
	bool t=true;
	int pro=0,cont=0;
	system("clear");
	while(t){
    	while(!file.eof()){
            file>>a;
            if(a=="MemTotal:"){
                file>>a;
                mt=stod(a);
            }

            if(a=="MemAvailable:"){
                file>>a;
                md=stod(a);
                break;
            }
        }
        cout<<"Porcentaje de memoria disponible: "<<md/mt*100<<"%"<<endl;
        file.close();

        file.open("/proc/stat");
        file>>a;
        double sum=0,um,sm,id;
        for(int i=0;i<10;i++){
            file>>a;
            sum=stoi(a)+sum;
            if(i==1)um=stoi(a);
            if(i==3)sm=stoi(a);
            if(i==4)id=stoi(a);
        }
        cout<<"Tiempo en User mode: "<<um/sum*100<<"%"<<endl;
        cout<<"Tiempo en System Mode mode: "<<sm/sum*100<<"%"<<endl;
        cout<<"Tiempo en Idle: "<<id/sum*100<<"%"<<endl;

        while(!file.eof()){
            file>>a;
            if(a=="ctxt"){
                int cont1;
                file>>a;
                cont1=stoi(a);
                cout<<"Tasa de cambios de contexto: "<<cont1-cont<<" contextos/segundo"<<endl;
                cont=cont1;
            }

            if(a=="processes"){
                int po;
                file>>a;
                po=stoi(a);
                cout<<"Tase de creacion de procesos: "<<po-pro<<" procesos/segundo"<<endl;
                pro=po;
                break;
            }
        }
        file.close();
        usleep(1000000);
        system("clear");
	}





}
