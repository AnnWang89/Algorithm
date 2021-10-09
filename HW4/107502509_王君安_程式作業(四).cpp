#include <iostream>
#include <queue>
#include <string>
#define MAX_TERMS 100
using namespace std;

struct node{
    int frequency;
    int index;
    node* rightchildren;
    node* leftchildren;
};
node* pq[MAX_TERMS];
void push(node*);
node* pop();
int top=-1;
void optinal_code(node*,int);
int code[MAX_TERMS];
int main()
{
    int N;
    char alphabet[MAX_TERMS];
    node element[MAX_TERMS];
    string code_string[MAX_TERMS];
    cout << "Input a number N: \n";
    cin >> N;

    for(int i=0;i<N;i++)
    {
        cin >> alphabet[i];
        cin >> element[i].frequency;
        element[i].index=i;
        element[i].leftchildren=NULL;
        element[i].rightchildren=NULL;
        push(&element[i]);
    }
    //cout <<"OK~~\n";
    while(top>0)
    {
        //cout <<"In\n";
        node* ptr = new node;
        //node popnode1=pop();
       // node popnode2=pop();
        ptr->leftchildren=pop();
        ptr->rightchildren=pop();
        ptr->index=-1;
        ptr->frequency=ptr->leftchildren->frequency+ptr->rightchildren->frequency;
        push(ptr);
    }
    //cout <<"Tree end\n";
    //node* popnode=pop();
    node* ptr=pop();
    //cout <<ptr->frequency<<endl;
    //cout <<"7 :"<< ptr->rightchildren->frequency<<endl;
    //cout <<"3 :"<<ptr->rightchildren->leftchildren->frequency<<endl;
    //cout <<"2 :"<<ptr->rightchildren->leftchildren->rightchildren->frequency<<endl;
    optinal_code(ptr,0);
    for(int i=0;i<N;i++)
    {
        while(code[i]>0)
        {
            if((code[i]%10)==1)
                code_string[i]="0"+code_string[i];
            else
                code_string[i]="1"+code_string[i];
            code[i]=code[i]/10;
        }
    }
    cout <<endl<<"Output:"<<endl;
    for(int i=0;i<N;i++)
        cout << alphabet[i] <<" "<< code_string[i]<<endl;
    return 0;
}
void push(node* Insert)
{
    //cout <<"push\n";
    pq[++top]=Insert;
    int now=top;
    while(now>0 && pq[now]->frequency < pq[(now-1)/2]->frequency)
    {
        node* Swap;
        Swap = pq[now];
        pq[now] = pq[(now-1)/2];
        pq[(now-1)/2] = Swap;
        now=(now-1)/2;
    }
}
node* pop()
{
    //cout <<"pop\n";
    node* minnode=pq[0];
    pq[0]=pq[top];
    top--;
    int now=0;
    node* Swap;
    while(now<top)
    {
        //cout <<"now:" <<now<<"\n";
        //cout <<"top:" <<top<<"\n";
        if(now*2+2<=top)
        {
            if(pq[now]->frequency > pq[now*2+2]->frequency || pq[now]->frequency > pq[now*2+1]->frequency)
            {
                if(pq[now*2+2]->frequency>pq[now*2+1]->frequency)
                {
                    Swap = pq[now];
                    pq[now] = pq[now*2+1];
                    pq[now*2+1] = Swap;
                    now=now*2+1;
                }else
                {
                    Swap = pq[now];
                    pq[now] = pq[now*2+2];
                    pq[now*2+2] = Swap;
                    now=now*2+2;
                }
            }else
                break;

        }else if(now*2+1<=top)
        {
            if(pq[now]->frequency > pq[now*2+1]->frequency)
            {
                Swap = pq[now];
                pq[now] = pq[now*2+1];
                pq[now*2+1] = Swap;
                now=now*2+1;
            }else
                break;
        }else
            break;
    }
    return minnode;
}
void optinal_code(node* ptr,int num)
{
    //cout << "num:"<<num<<endl;
    if(ptr->leftchildren)
    {
        //cout <<ptr->index<<endl;
        //cout <<"ptr->frequency :"<< ptr->frequency<<endl;
        optinal_code(ptr->leftchildren,num*10+1);
    }
    if(ptr->rightchildren)
    {
        //cout <<ptr->index<<endl;
        //cout <<"ptr->frequency"<< ptr->frequency<<endl;
        optinal_code(ptr->rightchildren,num*10+2);
    }

    if(!(ptr->leftchildren||ptr->rightchildren))
        code[ptr->index]=num;
}
