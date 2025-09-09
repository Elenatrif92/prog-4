
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int num_teminja=0, num_rebra=0;
    int kade=0;
    cin >> num_teminja >> num_rebra;
    vector<vector<int>> graph(num_teminja);
    
    int a=0, b=0;
    for(int i=0; i<num_rebra; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    for(int i=0; i<graph.size(); i++){
        for(int j=0; j<graph[i].size(); j++){
            cout << graph[i][j] << " ";
        }
        if(graph[i].size()==0) cout << "*empty*";
        cout << endl;
    }
    return 0;
}