#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>> grafo, vector<int> &pre, int vert, vector<int> &pai, int &cont)
{
    cout << vert << endl;
    pre[vert] = cont++; // pre do vert q entra = 0

    for(auto u: grafo[vert]) // vai na lista de adj de cada vert
    {
        if(pre[u] == -1) // se pre for 1 = nao visitado
        {
            pai[u] = vert;
            dfs(grafo,pre,u,pai,cont); //visita 
        }
    }
    
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
    vector<int> pre(n+1, -1); //inicializando o vetor todo com -1, com o n de 1 a 5  
    vector <int> pai(n+1,-1); 

    for(int i = 0; i < m; i++)
    {
       int u,v;
       cin >> u >> v;

       grafo[u].push_back(v);//lendo os arcos e pondo na lista de adj quem é vizinho de qm
       grafo[v].push_back(u);

    }


   //print_grafo(grafo);
    dfs(grafo,pre, 1,pai, cont);
    
    cout << "valores do pre" << endl;
    for(auto x: pre)
    {
        cout << x << endl;
    }
    
    cout << "valores do pai" << endl;
    for(auto x: pai)
    {
        cout << x << endl;
    }
        

  return 0;
} 