#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
	string a;
	ifstream file;
	file.open("/proc/cpuinfo");
	while(!file.eof()){
        getline(file,a);
        	if(string::npos!=a.find("model name")){
	            cout<<a<<endl;
	            break;
	        }
	}
	file.close();
	file.open("/proc/meminfo");	
	while(!file.eof()){
        getline(file,a);
        	if(string::npos!=a.find("MemTotal")){
	            cout<<a<<endl;
	            break;
	        }
	}
	file.close();

	file.open("/proc/version");	
        getline(file,a);
	cout<<a.substr(0,31)<<endl;
	file.close();
	
	file.open("/proc/uptime");
	file>>a;

	int s,m,h;
	s=stoi(a);
	m=s/60;
	s=s%60;
	h=m/60;
	m=m%60;
	cout<<"La ultima ves que se prendio el equipo fue hace: "<<h<<" horas, "<<m<<" minutos, "<<s<<" segundos"<<endl;
	
}

