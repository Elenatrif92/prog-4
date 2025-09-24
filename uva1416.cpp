#include <bits/stdc++.h>
using namespace std;

const long long inf=1e18; 

void floydWarshall(vector<vector<long long>>& dist){
    int v=dist.size(); //nodes
    
    for(int k=1; k<v; k++){
        for(int i=1; i<v; i++){
            for(int j=1; j<v; j++){
                if(dist[i][k]!=inf && dist[k][j]!=inf){
                    dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
       // cout << k << "  ///////////  ";
        //pecati_mat(dist);
    }
}

int main() {
    int n=0, m=0;//nodes,edegs
    long long L=0;
    cin >> n >> m >> L;

    vector<vector<long long>> dist(n+1, vector<long long>(n+1, L));
    
    for(int i=1; i<=n; i++) 
        dist[i][i] = 0;
     
    
    vector<vector<long long>> edges;
    
    long long dis, a, b;
    for(int i=0; i<m; i++){
        cin >> a >> b >> dis;
        
        dist[a][b]=min(dist[a][b],dis);
        dist[b][a]=min(dist[b][a],dis);
        
        edges.push_back({a,b,dis});
    }
    vector<vector<long long>> original_dist=dist; 
    
    floydWarshall(dist);
    long long c = 0;
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            c+=dist[i][j];
        }
    }

    long long max_c = c;

    
    for(auto e : edges){
        long long u=e[0], v=e[1], s=e[2];
        vector<vector<long long>> new_dist = original_dist; 
        
        new_dist[u][v] = new_dist[v][u] = L;//od zadacata

        
        floydWarshall(new_dist);

        long long new_c = 0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                new_c += new_dist[i][j];

        max_c = max(max_c, new_c);
    }

    cout << c << " " << max_c << endl;

    return 0;
}
