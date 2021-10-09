#include <iostream>
#define MAX_TERMS 80000
using namespace std;
struct node{
    int Adj_vertex;
    bool edgefound;
    node* pointnext;
    int vertexname;
};
void push(int);
bool checkend();
int Output[MAX_TERMS];
node edgelist[MAX_TERMS];
bool foundornot[MAX_TERMS];
void dfs(int );
int vertex,edge;
int top=-1;
bool exsit = true;
int main()
{
    cin >> vertex >>edge;
    for(int i=1;i<vertex+1;i++)//initial
    {
        edgelist[i].Adj_vertex=-1;
        edgelist[i].pointnext=NULL;
        edgelist[i].vertexname=i;
        foundornot[i]=false;
    }
    //put in the list
    int v1,v2;
    int Swap,Swap2;
    node* ptr;
    for(int i=0;i<edge;i++)
    {
        cin >> v1 >> v2;
        //v1
        ptr = &edgelist[v1];
        while(ptr->pointnext)
            ptr=ptr->pointnext;
        ptr->pointnext=new node;
        ptr->pointnext->Adj_vertex=v2;
        ptr->pointnext->edgefound=false;
        ptr->pointnext->pointnext=NULL;
        ptr->pointnext->vertexname=v1;
        //sort
        ptr = edgelist[v1].pointnext;
        while(ptr->Adj_vertex <=v2)
        {
            ptr=ptr->pointnext;
            if(!ptr)
                break;
        }
        Swap2=v2;
        while(ptr)
        {
            Swap=ptr->Adj_vertex;
            ptr->Adj_vertex=Swap2;
            Swap2=Swap;
            ptr=ptr->pointnext;
        }
        //sort end
        //v2
        ptr = &edgelist[v2];
        while(ptr->pointnext)
            ptr=ptr->pointnext;
        ptr->pointnext=new node;
        ptr->pointnext->Adj_vertex=v1;
        ptr->pointnext->edgefound=false;
        ptr->pointnext->pointnext=NULL;
        ptr->pointnext->vertexname=v2;
        ptr = edgelist[v2].pointnext;
        while(ptr->Adj_vertex<=v1)
        {
            ptr=ptr->pointnext;
            if(!ptr)
                break;
        }
        Swap2=v1;
        while(ptr)
        {
            Swap=ptr->Adj_vertex;
            ptr->Adj_vertex=Swap2;
            Swap2=Swap;
            ptr=ptr->pointnext;
        }
        //sort end
    }
    //check odd or not
    for(int i=1;i<=vertex;i++)
    {
        //cout <<"vertex "<<i<<" :"<<endl;
        ptr = &edgelist[i];
        ptr=ptr->pointnext;
        int Count=0;
        while(ptr)
        {
            //cout << ptr->Adj_vertex<< " ";
            ptr=ptr->pointnext;
            Count++;
        }
        if(Count%2==1||Count<=1)
        {
            exsit=false;
            break;
        }
        //cout << endl;
    }
    if(exsit)
        dfs(1);
    //out put
    if(checkend())
    {
        for(int i=top;i>=0;i--)
            cout << Output[i]<<" ";
    }else
        cout <<"not exist";
    cout <<endl;
    return 0;
}
void push(int vertex)
{
   Output[++top]=vertex;
}
bool checkend()
{
    if(top<edge)
        return false;
    else
        return true;
}
void dfs(int index)
{
    node* ptr;
    node* ptr2;
    ptr=&edgelist[index];
    while(ptr)
    {
        ptr=ptr->pointnext;
        if(ptr){
            if(!ptr->edgefound){
                ptr->edgefound=true;
                foundornot[ptr->vertexname]=true;
                foundornot[ptr->Adj_vertex]=true;
                ptr2=edgelist[ptr->Adj_vertex].pointnext;//ptr2 just mark it
                while(ptr2->Adj_vertex!=ptr->vertexname)
                    ptr2=ptr2->pointnext;
                ptr2->edgefound=true;
                dfs(ptr->Adj_vertex);
            }
        }
    }
    push(index);
}
