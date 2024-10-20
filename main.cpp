#include <iostream>
#include <vector>
#include <pair>
#include <queue>

using namespace std;

#define pl pair<int,int>
#define pll pair<pair<int,int>,int>
#define plp pair<int,pair<int,int>>

class SolutionThree{
public:
    int minCost(vector<vector<int>>& grid) {
        /*1 the cell to the right | i,j | i,j+1
          2 to the left           | i,j | i,j-1
          3 to the lower          | i,j | i+1,j
          4 to the upper cell     | i,j | i-1,j
          start cell (0,0),  ends cell (m-1,n-1)*/
        int n=grid.size();
        int m=grid[0].size();

        map<pl,vector<pll>> graph; //pair<int,int> | pair<pair<int,int>,int>
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(j<m-1) graph[{i,j}].push_back({{i,j+1},grid[i][j]==1 ? 0:1}); //si no es ni 1 ni 2 ni 3 ni 4, será 1
                if(i<n-1) graph[{i,j}].push_back({{i+1,j},grid[i][j]==3 ? 0:1});
                if(j>0) graph[{i,j}].push_back({{i,j-1},grid[i][j]==2 ? 0:1});
                if(i>0) graph[{i,j}].push_back({{i-1,j},grid[i][j]==4 ? 0:1});
            }
        }
        priority_queue<plp,vector<plp>,greater<plp>> q;  //pair<int,pair<int,int>> | distancia, coordenadas x y
        q.push({0,{0,0}});
        vector<vector<int>> dist(n,vector<int>(m,1e9));
        dist[0][0]=0;

        while(!q.empty()){
            auto node=q.top().second;
            int distance=q.top().first;
            q.pop();
            if(distance!=dist[node.first][node.second]) continue; //se ignora así mismo
            for(auto& it: graph[node]){ //coordenadas | proximas coordenadas y 0 o 1
                auto adj=it.first;
                int weight=it.second;
                int x=adj.first; //coordenada x
                int y=adj.second; //coordenada y
                if(weight+distance < dist[x][y]){
                    dist[x][y]=weight+distance;
                    q.push({weight+distance,adj}); //el menor peso posible, coordenadas
                }
            }
        }
        return dist[n-1][m-1]==1e9 ? -1: dist[n-1][m-1];
    }
};

int main(){
    return 0;
}