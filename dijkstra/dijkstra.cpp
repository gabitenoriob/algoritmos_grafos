#include <bits/stdc++.h>
using namespace std;

// vetor dist = cada indice tem a dist do vertice 0-indice
// vetor pre = tem o pai
// devo comparar os pesos dos adj para saber quem por na distancia
// cria uma fila de prioridade onde cada elemento é um par de inteiros, ordenados em ordem crescente de distância acumulada
void dijkstra(vector<vector<int>> &grafo, vector<int> &dist, vector<int> &pre, int n, vector<vector<int>> &pesos, int m)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila; // fila de prioridade com especificação GREATER = menor p maior
    fila.push({0, 1});                                                                    // sendo 1 o vert inicial sua distancia ate ele mesmo é 0, o par é (dist[v],v)

    while (!fila.empty())
    {
        int u = fila.top().second; // segundo /segunda parte do par / y (x,y) -> elemento do topo -> da fila
        int distancia_ate_u = fila.top().first;
        fila.pop();

        if (distancia_ate_u > dist[u])
            continue; // ja passou pelo u senao seria menor

        else
        {

            for (auto adjacente : grafo[u])
            {
                int v = adjacente;
                int peso_uv = pesos[u][v];

                if (dist[u] + peso_uv < dist[v])
                {
                    dist[v] = dist[u] + peso_uv;
                    pre[v] = u;
                    fila.push({dist[v], v});
                }
            }
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pesos(n + 1, vector<int>(n + 1, numeric_limits<int>::max())); // inicializar com valores grandes
    vector<vector<int>> grafo(n + 1);

    for (int i = 0; i < m; i++)
    {

        int u, v, peso;
        cin >> u >> v >> peso;

        grafo[u].push_back(v); // lendo os arcos e pondo na lista de adj quem é vizinho de qm
        grafo[v].push_back(u);
        pesos[u][v] = peso; // peso da aresta 0-1  = 50 por exemplo
        pesos[v][u] = peso; // 1 - 0 = igual
    }

    // inicializações
    vector<int> dist(n + 1);
    vector<int> pre(n + 1, -1);
    dist[1] = 0;
    for (int i = 2; i <= n; i++)
    {
        dist[i] = numeric_limits<int>::max();
    }

    dijkstra(grafo, dist, pre, n, pesos, m);

    for (int i = 1; i <= n; i++)
    {
        cout << "Distância mínima até o vértice " << i << ": " << dist[i] << endl;
        cout << "Predecessor de " << i << ": " << pre[i] << endl;
        cout << "Caminho: ";
        int atual = i;
        while (atual != -1)
        {
            cout << atual << " ";
            atual = pre[atual];
        }
        cout << endl
             << endl;
    }

    return 0;

    return 0;
}
