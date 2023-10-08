#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) {
        pai.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i) {
            pai[i] = i;
        }
    }

    void makeSet(int x) {
        pai[x] = x;
        rank[x] = 0;
    }

    int find(int x) {
        if (pai[x] != x) {
            pai[x] = find(pai[x]);
        }

        return pai[x];
    }

    void unionSets(int x, int y) {
        if (rank[x] >= rank[y]) {
            pai[y] = x;
            if (rank[x] == rank[y]) {
                rank[x]++;
            }
        } else {
            pai[x] = y;
        }
    }

private:
    vector<int> pai;
    vector<int> rank;
};

vector<vector<int>> kruskal(vector<vector<int>> &grafo, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &pesos, int n) {
    UnionFind *uf = new UnionFind(n);
    vector<vector<int>> arvore;

    for (int i = 1; i <= n; i++) {
        uf->makeSet(i);
    }

    while (!pesos.empty()) {
        int peso = pesos.top().first;
        int u = pesos.top().second;
        pesos.pop();

        if (!pesos.empty()) {
            int v = pesos.top().second;

            if (uf->find(u) != uf->find(v)) {
                arvore.push_back({u, v});
                uf->unionSets(uf->find(u), uf->find(v));
            }
        }
    }

    delete uf;
    return arvore;
}

int main(int argc, char *argv[]) {
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int vert_inicial = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        } 

        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } 
        
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[++i];
        } 
        
        else if (strcmp(argv[i], "-s") == 0) {
            show_solution = true;
        } 
        
        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1) {
            vert_inicial = atoi(argv[++i]);
        }
    }

    if (input_file == "") {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pesos;
    vector<vector<int>> grafo(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v, peso;
        fin >> u >> v >> peso;

        if (u < 0 || v < 0 || peso < 0) {
            cout << "entrada inválida" << endl;
            return 0;
        }

        grafo[u].push_back(v);
        grafo[v].push_back(u);

        pesos.push({peso, u});
        pesos.push({peso, v});
    }

    fin.close();

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        if (show_solution) {
            vector<vector<int>> arvore = kruskal(grafo, pesos, n);

            for (auto &aresta : arvore) {
                fout << "{" << aresta[0] << ", " << aresta[1] << "}" << endl;
            }

            fout.close();
            return 0;
        }
        else {
            vector<vector<int>> arvore = kruskal(grafo, pesos, n);
    // Escreva a árvore em 'fout' se necessário
            for (const auto &aresta : arvore) 
            {
                fout << "{" << aresta[0] << ", " << aresta[1] << "}" << endl;
            }
}


        fout.close();
    }

    if (show_solution) {
        // Se a opção -s for fornecida, exibir a solução na tela
        vector<vector<int>> arvore = kruskal(grafo, pesos, n);

        for (auto &aresta : arvore) {
            cout << "{" << aresta[0] << ", " << aresta[1] << "}" << endl;
        }
    }

    return 0;
}
