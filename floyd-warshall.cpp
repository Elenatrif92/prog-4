
#include <bits/stdc++.h>
using namespace std;

const int inf=1e9;

void pecati_mat(vector<vector<int>>& dist){
    int n=dist.size();
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if (dist[i][j]>=inf) cout << "inf ";
            else cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}
void floydWarshall(vector<vector<int>>& dist){
    int v=dist.size(); //nodes
    
    for(int k=0; k<v; k++){
        for(int i=0; i<v; i++){
            for(int j=0; j<v; j++){
                if(dist[i][k]!=inf && dist[k][j]!=inf){
                    dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j]);
                }
            }
        }
       // cout << k << "  ///////////  ";
        pecati_mat(dist);
    }
}


int main()
{
    int n=0;
    cin >> n; //br teminja
    vector<vector<int>> dist(n, vector<int>(n));
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << "Vnesi pat od "<<i<<" do "<< j<<" : (num/'inf')" << endl;
            string s;
            cin >> s;
            if (s=="inf") dist[i][j]=inf;
            else dist[i][j]=stoi(s);//i do j pat
             
        }
    }
    
    
    floydWarshall(dist);
    
    //pecati_mat(dist);
    
    return 0;
}