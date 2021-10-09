###### tags: `演算法`
# 演算法程式作業三
* 題目:
  A mathematical expression is given without parentheses. Design an algorithm to parenthesize the expression such that the value of the expression is maximized.
  For example, consider the expression: 2+7*5. There are two ways to parenthesize the expression 2+(7*5) = 37 and (2+7)*5 = 45, so in this case, your algorithm should output the second expression. Here, you may assume the given expressions contain only 3 kinds of binary operators ‘+’, ‘-’, and ‘*’.
  Input: expression Ex: 2+7*5-3*6
  Output: (((2+7)*5)-3)*6 or ((((2+7)*5)-3)*6)

  1 <= expression's length <= 30
  if there are several solutions, output one of them.
  
* 演算法設計：
  用 Dynamic Programming 計算最大值並記錄，在用遞迴找出紀錄的地方並加上括號。
  利用 dp[i][j]=max𝑖≤𝑘≤𝑗(dp[i][k] op[k] dp[k+1][j]) 設計演算法
* 時間複雜度分析：
  dp[i][j]=max𝑖≤𝑘≤𝑗 (dp[i][k] op[k] dp[k+1][j])
  要一格 dp 的表格 dp[i][j]，需要θ(j-i)的時間
  i 是從 0 跑到 n，j 是從 i 跑到 n，所以其實間複雜度為:
![](https://i.imgur.com/EE9TFJN.png)


Pseudo code：
```
int main(){
    operand[], number[],op_index , num_index ,dp[][][],maxormin[][][][];
    // dp :0 is k of max, 1 is the max answer, 2 is the min answer, 3 is k of min,
    // maxormin[][][][]:first is 1 max, 2 min, second 0 is before k, 1 is after k
    // dp and maxormin last two are index
    if(i=j) dp[1and2][i][j]= number[i]
    for(int c=1;c<num_index;c++) {//i和j的差
        for(int i=0;j<num_index;i++){ 
            j=i+c;
            dp[1][i][j] = max(calculate(dp[1or2][i][k], dp[1or2][k+1][j], operand[k])
            dp[2][i][j] = min(calculate(dp[1or2][i][k], dp[1or2][k+1][j], operand[k])
            dp[0][i][j]=k//save the k of max
            dp[3][i][j] =k// save the k of min
            maxormin[1&2][1&0][i][j]=1 or 2
        }
    }
    output(0,num_index-1,1);
}

calculate(left, right, op){
    switch (op)
        case '+': return left + right; 
        case '-': return left - right; 
        case '*': return left*right;
}

output(left, right,kmaxormin){
    if(left=right)   
        return  dp[1][left][right];
    else{
		if  kmaxormin=1        	
            k=dp[0][left][right];
        else						
            k=dp[3][left][right];
            return "("+output(left,k, kmaxormin)+")"+operand[k]+"("+output(k+1,left, kmaxormin)+")"
    }
}

```
* 實驗分析 : 畫出 n 與時間關係 t 的折線圖
![](https://i.imgur.com/cqRrW5J.png)
