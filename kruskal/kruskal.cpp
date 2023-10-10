#include <bits/stdc++.h>
#include <fstream>

using namespace std;
typedef struct aresta
{
   int peso;
   int v_inicial;
   int v_final;

}aresta;

class UnionFind {
public:
    // Construtor da classe UnionFind
    UnionFind(int n) {
        pai.resize(n);  // Inicializa o vetor 'pai' com 'n' elementos
        rank.resize(n, 0);  // Inicializa o vetor 'rank' com 'n' elementos, todos inicializados com 0

        // Inicializa cada elemento do vetor 'pai' com seu próprio índice
        for (int i = 0; i < n; ++i) {
            pai[i] = i;
        }
    }

    // Função para criar um conjunto (um único elemento) com o índice 'x'
    void makeSet(int x) {
        pai[x] = x;  // Define o pai do elemento 'x' como ele mesmo
        rank[x] = 0;  // Inicializa o rank do conjunto com 'x' como 0
    }

    // Função para encontrar o representante (raiz) do conjunto ao qual 'x' pertence
    int find(int x) {
        if (pai[x] != x) {
            pai[x] = find(pai[x]);  // Atualiza o pai de 'x' para a raiz do conjunto
        }

        return pai[x];  // Retorna a raiz do conjunto
    }

    // Função para unir dois conjuntos com representantes (raízes) 'x' e 'y'
    void unionSets(int x, int y) {
        if (rank[x] >= rank[y]) {
            pai[y] = x;  // Define o pai do conjunto com 'y' como 'x'
            if (rank[x] == rank[y]) {
                rank[x]++;  // Incrementa o rank de 'x' se ambos têm o mesmo rank
            }
        } else {
            pai[x] = y;  // Define o pai do conjunto com 'x' como 'y'
        }
    }

private:
    vector<int> pai;  // Vetor que armazena o pai de cada elemento
    vector<int> rank;  // Vetor que armazena a altura aproximada de cada conjunto (rank)
};

// Função para o algoritmo de Kruskal
int kruskal(vector<vector<int>> &grafo, priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &pesos, int n, int m, int vert_inicial, int show, vector<aresta> &arestas) {
    UnionFind *uf = new UnionFind(n+1);  // Cria uma instância da classe UnionFind
    vector<vector<int>> arvore;  // Vetor que armazena as arestas da Árvore Geradora Mínima
    int custo = 0;  // Variável para armazenar o custo total da Árvore Geradora Mínima

    vector<bool> adicionada(m, false);  // Inicializa um vetor para rastrear se cada aresta foi adicionada à AGM

    for (int i = 1; i <= n; i++) {
        uf->makeSet(i);  // Cria conjuntos individuais para cada vértice do grafo
    }

    uf->makeSet(vert_inicial);  // Cria um conjunto para o vértice inicial

    while (!pesos.empty()) {
        int i = pesos.top().second;  // Obtém o índice da aresta no vetor 'arestas'
        int peso = pesos.top().first;  // Obtém o peso da aresta de menor peso
        int u = arestas[i].v_inicial;  // Obtém o primeiro vértice da aresta
        int v = arestas[i].v_final;  // Obtém o segundo vértice da aresta
        pesos.pop();  // Remove a aresta da fila de prioridade

        if (uf->find(u) != uf->find(v)) {
            arvore.push_back({u, v});  // Adiciona a aresta à Árvore Geradora Mínima
            uf->unionSets(uf->find(u), uf->find(v));  // Une os conjuntos dos vértices u e v
            if(arestas[i].peso == peso)
            {
            custo += peso;  // Atualiza o custo total
            }
            adicionada[i] = true;  // Marca a aresta como adicionada à AGM
        }
    
    }

    if (show) {
        for (int i = 0; i < m; i++) {
            if (adicionada[i]) {
                cout << "(" << arestas[i].v_inicial << "," << arestas[i].v_final << ")";  // Exibe as arestas da Árvore Geradora Mínima
        
            }
        }

        cout << endl;
    }

    delete uf;
    return custo;
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

    ifstream fin;
    fin.open(input_file);

    if (!fin) {
        cerr << "Could not open input file: " << input_file << endl;
        return 1;
    }

    int n, m;
    fin >> n >> m;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pesos;
    vector<aresta>arestas(m+1);
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

        arestas[i].peso=peso;
        arestas[i].v_inicial = u;
        arestas[i].v_final = v;

        pesos.push({peso, i});
    
    }

    fin.close();

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        if (show_solution) { // if -s = mostra a arvore no formato (x,y) (z,w) 
             kruskal(grafo, pesos, n, m,vert_inicial,1,arestas);

            fout.close();
            return 0;
        }
        else { // aqui deve mostra so a soma dos pesos e nao a arvore
            int custo = kruskal(grafo, pesos, n,m,vert_inicial,0,arestas);
                fout << custo;
                //cout << "custo:" << custo <<endl;
            
            }


        fout.close();
    }

    else {
        // Se a opção -s for fornecida, exibir a solução na tela
         int custo = kruskal(grafo, pesos,n,m,vert_inicial,0,arestas);
         if(!show_solution)
         {
                cout << custo << endl;

         }
                //cout << "custo:" << custo <<endl;
            
        //kruskal(grafo, pesos, n,vert_inicial,1);

    }

    return 0;
}
