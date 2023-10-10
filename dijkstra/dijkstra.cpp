#include <bits/stdc++.h>
using namespace std;

// vetor dist = cada indice tem a dist do vertice 0-indice
// vetor pre = tem o pai
// devo comparar os pesos dos adj para saber quem por na distancia
// cria uma fila de prioridade onde cada elemento é um par de inteiros, ordenados em ordem crescente de distância acumulada
void dijkstra(vector<vector<int>> &grafo, vector<int> &dist, vector<int> &pre, vector<vector<int>> &pesos)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila; // fila de prioridade com especificação GREATER = menor p maior
    fila.push({0, 1});              //mudar p -i e nao 1 sempre         // sendo 1 o vert inicial sua distancia ate ele mesmo é 0, o par é (dist[v],v)

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
            cout << "-i: vértice inicial" << endl;
            return 0;
        } 

        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1) {
            output_file = argv[++i];
        } 
        
        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1) {
            input_file = argv[i + 1];
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
    vector<vector<int>> pesos(n + 1, vector<int>(n + 1, numeric_limits<int>::max())); // inicializar com valores grandes
    vector<vector<int>> grafo(n + 1);

    for (int i = 0; i < m; i++)
    {

        int u, v, peso;
        fin >> u >> v >> peso;
        
        if(u <0 || v < 0 || peso < 0)
        {
            cout << "entrada inválida" << endl;
            return 0;
        }

        grafo[u].push_back(v); // lendo os arcos e pondo na lista de adj quem é vizinho de qm
        grafo[v].push_back(u);
        pesos[u][v] = peso; // peso da aresta 0-1  = 50 por exemplo
        pesos[v][u] = peso; // 1 - 0 = igual
    }

    // inicializações
    vector<int> dist(n + 1);
    vector<int> pre(n + 1, -1);
    dist[vert_inicial] = 0; // mudar p -i e nao sempre 1
    for (int i = 1; i <= n; i++)
    {
        if(i != vert_inicial)
        {
        dist[i] = numeric_limits<int>::max();
        }
    }

    fin.close();

    if (!(output_file == "")) {
        ofstream fout(output_file);
        if (!fout) {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        if (show_solution) {
            dijkstra(grafo, dist, pre,pesos);

    for (int i = 1; i <= n; i++)
    {
        if(dist[i] == numeric_limits<int>::max())
        {
            dist[i] =-1; //vert inalcançavel
        }
fout <<  i << ":" << dist[i] << endl;
    }


            fout.close();
            return 0;
        }
        else {
             dijkstra(grafo, dist, pre,pesos);

    for (int i = 1; i <= n; i++)
    {
        if(dist[i] == numeric_limits<int>::max())
        {
            dist[i] =-1; //vert inalcançavel
        }
fout <<  i << ":" << dist[i] << endl;
    }

}


        fout.close();
    } 
    else 
    {
        dijkstra(grafo, dist, pre,pesos);
        for (int i = 1; i <= n; i++)
        {
            if(dist[i] == numeric_limits<int>::max())
                dist[i] =-1; //vert inalcançavel
        
            cout  << i << ":" << dist[i];

            if (i != n)
            {
                cout << " ";
            }
            else
            {
                cout << endl;
            }
        }
    }



    return 0;

}