#include<iostream>
#include<cmath>
using namespace std;

int main(){
    int n=0, count=0, sum=0;
    cin>>n;
    char letras[n];

    for(int i=0;i<n;i++){
        cin>>letras[i];
    }

    for(int j=n-1;j>=0;j--){
        if(letras[j]=='O'){
            sum+=pow(2, count);
            count++;
        }
        else count++;
    }
    cout<<sum<<endl;
}
