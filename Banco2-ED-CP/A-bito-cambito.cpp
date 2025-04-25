#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main(){
    int n;
    while(cin >> n && n != 0){
        vector<char> microprocessor(32, '?');
        
        for(int i = 0; i < n; i++){
            string instruction;
            cin >> instruction;
            
            if(instruction == "CLEAR"){
                int bit;
                cin >> bit;
                microprocessor[bit] = '0';
            }
            else if(instruction == "SET"){
                int bit;
                cin >> bit;
                microprocessor[bit] = '1';
            }
            else if(instruction == "OR"){
                int bit1, bit2;
                cin >> bit1 >> bit2;
                if(microprocessor[bit1] == '1' || microprocessor[bit2] == '1')
                    microprocessor[bit1] = '1';
                else if(microprocessor[bit1] == '0' && microprocessor[bit2] == '0')
                    microprocessor[bit1] = '0';
                else
                    microprocessor[bit1] = '?';
            }
            else if(instruction == "AND"){
                int bit1, bit2;
                cin >> bit1 >> bit2;
                if(microprocessor[bit1] == '0' || microprocessor[bit2] == '0')
                    microprocessor[bit1] = '0';
                else if(microprocessor[bit1] == '1' && microprocessor[bit2] == '1')
                    microprocessor[bit1] = '1';
                else
                    microprocessor[bit1] = '?';
            }
        }
        
        for(int i = 31; i >= 0; i--){
            cout << microprocessor[i];
        }
        cout << endl;
    }
    return 0;
}