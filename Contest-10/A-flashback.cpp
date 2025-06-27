#include <bits/stdc++.h>
using namespace std;

// Estructura de Conjunto Disjunto (DSU)
struct ConjuntoDisjunto {
    vector<int> padre, rango;
    ConjuntoDisjunto(int n) : padre(n+1), rango(n+1, 0) {
        iota(padre.begin(), padre.end(), 0);
    }
    // Encuentra el representante del conjunto de x
    int encontrar(int x) {
        return padre[x] == x ? x : padre[x] = encontrar(padre[x]);
    }
    // Une los conjuntos de a y b; devuelve false si ya estaban unidos
    bool unir(int a, int b) {
        a = encontrar(a);
        b = encontrar(b);
        if (a == b) return false;
        if (rango[a] < rango[b]) swap(a, b);
        padre[b] = a;
        if (rango[a] == rango[b]) rango[a]++;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // Lectura de las carreteras existentes
    vector<pair<int,int>> carreteras;
    carreteras.reserve(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        carreteras.emplace_back(u, v);
    }

    ConjuntoDisjunto dsu(n);
    vector<pair<int,int>> redundantes;

    // Detectar carreteras redundantes (forman ciclo)
    for (auto &c : carreteras) {
        if (!dsu.unir(c.first, c.second)) {
            redundantes.push_back(c);
        }
    }

    // Obtener un representante de cada componente
    vector<int> representante(n+1, 0);
    vector<int> componentes;
    componentes.reserve(n);
    for (int ciudad = 1; ciudad <= n; ciudad++) {
        int raiz = dsu.encontrar(ciudad);
        if (representante[raiz] == 0) {
            representante[raiz] = ciudad;
            componentes.push_back(ciudad);
        }
    }

    // El número de operaciones es igual al número de carreteras redundantes
    int t = redundantes.size();
    cout << t << "\n";

    // Para cada carretera redundante, cerrarla y abrir una nueva que conecte componentes
    for (int i = 0; i < t; i++) {
        int cierra_u = redundantes[i].first;
        int cierra_v = redundantes[i].second;
        int abre_a  = componentes[i];
        int abre_b  = componentes[i+1];
        cout << cierra_u << " " << cierra_v << " " << abre_a << " " << abre_b << "\n";
    }

    return 0;
}
