#include <iostream>
#include <vector>
#include <queue>
#define MAX_TERMS 11000
using namespace std;
struct edge{
    int out; //vertex point to
    int flow; //flow
};
int V,E;
vector<edge> vertex_adj[MAX_TERMS]; //adj-list for each vertex
int BFS(int);
int main() {
    int u,v;
    edge the_edge;
    the_edge.flow=0;

    //input
    cin >> V >> E;
    int Connectivity=E+1;
    for(int i=0;i<E;i++)
    {
        cin>>u>>v;
        the_edge.out=v;
        vertex_adj[u].push_back(the_edge);
        the_edge.out=u;
        vertex_adj[v].push_back(the_edge);
    }

    for(int i=2;i<V+1;i++){//O(V)
        Connectivity=min(Connectivity,BFS(i));
        for(int j=1;j<V+1;j++)
            for(int k=0;k<vertex_adj[j].size();k++)
                vertex_adj[j][k].flow=0;
    }

    cout<<Connectivity<<endl;
    return 0;
}
int BFS(int t){
    int all_flow=0;
    while(1){
        int P[V+1];//parent
        int Flow[V+1];//the flow from S to the vertex
        queue<int> Q;

        for(int i=0;i<V+1;i++)
            Flow[i]=0;
        Flow[1]=INT_MAX;
        Q.push(1);

        while(!Q.empty()){
            int u=Q.front();
            Q.pop();
            for(int i=0;i<vertex_adj[u].size();i++)
            {
                edge &e=vertex_adj[u][i];//adj of u
                if(Flow[e.out]==0 && e.flow<1)//no flow
                {
                    P[e.out]=u;
                    Flow[e.out]=min(Flow[u],1-e.flow);
                    Q.push(e.out);
                }
            }
            if(Flow[t]>0)
                break;
        }
        if(Flow[t]<=0)
            return all_flow;

        for(int i=t;i!=1;i=P[i])//count flow
        {
            for(int j=0;j<vertex_adj[P[i]].size();j++)
            {
                if(vertex_adj[P[i]][j].out==i)
                {
                    vertex_adj[P[i]][j].flow = vertex_adj[P[i]][j].flow+Flow[t]  ;
                    break;
                }
            }
        }
        all_flow = Flow[t] + all_flow;
    }
}
