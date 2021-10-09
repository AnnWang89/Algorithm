###### tags: `演算法`
# 演算法程式作業六

* 題目:
  Given a simple undirected connected graph G, find the edge connectivity on G.
  **Input**: first line contains two integers |V| and |E|, following |E| lines are the edge(u,v) ∈ G
  **Output**: a number represents edge connectivity.

* 演算法設計：
  以adj list的方式去存邊和點的關係。
  用Ford-Fulkerson & Edmonds-Karp 的方法作，就是用BFS去跑，跑BFS的方式存在Q中，並將每個邊的容量都當作是1。

* 時間複雜度分析：
  Edmonds-Karp 的時間複雜度為O(VE^2)
 
* Pseudo code:
```
struct edge{ out, flow}, vertex_adj[][]; //adj-list for each vertex
main() {
    input each edge(u,v) and V, E//set all flow=0
    Connectivity=E+1;
    for i=2~i<V+1
        Connectivity=min(Connectivity,BFS(i))
        For j=1~V+1
            for k=0~vertex_adj[j].size()
                vertex_adj[j][k].flow=0
    output Connectivity
}
int BFS(int t){
    all_flow=0;
    while(1)
        P[], Flow[]=0;//parent and the flow from S to the vertex
        Q;//a queue
        Flow[1]=INF
        Q.push(1);
        while(!Q.empty())
            u= Q.pop()            
            for i=0~vertex_adj[u].size()
                &e=vertex_adj[u][i];//adj of u
                if(Flow[e.out]==0 && e.flow<1)//no flow
                    P[e.out]=u
                    Flow[e.out]=min(Flow[u],1-e.flow)
                    Q.push(e.out)
            if(Flow[t]>0)
                break
        if(Flow[t]<=0)  return all_flow;//不能流了
        for(int i=t;i!=1;i=P[i])//count flow
            for j=0~vertex_adj[P[i]].size()
                if(vertex_adj[P[i]][j].out==i)
                    vertex_adj[P[i]][j].flow = Flow[t] + vertex_adj[P[i]][j].flow;
                    break;
        all_flow = Flow[t] + all_flow
}
```
