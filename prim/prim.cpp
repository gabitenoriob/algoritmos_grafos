#include <bits/stdc++.h>
#include <fstream>

#include <bits/stdc++.h>

using namespace std;

void prim(vector<vector<int>> pesos, vector<vector<int>> grafo, vector<int> &agm, vector<bool> &visited, vector<int> &dist, int init, int n)
{

    priority_queue<pair<int, pair<int, int>>> fila; // fila de prioridade com especificação GREATER = menor p maior
    dist[init] = 0;
    fila.push({0, {init, init}}); // mudar p -i e nao 1 sempre         // sendo 1 o vert inicial sua distancia ate ele mesmo é 0, o par é (dist[v],v)
    int count = 0;

    while (!fila.empty())
    {
        pair<int, int> edge = fila.top().second; // segundo /segunda parte do par / y (x,y) -> elemento do topo -> da fila
        fila.pop();
        int u = edge.first; // vertice atual
        int pai = edge.second; // vertice que antes do atual
        visited[u] = true;

        if (count != n && pai != u && pesos[pai][u] == dist[u])
        {
            if (agm[pai] == -1)
            {
                agm[pai] = u;
            }
            else if (agm[u] == -1)
            {
                agm[u] = pai;
            }

            count++;
        }

        for (auto adjacente : grafo[u])
        {
            int v = adjacente;
            int peso_uv = pesos[u][v];

            if (visited[v])
                continue;

            if (peso_uv < dist[v])
            {
                dist[v] = peso_uv;
                fila.push({-peso_uv, {v, u}}); // ordena de forma descrescente mesmo, só que com abordagem negativa!
            }
        }
    }
}

vector<priority_queue<int>> sort_agm(vector<int> agm, int n)
{
    vector<priority_queue<int>> graph_agm(n + 1);

    // Ordenando a arvore
    for (int i = 0; i <= n; i++)
    {
        if (agm[i] != -1)
        {
            if (i > agm[i])
            {
                graph_agm[agm[i]].push(-i);
            }
            else
            {
                graph_agm[i].push(-agm[i]);
            }
        }
    }

    return graph_agm;
}

int main(int argc, char *argv[])
{
    string input_file = "";
    string output_file = "";
    bool show_solution = false;
    int vert_inicial = 1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            cout << "Help:" << endl;
            cout << "-h: mostra o help" << endl;
            cout << "-o <arquivo>: redireciona a saida para o 'arquivo'" << endl;
            cout << "-f <arquivo>: indica o 'arquivo' que contém o grafo de entrada" << endl;
            cout << "-s: mostra a solução (em ordem crescente)" << endl;
            cout << "-i: vértice inicial" << endl;
            return 0;
        }

        else if (strcmp(argv[i], "-o") == 0 && i < argc - 1)
        {
            output_file = argv[++i];
        }

        else if (strcmp(argv[i], "-f") == 0 && i < argc - 1)
        {
            input_file = argv[++i];
        }

        else if (strcmp(argv[i], "-s") == 0)
        {
            show_solution = true;
        }

        else if (strcmp(argv[i], "-i") == 0 && i < argc - 1)
        {
            vert_inicial = atoi(argv[++i]);
        }
    }

    if (input_file == "")
    {
        cerr << "No input file specified. Use the -f parameter." << endl;
        return 1;
    }

    ifstream fin(input_file);
    if (!fin)
    {
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

        if (u < 0 || v < 0 || peso < 0)
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
    vector<int> agm(n + 1, -1);
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, numeric_limits<int>::max());

    fin.close();

    prim(pesos, grafo, agm, visited, dist, vert_inicial, n);

    int soma = 0;

    for (int i = 1; i <= n; i++)
        if (dist[i] != numeric_limits<int>::max())
            soma += dist[i];

    if (show_solution)
    {
        vector<priority_queue<int>> graph_agm = sort_agm(agm, n);

        for (int i = 0; i < graph_agm.size(); i++)
        {
            while (!graph_agm[i].empty())
            {
                int j = graph_agm[i].top();
                graph_agm[i].pop();

                cout << "(" << i << "," << -j << ") ";
            }
        }

        cout << endl;
    }
    else
    {

        cout << soma << endl;
    }

    if (!(output_file == ""))
    {
        ofstream fout(output_file);
        if (!fout)
        {
            cerr << "Could not open output file: " << output_file << endl;
            return 1;
        }

        fout << "custo da agm = " << soma << endl;

        if (show_solution)
        {
            vector<priority_queue<int>> graph_agm = sort_agm(agm, n);

            for (int i = 0; i < graph_agm.size(); i++)
            {
                while (!graph_agm[i].empty())
                {
                    int j = graph_agm[i].top();
                    graph_agm[i].pop();

                    fout << "(" << i << "," << -j << ") ";
                }
            }

            fout << endl;
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (agm[i] != -1)
                {
                    fout << "(" << i << "," << agm[i] << ") ";
                }
            }

            fout << endl;
        }

        fout.close();
    }

    return 0;
}