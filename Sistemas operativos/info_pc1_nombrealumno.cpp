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
}

