#include<iostream>
#include<vector>
#include<string>
using namespace std;
int larger_sum(vector<int> arr){
    int sum_m=0;
    for(int i=0;i<arr.size();i++){
        int sum=0;
        for(int j=i;j<arr.size();j++){
            sum=sum+arr[j];
            if(sum>sum_m){
                sum_m=sum;
            }
        }
    }
    return sum_m;
}
int main(){
    vector<int> arr;
    string val,num;

    while(getline(std::cin,val)){
        int p=0;
        string t;
        while ((p = val.find(' ')) != string::npos) {
            t = val.substr(0, p);
            arr.push_back(stoi(t));
            val.erase(0, p + 1);
        }
        arr.push_back(stoi(val));
        for(int i=0;i<arr.size();i++){
            cout<<arr[i]<<",";
        }
        cout<<endl;
        cout<<larger_sum(arr)<<endl;
        arr.clear();
    }
}
