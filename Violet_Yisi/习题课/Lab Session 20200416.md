**Lab Session**

16-04-2020

1. Find the smallest positive zero of
   $$
   f (x) = x^4 − 6.4x^3 + 6.45x^2 + 20.538x − 31.752
   $$

2. Create the second difference matrix with size $N$, for example $N=5$:
   $$
    A = \begin{pmatrix}
    2 &-1  &  & &\\
     -1 & 2 &-1  & \\
     & -1 & 2 &-1  \\
     & & -1  &2 &-1 \\
     & & & -1 & 2
    \end{pmatrix}
    $$
    
3. $A$ is a square matrix? $A$ is a diagonal matrix? 
   
4. Use the results of LU decomposition
   $$
   A = LU =\begin{pmatrix}
   1& 0& 0\\
   3/2& 1& 0\\
   1/2 &11/13& 1\end{pmatrix}\begin{pmatrix}
   2& −3& −1\\
   0 &13/2& −7/2\\
   0 &0& 32/13\end{pmatrix}
   $$
   to solve $Ax = b$, where $b^T =(1 \;−1\; 2)$.

5. Read the scripyt `lab_20200416_jaan1.py`. What is the purpose of the function? Can you find the errors in the script and correct them?  

6. Solve the following $n$ simultaneous equations by the SOR method, $A$ is the second difference matrix,  
$$
\begin{aligned}
Ax=\begin{pmatrix}
    2 &-1  &  & &\\
     -1 & 2 &-1  & \\
     & -1 & 2 &-1  \\
     & & -1  &2 &-1 \\
     & & & -1 & 2
    \end{pmatrix}
    \begin{pmatrix}
    x_1\\x_2\\\vdots \\x_n\end{pmatrix}=\begin{pmatrix}
0 \\0\\\vdots\\
0\\1\end{pmatrix}
\end{aligned}
$$
In this case the iterative formulas are
$$
\begin{aligned}
x_1 &= \omega(x_2 − x_n)/2 + (1 − \omega)x_1\\
x_i& = \omega(x_{i−1} + x_{i+1})/2 + (1 − \omega)x_i , \; i = 2, 3, \cdots, n − 1\\
x_n &= \omega(1 − x_1 + x_{n−1})/2 + (1 − \omega)x_n
\end{aligned}
$$
(1) Read the script `gaussSeidel.py`. Can you find out the formula for the relaxation factor $\omega$?
(2) Can you code `iterEqs(x, omega)` and integrate it into the main program `lab_20200416_jaan2.py`?
(3) Run the program with $ n= 20$, $\epsilon=1e-9$.  What is the value of $\omega$? The exact solution can be shown to be $x_i = −n/4 +i/2$, $i = 1, 2,\cdots, n$. 
(4) Is the convergence slow or fast? Why?
(5) If we were to change each diagonal term of the coefficient from 2 to 4, how many iterations will be needed? 


