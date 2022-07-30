# 「FZOI Round」简单 NOI 模拟赛

|题目名称|题目代号|时空限制|捆绑测试|题目类型|
|:-:|:-:|:-:|:-:|:-:|
|矩阵|matrix|$1\texttt{s}/512\texttt{MiB}$|是|交互题（伪）|
|栈|stack|$1\texttt{s}/512\texttt{MiB}$|是|传统题|
|东方智慧|knowledge|$10\texttt{s}/1\texttt{GiB}$|否|传统题|

## 矩阵 matrix

### 题目描述

对于 $n$ 行 $m$ 列的矩阵 $\bold{A}$ 和 $m$ 行 $k$ 列的矩阵 $\bold{B}$ 定义矩阵乘法

$$(\bold{A}\times\bold{B})_{i,j}=\sum_{x=1}^k\bold{A}_{i,x}\bold{B}_{x,j}$$

，在此基础上定义方阵（行数与列数相等的矩阵）$\bold{M}$ 的幂

$$\begin{matrix}
&k\\\bold{M}^k=&\overbrace{\bold{M}\times\bold{M}\times\cdots\times\bold{M}}\end{matrix}$$

。给定一个有 $n$ 行 $n$ 列的非零 $01$ 矩阵 $\bold{M}$。保证有

$$\exist k\in[1,n]\quad s.t.\quad\bold{M}_{k,k}=1$$

，请你判定下列命题 $p$ 是否成立。

$$\exist k\in\mathbb{N_+}\quad s.t.\quad\forall i,j\in[1,n]\quad\bold{M}^k_{i,j}\geq 1$$

### 温馨提示

为减少选手负担，本题其余部分已经帮你写好，你只需要完成下面两个函数。

```cpp
bool solve1(const uint32_t& subId,const uint32_t& N,const vector<vector<bool>>& Matrix);
bool solve2(const uint32_t& subId,const uint32_t& N,const vector<pair<uint32_t,uint32_t>>& Matrix);
```

`solve1` 函数给定了三个参数 `subId`、`N`、`Matrix`，分别表示子任务编号、方阵的大小、给定的矩阵，你只需要返回命题 $p$ 是否成立（`true`/`false`）。

为了减少方阵的空间占用，`solve2` 函数给定了三个参数 `subId`、`N`、`Matrix`，分别表示子任务编号、方阵的大小、矩阵中的所有非零项坐标（从 $0$ 开始编号），你只需要返回命题 $p$ 是否成立（`true`/`false`）。

运行下发文件中的 `compile.sh` 即可编译进而测试程序是否通过样例，也可通过直接在赛时提交的方式测试给定样例。

### 数据范围与提示

对于 $100\%$ 的数据，保证 $\operatorname{solve1}:n^2\leq 2\times 10^6$，$\operatorname{solve2}:\operatorname{sizeof}\bold{M}\leq 2\times 10^6$。

|子任务编号|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$20$|$n\leq 100$|
|$2$|$40$|$n\leq 10^3$|
|$3$|$40$|$n\leq 10^6$|

## 栈 stack

### 题目描述

现在有一个长度为 $n$ 的由栈组成的序列，一开始所有栈都为空。你需要支持以下操作：

1. 向所有编号在 $[l,r]$ 内的栈压入 $x$ 元素；
2. 将所有编号在 $[l,r]$ 内的非空的栈的栈顶弹出；
3. 查询第 $s$ 个栈从栈顶开始往下的第 $k$ 个元素。

### 输入格式

第一行，两个正整数 $n,q$；

后 $q$ 行，每行第一个数为 $\texttt{op}_i$，表示这一次的操作种类。

如果 $\texttt{op}_i=1$，那么接下来输入三个数 $l_i,r_i,x_i$，分别对应操作 $1$ 中的 $l,r,x$。

如果 $\texttt{op}_i=2$，那么接下来输入两个数 $l_i,r_i$，对应操作 $2$ 中的 $l,r$。

如果 $\texttt{op}_i=3$，接下来会输入两个数 $s_i,k_i$，对应操作 $3$ 中的 $s,k$。

### 输出格式

对于每一次 $3$ 操作，若第 $k$ 个元素存在，则输出第 $k$ 个元素，否则输出 `Error`。

### 数据范围与提示

对于 $100\%$ 的数据，保证 $1\leq n,q\leq 2\times 10^5$，$x_i\leq 10^9$。

|子任务编号|分值|特殊性质|
|:-:|:-:|:-:|
|$1$|$20$|$1\leq n,q\leq 5\times 10^3$|
|$2$|$40$|$1\leq n,q\leq 5\times 10^4$|
|$3$|$40$|$1\leq n,q\leq 2\times 10^5$，$x_i\leq 10^9$|

## 东方智慧 knowledge

### 题目描述

> 这个问题在东亚国家人所共知，如果没人提出问题，其他国家怎么得知这样的问题呢？

给定一个长度为 $n$ 的非下降正整数序列 $a=(a_1,a_2,\cdots,a_n)$，对于每一个 $k\in[0,n]$，求解满足下列条件的非下降正整数序列 $x=(x_1,x_2,\cdots,x_n)$ 的个数，结果对 $998244353$ 取模。

- $\forall i\in[1,n],x_i\leq a_i$。
- 恰好有 $k$ 个下标 $i$ 满足 $x_i=a_i$。

### 输入格式

第一行，一个正整数 $n$，表示序列长度。

第二行，$n$ 个正整数 $a_i$，表示序列中的元素。

### 输出格式

输出当 $k=0,1,\cdots,n$ 时的答案，用空格隔开。

### 样例

#### 样例输入 1

```plain
3
1 2 3

```

#### 样例输出 1

```plain
5 5 3 1

```

#### 样例输入 2

```plain
4
3 3 3 3

```

#### 样例输出 2

```plain
15 10 6 3 1

```

### 数据范围与提示

对于 $30\%$ 的数据，保证 $1\leq n\leq 9$，$1\leq a_i\leq 9$。

对于 $60\%$ 的数据，保证 $1\leq n\leq 3\times 10^3$，$1\leq a_i\leq 3\times 10^3$。

对于 $100\%$ 的数据，保证 $1\leq n\leq 250000$，$1\leq a_i\leq 250000$。
