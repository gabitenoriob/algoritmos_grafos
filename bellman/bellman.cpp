#include <bits/stdc++.h>

using namespace std;

struct Aresta {
    int v_final;
    int peso;
};

void BellmanFord(vector<vector<Aresta>>& grafo, vector<vector<int>>& pesos, int n, int vert_inicial) {
    vector<int> distancia(n + 1, numeric_limits<int>::max());
    distancia[vert_inicial] = 0;

        for (int u = 1; u <= n; u++) {
            for (const Aresta& aresta : grafo[u]) {
                int v = aresta.v_final;
                int peso = aresta.peso;

                if (distancia[u] != numeric_limits<int>::max() && distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                }
            }
        }
    

    
        for (const Aresta& aresta : grafo[u]) {
            int v = aresta.v_final;
            int peso = aresta.peso;

            if (distancia[u] != numeric_limits<int>::max() && distancia[u] + peso < distancia[v]) {
                cerr << "Ciclo de peso negativo encontrado." << endl;
                return;
            }
        }

    for (int i = 1; i <= n; i++) {
        cout << "Distância mínima de " << vert_inicial << " para " << i << ": " << distancia[i] << endl;
    }
}

int main(int argc, char* argv[]) {
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int vert_inicial = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saída para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        } else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            vert_inicial = atoi(argv[++i]);
        }
    }

    if (input_file == "") {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin;
    fin.open(input_file);

    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;

    vector<vector<Aresta>> grafo(n + 1);
    vector<vector<int>> pesos(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));

    for (int i = 0; i < m; i++) {
        int u, v, peso;
        fin >> u >> v >> peso;

        if (u < 0 || v < 0) {
            cout << "entrada inválida" << endl;
            return 0;
        }

        Aresta nova_aresta;
        nova_aresta.v_final = v;
        nova_aresta.peso = peso;

        grafo[u].push_back(nova_aresta);
        pesos[u][v] = peso;
        pesos[v][u] = peso;
    }

    BellmanFord(grafo, pesos, n, vert_inicial);

    return 0;
}
