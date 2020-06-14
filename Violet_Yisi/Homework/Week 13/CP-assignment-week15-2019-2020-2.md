# Computational Physics

## Assignment Week 15

last update: 09-06-2020

### Group Assignments

1. Use the finite difference method to solve the given boundary problem using step sizes $h=0.1$ and $h=0.01.$ Plot your two approximate solutions and the actual solutions on the same coordinate system.
    (1) $x^{\prime\prime}=2x^{\prime}-x+t^{2}-1$ over $\left[  0,1\right]$ with $x\left(  0\right)  =5$ and $x\left(  1\right)  =10,$ $x\left(  t\right) =t^{2}+4t+5$.

    (2) $x^{\prime\prime}+\left(  1/t\right)  x^{\prime}+(1-1/\left(
       4t^{2}\right)  )x=0$ over $\left[  1,6\right]$ with $x\left(  1\right)  =1$ and $x\left(  6\right)  =0,$ $x\left(  t\right)  =\dfrac{0.2913843206\cos   \left(  t\right)  +1.01299385\sin\left(  t\right)  }{\sqrt{t}}$.

2. Solve the boundary value problem
    $$
    u_{xx} + 4u_x + e^xu = \sin(8x)
    $$
   numerically on $[-1, 1]$ with boundary conditions $u(\pm1) = 0$.

3. Apply the matrix representation method to solve Morse oscillator. The one-dimensional time-independent Schrödinger equation is given as: 
   $$
   -\frac{\hbar^2}{2m}\frac{d^2\psi(x)}{dx^2}+V(x)\psi(x)=E\psi(x)
   $$
   where Morse potential is defined as
   $$
   V(x)=D(1-e^{-\beta x})
   $$
   The analytical solutions are  determined as
   $$
   \begin{aligned}
   E_n & = \hbar\omega_0\left(n+\frac{1}{2}\right)-\frac{\hbar^2\omega_0^2}{4D}\left(n+\frac{1}{2}\right)^2,\quad n=0,1,\cdots\\
   \omega_0^2&=\frac{2D\beta^2}{m}
   \end{aligned}
   $$
   (1) Set $m=1$, $D=1$, $\beta=0.3$. Please write the script to calculate the five lowest energies numerically.  How do the results change with the increase of the size of the matrices? 
   (2) Please plot the corresponding wave functions of the five lowest-energy states.

   Hint: For simplicity, $\hbar=1$. 

4. Apply the shooting method or the matching method to calculate the first few energy levels and the associated wave functions for a potential of the form
    $$
    V = \frac{1}{2}k_1x^2+\frac{1}{2}k_2{x^4}
    $$
    For small $x$ the first $(k_1)$ term dominates, and the behavior is close to that found for the harmonic oscillator, while for large $x$ the second $(k_2)$ term dominates and the behavior is anharmonic. 
    You can set $k_1=1$, $k_2=0.1$. $\hbar=m=1$.
    

5. (Optional) Apply the matching method to obtain the energy eigenvalues and wave functions for the ground state and the first few excited states for the one-dimensional Lennard-Jones potential, which is given as
    $$
    V(x)=4\epsilon\left[\left(\frac{\sigma}{x}\right)^{12}-\left(\frac{\sigma}{x}\right)^{6}\right]
    $$
    with $\epsilon=10$ and $\sigma=1$. The integrations can be started at $x_L=0.5$ (on the left) and $x_R=5$ (on the right) with $\Delta x=0.01$. The matching point shall be chosen near the minimum of the potential because the absolute value of wave function approaches its maximum there.

6. (Optional) Many three-dimensional quantum mechanics problems can be reduced effectively to one- or two-dimensional problems. For example, the hydrogen atom is three dimensional, however, the spherical symmetry makes it possible to write the wave function in the form
   $$
   \psi(r,\theta,\varphi)=R(r)Y(\theta,\varphi)
   $$ 
   It is common practice to deal instead with the related function $U(r)$, 
   $$
   U(r) = rR(r)
   $$
   which satisfies the equation
   $$
   \frac{d^2 U(r)}{dr^2}=\left(2[V(r)-E]+\frac{l(l+1)}{r^2}\right)
   U(r) \quad\quad (1)
   $$
   where $V(r)=-1/r$ is the Coulomb potential and $l$ is an integer associated with the angular momentum of the electron, $l=0,1,\cdots$. Employ the shooting method to solve Eq.(1) for $U(r)$ starting the integration at $r=0$ with the initial value $U(r)=0$. Consider the cases $l=0$ and $l=1$ and compare your results with the analytic solutions for the hydrogen atom. 
   Hint: The energies of the bound states are given by $-1/2n^2$, where $n=1,2,\cdots$.

7. (Optional) Employ the central finite difference method to solve the BVP defined by
   $$
   -\nabla^2 u=20\cos(3\pi x)\sin(2\pi y)
   $$
   on a unit square with boundary conditions
   $$\begin{cases}
   u(0,y)=y^2\\
   u(1,y)=1\\
   u(x,0)=x^3\\
   u(x,1)=1
   \end{cases}
   $$

8. One way to calculate $\pi$ is by randomly throwing a dart into the unit square defined by $x \in [0, 1]$ and $y\in [0, 1]$ in the $xy$ plane. The chance of the dart landing inside the unit circle centered at the origin of the coordinates is $\pi/4$, from the comparison of the areas of one quarter of the circle and the unit square. Write a program to calculate $\pi$ in such a manner.