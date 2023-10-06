#include <bits/stdc++.h>
using namespace std;
//arvore geradora minima, preciso de 1 arvore inicialmente vazia e que as arestas ordenadas em menor custo sao adc nessa
//arvore de maneira que nao gere ciclo obv

//estrutura UNION FIND para verificar se os conjuntos formam ciclos 
class UnionFind {
public:
    UnionFind(int n){
        pai.resize(n);
        rank.resize(n, 0);

        // Inicializa cada elemento como um conjunto separado, cada vert ké uma comp conexa
        for (int i = 0; i < n; ++i) {
            pai[i] = i;
        }
    }

    void makeSet(int x)
    {
        pai[x] = x;
        rank[x] = 0;
    }

    int find(int x)
    {
        if(pai[x] !=x)
        {
            pai[x] = find(pai[x]);
        }

        return pai[x];
    }

    void unionSets(int x , int y)
    {
        if(rank[x] >= rank[y])
        {
            pai[y] = x;
            if(rank[x] == rank[y])
            {
                rank[x] ++;
            }
        }
        else
        {
            pai[x] = y;
        }
        
    }

private:
    vector<int> pai;
    vector<int> rank;
};

vector<vector<int>> kruskal(vector<vector<int>> &grafo,priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &pesos, int n)
{
    UnionFind *uf = new UnionFind(n);
    vector<vector<int>>arvore; // arvore vazia

    for(int i = 1; i <= n; i++)
    {
        uf->makeSet(i);
    }
    while(!pesos.empty())
    {
        int peso = pesos.top().first;
        int u = pesos.top().second;
        pesos.pop();

        if(!pesos.empty())
        {
            int v = pesos.top().second; // se a fila n ta vazia e ta ordenada entao se ha aresta uv = 10 a fila tem (10,u) (10,v) em sequencia


            if(uf->find(u) != uf->find(v))
            {
                arvore.push_back({u,v});
                uf->unionSets(uf->find(u),uf->find(v));
            }
            
        }


    }
    delete uf;
    return arvore;
}
int main()
{
    int n, m;
    cin >> n >> m;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pesos; // fila de prioridade com especificação GREATER = menor p maior
    vector<vector<int>> grafo(n + 1);

    for (int i = 0; i < m; i++)
    {

        int u, v, peso;
        cin >> u >> v >> peso;

        if(u <0 || v < 0 || peso < 0)
        {
            cout << "entrada inválida" << endl;
            return 0;
        }

        grafo[u].push_back(v); // lendo os arcos e pondo na lista de adj quem é vizinho de qm
        grafo[v].push_back(u);

        // por os pesos em ordem
       pesos.push({peso,u});
       pesos.push({peso,v});
    }

//testei e esta ordenando correto exemplo aresta de peso 1 do vert 2 -4 = 1,4 e 1,2
    
    
   
vector<vector<int>> arvore= kruskal(grafo,pesos, n);

for (auto &aresta : arvore)
{
    cout << "{" << aresta[0] << ", " << aresta[1] << "}" << endl;
}

    return 0;
}
