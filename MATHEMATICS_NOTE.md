[TOC]  

# 统计值  

## 方差与标准差  
> 2.6 Introduction to the Basic Mathematical Tools Used in Digital Image Processing  
Estimating the Mean, Variance, and Higher-Order Moments from Sample Data[^DIP, 4th]  

- N observations  

**population variance**  
$$
{\sigma}^2=\frac{1}{N}\sum\limits_{i=1}^N\left(x_i - \bar{x}\right)^2
$$

**sample variance**  
$$
{\sigma}^2=\frac{1}{N-1}\sum\limits_{i=1}^N\left(x_i - \bar{x}\right)^2
$$

## 协方差与协方差矩阵  
> wikipedia: [Definition of sample covariance](https://en.wikipedia.org/wiki/Sample_mean_and_covariance)  

**Definition of sample covariance**  

- K variables  
- N observations  

The sample **covariance matrix** is a $K \mbox{-} by \mbox{-} K$ matrix $\mathbf{Q} =\left[q_{jk}\right]$   with entries
$$
q_{jk}=\frac{1}{N-1}\sum\limits_{i=1}^{N}\left(x_{ij}-\bar{x}_j\right)\left(x_{ik}-\bar{x}_k\right)
$$

where $q_{jk}$  is an estimate of the covariance between $j^{th}$ the variable and the $k^{th}$ variables.

## 相关系数 correlation  
> 3.1.5 相关系数(Corr)[^QX/T 127-2011]

## 均方根误差 root-mean-square-error  
> 3.1.4 均方根误差(RMSE)[^QX/T 127-2011]

# 导数 Derivative  
> 2.1 导数概念[^高等数学, 第6版]  
> 3.6 Sharpening (Highpass) Spatial Filters[^DIP, 4th]  


## 差分  
> [wikipedia: Finite difference](https://en.wikipedia.org/wiki/Finite_difference)  

> 10.2 Point, Line, and Edge Detection[^DIP, 4th]  

## 差商  
> [wikipedia: Difference quotient](https://en.wikipedia.org/wiki/Difference_quotient)  

## Gradient 梯度  
> [Wikipedia: Gradient](https://en.wikipedia.org/wiki/Gradient)  
> 3.6 Sharpening (Highpass) Spatial Filters[^DIP, 4th]  
> 9.7 方向导数与梯度[^高等数学, 第6版]  

### Gradient descent  
> [Wikipedia: Gradient descent](https://en.wikipedia.org/wiki/Gradient_descent)  


# Taylor Formula  
> 3.3 泰勒公式[^高等数学, 第6版]  

# Vector 向量  
> 8.1 向量及其线性运算[^高等数学, 第6版]  

## 范数  
> 5.1 向量的内积、长度及正交性[^线性代数, 第5版]  
> [Wikipedia: Norm (mathematics)](https://en.wikipedia.org/wiki/Norm_(mathematics))  

## dot product or inner product  
> 5.1 向量的内积、长度及正交性[^线性代数, 第5版]  

> [Wikipedia: Dot product](https://en.wikipedia.org/wiki/Dot_product)  

In mathematics, the **dot product** or **scalar product** is an algebraic operation that takes two equal-length sequences of numbers (usually **coordinate vectors**), and **returns a single number**.  

In Euclidean geometry, the dot product of the Cartesian coordinates of two vectors is widely used. It is often called "the" **inner product** (or rarely **projection product**) of Euclidean space, even though it is not the only inner product that can be defined on Euclidean space (see Inner product space for more).  

**Algebraic definition**  
The dot product of two vectors $a=[a_1, a_2, \dots, a_n]$ and $b=[b_1, b_2, \dots, b_n]$ is defined as
$$
a\cdot{b}=\sum\limits_{i=1}^n{a_i}{b_i} = a_1b_1 + a_2b_2 + \cdots + a_nb_n
$$


## 数量积  
> 8.2 数量积 向量积 混合积[^高等数学, 第6版]  

向量$\mathbf{a}$与$\mathbf{b}$的数量积，记作，即
$$
\mathbf{a}\cdot\mathbf{b}=\lVert{a}\rVert\lVert{b}\rVert\cos{\theta}
$$
$θ$为向量$a$与$b$的夹角。

> 5.1 向量的内积、长度及正交性[^线性代数, 第5版]  

## 向量积  
> 8.2 数量积 向量积 混合积[^高等数学, 第6版]  

> [Wikipedia: Cross product](https://en.wikipedia.org/wiki/Cross_product)  

In mathematics, the **cross product** or **vector product** (occasionally directed area product, to emphasize its geometric significance) is a binary operation on two vectors in three-dimensional space $\mathbb{R}^3$, and is denoted by the symbol $\times$. Given two linearly independent vectors a and b, the cross product, $a\times{b}$ (read "a cross b"), is a **vector** that is perpendicular to both a and b, and thus normal to the plane containing them.  

**Definition**  
The cross product of two vectors a and b is defined only in three-dimensional space and is denoted by $a\times{b}$.    

The cross product $a\times{b}$ is defined as a vector $**c**$ that is perpendicular (orthogonal) to both a and b, with a direction given by the **right-hand rule** and a magnitude equal to the area of the parallelogram that the vectors span.  

The cross product is defined by the formula  
$$
\mathbf{a}\times\mathbf{b}=\lVert{a}\rVert\lVert{b}\rVert\sin\theta\ \mathbf{n}
$$
where:  

- $\theta$ is the angle between $\mathbf{a}$ and $\mathbf{b}$ in the plane containing them (hence, it is between $0\degree$ and $180\degree$)   
- $\Vert\mathbf{a}\Vert$ and $\Vert\mathbf{b}\Vert$ are the magnitudes of vectors $\mathbf{a}$ and $\mathbf{b}$  
- and $\mathbf{n}$ is a **unit vector** perpendicular to the plane containing $\mathbf{a}$ and $\mathbf{b}$, in the direction given by the **right-hand rule**  

If the vectors $\mathbf{a}$ and $\mathbf{b}$ are parallel (that is, the angle $\theta$ between them is either $0\degree$ or $180\degree$), by the above formula, the cross product of a and b is the zero vector $\mathbf{0}$.

**Matrix notation**  
The cross product can also be expressed as the formal determinant:
$$
\mathbf{a}\times\mathbf{b}=
\begin{vmatrix}
\mathbf{i} & \mathbf{j} & \mathbf{k} \\
a_1 & a_2 & a_3 \\
b_1 & b_2 & b_3 
\end{vmatrix}
$$

## Outer product  
> [wikipedia: outer product](https://en.wikipedia.org/wiki/Outer_product)  

In linear algebra, the outer product of two coordinate vectors is a matrix.  

Given two vectors of size $m\times1$ and $n\times1$ respectively  
$$
u=\begin{bmatrix}u_1 \\ u_2 \\ \vdots \\ u_m \end{bmatrix}, v=\begin{bmatrix}v_1 \\ v_2 \\ \vdots \\ v_n \end{bmatrix}
$$

**outer product**, denoted $u\times{v}$, is defined as the $m\times{n}$ matrix  
$$
u\otimes{v}=\begin{bmatrix}
u_1v_1 & u_1v_2 & \dots & u_1v_n \\ 
u_2v_1 & u_2v_2 & \dots & u_2v_n \\
\vdots & \vdots & \ddots & \vdots \\
u_mv_1 & u_mv_2 & \dots & u_mv_n
\end{bmatrix}
$$

The **outer product** $u\otimes{v}$ is equivalent to a matrix multiplication ${uv}^T$.  

## 混合积  
> 8.2 数量积 向量积 混合积[^高等数学, 第6版]  

# References  

[^DIP, 4th]: Rafael C Gonzalez,Richard E Woods.Digital Image Processing:4th ed[M].New York:Pearson,2018.  

[^高等数学, 第6版]: 同济大学数学系.高等数学:第6版[M].北京:高等教育出版社,2007.  

[^线性代数, 第5版]: 同济大学数学系.工程数学·线性代数:第5版[M].北京:高等教育出版社,2007.  

[^QX/T 127-2011]: 气象卫星定量产品质量评价指标和评估报告要求:QX/T 127-2011[S].北京:气象出版社,2011.
