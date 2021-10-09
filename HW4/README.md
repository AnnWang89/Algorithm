###### tags: `演算法`
# 演算法程式作業四
* 題目:
  Huffman encoding
  
  **Input**: First line containing a single integer N,  Each of the next N lines is a alphabet and it's frequency.
  **Output**: binary character code

* 演算法設計：
  把所有的frequency都放進priority queue裡。
  再來建一棵樹，每次新增一個node，拿出priority queue裡最小的2個，分別為左右小孩，而這個node的 frequency就會是左右小孩的frequency相加。
  完成後找出樹的葉子，從root開始找，往左就填0，往右就填1，最後就可以找出binary character code

* 時間複雜度分析：
  每次都拿最小的兩個放tree→O(n)
  其中push或pop都是→O(log(n))
  找leaf的時候 worst case→O(n) ⇒ T(n)= O(nlog(n))
 

* Pseudo code：
```
struct node{ frequency,index,rightchildren,leftchildren}
main()
{
   	N, alphabet[], element[] //push all element in the priority queue (heap)
code[];
    while(top>0)//O(n)
    {
        node* ptr = new node;
        ptr->leftchildren=pop();//從priority queue 裡拿出最小的(O(log(n))
        ptr->rightchildren=pop();//從priority queue 裡拿出最小的
        ptr->index=-1;
        ptr->frequency=ptr->leftchildren->frequency+ptr->rightchildren->frequency;
        push(ptr);
    }
    node* ptr=pop();
    optinal_code(ptr,0);
    for(int i=0;i<N;i++)
        cout << alphabet[i] <<" "<< code[i]
    return 0;
}
void optinal_code(node* ptr,int num)
{
    if(ptr->leftchildren)
        optinal_code(ptr->leftchildren, num*10+‘0’);
    if(ptr->rightchildren)
        optinal_code(ptr->rightchildren, num*10+‘1’);
    if(!(ptr->leftchildren||ptr->rightchildren))
        code[ptr->index]=num;
}
```
