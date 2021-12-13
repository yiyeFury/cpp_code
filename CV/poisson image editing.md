[TOC]

# Poisson Image Editing[^Pérez, 2003]

## Poisson solution to guided interpolation


![](./figure1_Guided interpolation notations.jpg "Guided interpolation notations")
> Guided interpolation notations
> - **Unknown function** $f$ interpolates in domain $\Omega$ the **destination function** $f^*$, under **guidance of vector field** $\mathbf{v}$, which might be or not the gradient field of a **source function** $g$.

### Guided Interpolation
|符号|含义|
|:-|:-|
|$S$|image definition domain|
|$\Omega$| closed subset of $S$ with boundary $\partial\Omega$|
|$f^*$|known scalar function defined over $S$ minus the interior of $\Omega$|
|$f$|unknown scalar function defined over the interior of $\Omega$|
|$\mathbf{v}$|vector field defined over $\Omega$|

### Discrete Poisson solver
|符号|含义|
|:-|:-|
|$S$|include all the pixels of an image or only a subset of them|
|$N_p$|the set of ${p's}$ 4-connected neighbor which are in S, for each pixel $p$ in S|
|$\langle{p, q}\rangle$|pixel pair such that $q\in N_p$|
|$\partial\Omega$|the boundary of $\Omega$, $\partial\Omega=\{{p}\in{S}\backslash{\Omega}:{N_p}\cap{\Omega}\ne\empty\}$|
|$f_p$|the value of $f$ at $p$|
|$v_{pq}$|the projection of $\mathbf{v}(\frac{p+q}{2})$ on the oriented edge $[{p,q}]$, i.e., $v_{pq}=\mathbf{v}(\frac{p+q}{2})\cdot\vec{pq}$.|

**The task is to compute the set of intensities** ${f}|_{\Omega}=\{{f_p}, {p}\in{\Omega}\}$.  

- simultaneous linear equations:  
for all $p\in{\Omega}$,  
$$
|{N_p}|{f_p}
-
\sum\limits_{q\in{N_p}\cap{\Omega}}{f_q}
=
\sum\limits_{q\in{N_p}\cap{\partial\Omega}}{f^*_q}
+
\sum\limits_{q\in{N_p}}{v_{pq}}
\tag{7}\label{7}
$$

### Importing Gradients
> The basic choice for the guidance field v is a gradient field taken directly from a **source image**. Denoting by $g$ this source image.  

for all $\langle{p,q}\rangle$, 
$$
v_{pq}=g_p-g_q \tag{11}\label{11}
$$

### Mixing Gradients
> destination image $f^*$  

for all $\langle {p,q} \rangle$,
$$
v_{pq}=
\begin{cases}
f^*_p-f^*_q & \rm{if}\ |f^*_p - f^*_q|>|g_p - g_q| \\
g_p - g_q & \text{otherwise} \\
\end{cases}
\tag{13}\label{13}
$$


## References
[^Pérez, 2003]: Pérez P, Gangnet M, Blake A. Poisson image editing[M]//ACM SIGGRAPH 2003 Papers. 2003: 313-318.