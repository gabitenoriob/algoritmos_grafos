#include <bits/stdc++.h>

using namespace std;

void bfs(vector<vector<int>> grafo, vector<int> &pai, int vert_inicial, vector<int> &pre)
{
    int cont= 0;
    vector <int> dist (grafo.size(), INT_MAX);
    queue<int>fila;
    fila.push(vert_inicial);
    dist[vert_inicial] = 0;

    while(! (fila.empty())){
        int w = fila.front();
        pre[w] = cont++;
        cout << w << endl;
        fila.pop();

        for(auto vizinho : grafo[w])
        {
            if(dist[w] + 1 < dist[vizinho]){
                dist[vizinho] = dist[w] + 1;
                pai[vizinho] = w;
                fila.push(vizinho);
            }
        }   
    }
    
    cout << "distancia: ";
    for(int i = 1; i < dist.size(); i++)
    {
        cout << i << ": " << dist[i] << " ";
    }
    
    cout << endl;

}


void print_grafo(vector<vector<int>> grafo)
{
    for(int i = 0; i < grafo.size(); i++)
    {
       cout<< i << ":" ;
       for(auto print: grafo[i])
       {
           cout << print << " -> " ;
       }
       cout << endl;
    }
    
}



int main() {

    int n,m, cont = 0;
    cin >> n >> m;
    vector<vector<int>> grafo(n +1); //lista de adj
    vector<int> pai(n+1, -1); //inicializando o vetor todo com -1, com o n de 1 a 5  
    vector<int> pre(n+1, -1);

    for(int i = 0; i < m; i++)
    {
       int u,v;
       cin >> u >> v;

       grafo[u].push_back(v);//lendo os arcos e pondo na lista de adj quem é vizinho de qm
       grafo[v].push_back(u);

    }


   //print_grafo(grafo);
    bfs(grafo,pai,1,pre);
    
    cout << "valores do pai" << endl;
    for(auto x: pai)
    {
        cout << x << endl;
    }
     cout << "valores do pre" << endl;
    for(auto x: pre)
    {
        cout << x << endl;
    }
    

  return 0;
} 