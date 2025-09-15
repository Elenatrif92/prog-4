
#include <bits/stdc++.h>
using namespace std;

int teminja=0, rabovi=0;

vector<int> bellman(int start, vector<vector<int>>& graf){
    vector<int> dist(teminja, 1e8);
    dist[0]=0;
    
    for(int i=0; i<teminja; i++){
        
        for(auto next:graf){
            int u=next[0], v=next[1], w=next[2];
            if(dist[u] != 1e8 && dist[u] + w < dist[v]){
                
                // posle vth iteracija ima neg ciklus
                if(i == teminja - 1)
                    return {-1};
                
                dist[v]=dist[u]+w;
                    
            }
        }
    }
    
   return dist;
}

int main()
{
   
    cin >> teminja >> rabovi;
    vector<vector<int>> graf;
    int a=0, b=0, w=0;
    for(int i=0; i<rabovi; i++){
        cin >> a >> b >> w;
        graf.push_back({a,b,w});
    }
    
    vector<int> dist=bellman(0, graf);
    
    
    ofstream fout("output.txt"); // otv fajl
    if (dist.size() == 1 && dist[0] == -1) 
        fout << "Negative cycle detected\n";
    
    else {
        for (auto d : dist) {
            if (d == 1e8) fout << "INF ";
            else fout << d << " ";
        }
        
    }

    fout.close(); // save and close file
    
    
    return 0;
}