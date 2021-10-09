###### tags: `演算法`
# 演算法程式作業五
* 題目:
  Given an undirected graph G(V,E), determine whether there is a **Eulerian Circuit** in G.
  If there is a Eulerian Circuit in G, Output the first lexicographical order(字典序) circuit 
  else, Output "not exist"
|V| <= 10000 , |E| <= 30000

* 演算法設計：
  用link list存每一個相鄰的點，然後再排序。
  選第一個點開始，用遞迴跑，每一次跑相鄰的下一個點，記錄跑過的邊和點，跑完所有的編後，把點放入output中。檢查是不是每個點都是有偶數相鄰邊，或是是否每個點都有跑到。若沒有Eulerian Circuit就output “not exist”，有的話就把output中的東西全部印出來就是答案。

* 時間複雜度分析：
  Sort的部分:因為是link list ⟹ O(E V(E)) 其中V(E)為每個點的邊數 
  看是否都為偶數邊 ⟹ O(V)
  Dfs: 因為每個點的每個邊都跑過⟹ O(E V)
 
* Pseudo code:
```
int main()
{
	Input vertex and edges then sort them// O(E V(E))
    //check odd or not
    for(i=1to vertex) //O(V)
        count=each vertices of edges
        if(Count%2==1||Count<=1)
            exsit=false
    if(exsit)  dfs(1);// O(VE) 
    if(checkend())		
        cout << Output[i]
    else		        
        cout <<"not exist"
}

bool checkend()
{
    if(vertexintheoutput<edge)     
        return false;
    else					       
        return true;
}

void dfs(int index)
{
    ptr=edgelist[index]
    while(ptr)
    {
        ptr=ptr->pointnext;
        if(!ptr->edgefound &&ptr){
        	foundornot[ptr->vertexname, ptr->Adj_vertex] = true;
        	ptr2=edgelist[ptr->Adj_vertex].pointnext;
        	while( ptr2->Adj_vertex!=ptr->vertexname ){
                    ptr2=ptr2->pointnext;
                    ptr,ptr2->edgefound=true;
                    dfs(ptr->Adj_vertex);
            }
        }
    }
    push(index);
}
```
