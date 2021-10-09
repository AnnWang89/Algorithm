#include <iostream>
#include <string>
#define MAX_TERMS 100
#include <time.h>
using namespace std;
int calculate(int,int,char);
void output(int,int,int);
char operand[MAX_TERMS];
int MAX_or_MIN[3][2][MAX_TERMS][MAX_TERMS];//1.[1]max k,[2]min k,2.[0]is before k,[1] is after k, max=1, min =2
int numbers[MAX_TERMS];
int num_index=0,op_index=0;
int dp[4][MAX_TERMS][MAX_TERMS];//0 is k of max, 1 is the max, 2 is the min, 3 is k of min
int main()
{
    string expression;
    cin >> expression;

    double START,END;
    START = clock();
    for(int i=0;i<expression.size();i++)
    {
        if(expression[i]=='-')
        {
            i++;
            while(expression[i]>='0'&&expression[i]<='9')
            {
                dp[1][num_index][num_index]=10*dp[1][num_index][num_index]-(expression[i]-'0');
                dp[2][num_index][num_index]=10*dp[2][num_index][num_index]-(expression[i]-'0');
                i++;
            }
            numbers[num_index]=dp[2][num_index][num_index++];
        }else
        {
            while(expression[i]>='0'&&expression[i]<='9')
            {
                dp[1][num_index][num_index]=10*dp[1][num_index][num_index]+(expression[i]-'0');
                dp[2][num_index][num_index]=10*dp[2][num_index][num_index]+(expression[i]-'0');
                i++;
            }
            numbers[num_index]=dp[2][num_index][num_index++];
        }
        operand[op_index++]=expression[i];
    }

    for(int i=0;i<num_index;i++)
    {
        MAX_or_MIN[1][0][i][i]=1;
        MAX_or_MIN[1][1][i][i]=1;
        MAX_or_MIN[2][0][i][i]=1;
        MAX_or_MIN[2][1][i][i]=1;
    }
    for(int c=1;c<num_index;c++)
    {
        int j=1;
        for(int i=0;j<num_index;i++)
        {
            j=i+c;
            int MAX=calculate(dp[1][i][i],dp[1][i+1][j],operand[i]);
            int MIN=calculate(dp[1][i][i],dp[1][i+1][j],operand[i]);
            for(int k=i;k<j;k++)
            {
                //find max
                if(calculate(dp[1][i][k],dp[1][k+1][j],operand[k]) >= MAX)//max max
                {
                    MAX_or_MIN[1][0][i][j]=1;
                    MAX_or_MIN[1][1][i][j]=1;
                    MAX=calculate(dp[1][i][k],dp[1][k+1][j],operand[k]);
                    dp[0][i][j]=k;
                }
                if(calculate(dp[1][i][k],dp[2][k+1][j],operand[k])>=MAX)//max min
                {
                    MAX_or_MIN[1][0][i][j]=1;
                    MAX_or_MIN[1][1][i][j]=2;
                    MAX=calculate(dp[1][i][k],dp[2][k+1][j],operand[k]);
                    dp[0][i][j]=k;
                }
                if(calculate(dp[2][i][k],dp[1][k+1][j],operand[k])>=MAX)//min max
                {
                    MAX_or_MIN[1][0][i][j]=2;
                    MAX_or_MIN[1][1][i][j]=1;
                    MAX=calculate(dp[2][i][k],dp[1][k+1][j],operand[k]);
                    dp[0][i][j]=k;
                }
                if(calculate(dp[2][i][k],dp[2][k+1][j],operand[k])>=MAX)//min min
                {
                    MAX_or_MIN[1][0][i][j]=2;
                    MAX_or_MIN[1][1][i][j]=2;
                    MAX=calculate(dp[2][i][k],dp[2][k+1][j],operand[k]);
                    dp[0][i][j]=k;
                }

                //find min

                if(calculate(dp[1][i][k],dp[1][k+1][j],operand[k]) <= MIN)//max max
                {
                    MAX_or_MIN[2][0][i][j]=1;
                    MAX_or_MIN[2][1][i][j]=1;
                    MIN=calculate(dp[1][i][k],dp[1][k+1][j],operand[k]);
                    dp[3][i][j]=k;
                }
                if(calculate(dp[1][i][k],dp[2][k+1][j],operand[k])<=MIN)//max min
                {
                    MAX_or_MIN[2][0][i][j]=1;
                    MAX_or_MIN[2][1][i][j]=2;
                    MIN=calculate(dp[1][i][k],dp[2][k+1][j],operand[k]);
                    dp[3][i][j]=k;
                }
                if(calculate(dp[2][i][k],dp[1][k+1][j],operand[k])<= MIN)//min max
                {
                    MAX_or_MIN[2][0][i][j]=2;
                    MAX_or_MIN[2][1][i][j]=1;
                    MIN=calculate(dp[2][i][k],dp[1][k+1][j],operand[k]);
                    dp[3][i][j]=k;
                }
                if(calculate(dp[2][i][k],dp[2][k+1][j],operand[k])<= MIN)//min min
                {
                    MAX_or_MIN[2][0][i][j]=2;
                    MAX_or_MIN[2][1][i][j]=2;
                    MIN=calculate(dp[2][i][k],dp[2][k+1][j],operand[k]);
                    dp[3][i][j]=k;
                }

            }
            dp[1][i][j]=calculate(dp[MAX_or_MIN[1][0][i][j]][i][dp[0][i][j]],dp[MAX_or_MIN[1][1][i][j]][dp[0][i][j]+1][j],operand[dp[0][i][j]]);
            dp[2][i][j]=calculate(dp[MAX_or_MIN[2][0][i][j]][i][dp[3][i][j]],dp[MAX_or_MIN[2][1][i][j]][dp[3][i][j]+1][j],operand[dp[3][i][j]]);
        }
    }
    /*
    cout << "Max:"<<endl;
    for(int i=0;i<num_index;i++)
    {
         for(int j=0;j<num_index;j++)
            cout << dp[1][i][j] << " ";
         cout << endl;
    }
    cout << endl;

    cout << "Min:"<<endl;
    for(int i=0;i<num_index;i++)
    {
         for(int j=0;j<num_index;j++)
            cout << dp[2][i][j] << " ";
         cout << endl;
    }
    cout << endl;
    cout << "k max:" << endl;
    for(int i=0;i<num_index;i++)
    {
         for(int j=0;j<num_index;j++)
            cout << dp[0][i][j] << " ";
         cout << endl;
    }
    cout << endl;
    cout << "k min:" << endl;
    for(int i=0;i<num_index;i++)
    {
         for(int j=0;j<num_index;j++)
            cout << dp[3][i][j] << " ";
         cout << endl;
    }

    for(int i=0;i<num_index;i++)
        cout << numbers[i] << " ";
    cout <<endl;
    for(int i=0;i<op_index;i++)
        cout << operand[i] << " ";
    cout <<endl;
    cout << "answer:"<<endl;
    */
    output(0,num_index-1,1);
    //cout << endl <<"num_index: "<< num_index;
    END = clock();
    //cout << endl << "程式執行所花費：" << (double)clock()/CLOCKS_PER_SEC << " S" ;
    //cout << endl << "進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
    return 0;
}
int calculate(int left,int right,char op)
{
    switch (op){
        case '+':
            return left+right;
        case '-':
            return left-right;
        case '*':
            return left*right;
    }
}
void output(int left,int right,int k_max_min)
{
    if(left==right)
        cout <<dp[1][left][right];
    else{
            int k;
            if(k_max_min==1)
                k=dp[0][left][right];
            else
                k=dp[3][left][right];
            if(left!=k)
                cout << "(" ;
            output(left,k,MAX_or_MIN[k_max_min][0][left][right]);
            if(left!=k)
                cout <<")";
            cout << operand[k];
            if(k+1!=right)
                cout << "(" ;
            output(k+1,right,MAX_or_MIN[k_max_min][1][left][right]);
            if(k+1!=right)
                cout <<")";
    }
}
