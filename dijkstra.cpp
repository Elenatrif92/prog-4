
#include <bits/stdc++.h>
using namespace std;

void dijkstra(vector<int> &distances, vector<vector<pair<int,int>>>& graph){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; //distanca, teme
    pq.push({0,0});
    
    vector<bool> visited(graph.size(), false);
    
    while(!pq.empty()){
        auto u=pq.top(); //distanca, teme
        pq.pop();
        
        auto pocetno=u.second;
        
        if (visited[pocetno]) continue;  
        visited[pocetno]=true;
        
        for(auto next:graph[u.second]){ //adjacentni na temeto u
            auto to=next.second, w=next.first;
            
            if(distances[to] > distances[pocetno] + w) //do ovde plus ova weight dali e < od prethodnoto
            {
                distances[to]=distances[pocetno]+w;
                pq.push({distances[to], to});
            }
        }
    }
}

int main()
{
    int num_teminja=0, num_rebra=0;
    int kade=0;
    cin >> num_teminja >> num_rebra;
    vector<vector<pair<int,int>>> graph(num_teminja);
    
    vector<int> distances(num_teminja, INT_MAX);
    distances[0]=0;
    
    int a=0, b=0, dist=0;
    for(int i=0; i<num_rebra; i++){
        cin >> a >> b >> dist;
        graph[a].push_back({dist,b});
        graph[b].push_back({dist, a});//izbrisi ako treba directed, samo a->b bez b->a
    }
    
    dijkstra(distances, graph);
    
    for(auto dis:distances){
        cout << ((dis==INT_MAX)?-1:dis) << " ";
    }
    
//  9
// 14
// 0 1 4
// 0 7 8
// 1 2 8
// 1 7 11
// 2 3 7
// 2 8 2
// 2 5 4
// 3 4 9
// 3 5 14
// 4 5 10
// 5 6 2
// 6 7 1
// 6 8 6
// 7 8 7
// 0 4 12 19 21 11 9 8 14 
    return 0;
}