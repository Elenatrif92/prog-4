
#include <bits/stdc++.h>
using namespace std;


vector<int> bellman(int start, vector<vector<int>>& graf, int teminja) {
    vector<int> dist(teminja, 1e8);
    dist[start] = 0;

    for (int i = 0; i < teminja; i++) {
        
        for (auto &next : graf) {
            int u = next[0], v = next[1], w = next[2];
            if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                
                // posle nth iteracija ima neg ciklus
                if (i == teminja - 1) 
                    return {-1};
                
                dist[v] = dist[u] + w;
                
            }
        }
    }

    return dist;
}

int main() {

    srand(time(0));
    
    
    vector<vector<int>> graf;
    int a = 0, b = 0, w = 0;
    
    
    ofstream fout("output.txt");
    
    for(int h=0; h<10; h++){
        //gen graf
        graf.clear();
    
        if(fout.is_open())
        {
            int teminja = rand() % 30 + 10, rabovi = rand() % 50 + 20;
            fout << endl;
            fout << "teminja i rabovi: " << teminja << " " << rabovi << endl;
            for (int i = 0; i < rabovi; i++) {
                int u = rand() % teminja;
                int v = rand() % teminja;
                while (v == u) v = rand() % teminja; // avoid self-loop
                int w = (rand() % 21) - 3;          // weights in [-3, 17]
                graf.push_back({u, v, w});
            }
            
            //pecati u fajl
            for(int i=0; i<graf.size(); i++){
                auto reb=graf[i];
                fout << reb[0] << " " << reb[1] << " " << reb[2] << endl;
                
            }
            fout << endl << endl;
            vector<int> dist = bellman(0, graf, teminja);
            
            if (dist.size() == 1 && dist[0] == -1) {
                fout << "Negative cycle detected\n";
            } 
            else {
                for (auto d : dist) {
                    if (d == 1e8) fout << "INF ";
                    else fout << d << " ";
                    
                    
                }
                
            }
            
            fout<< '\n';
        }
        
        
    } 
    
    fout.close();

    return 0;
}
