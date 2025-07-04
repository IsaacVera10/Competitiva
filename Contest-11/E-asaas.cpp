#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s1,s2;

    while((cin>>s1) && s1[0] != '#'){
        cin >> s2;
        int n = s1.size(), m = s2.size();
        int cnt = 0;
        // posición desde la que buscamos
        size_t pos = 0;
        while (pos + m <= (size_t)n) {
            // buscamos s2 en s1 a partir de pos
            size_t p = s1.find(s2, pos);
            if (p == string::npos) break;
            ++cnt;
            // simulamos cortar ese trozo y seguimos justo después
            pos = p + m;
        }
        cout << cnt << "\n";
    }



    return 0;
}