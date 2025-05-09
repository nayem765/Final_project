# 2D Heat Equation Solver by Forward Euler Method, Non-MPI and MPI Parallelization.

##  Project Overview 
The heat equation is a parabolic partial differential equation, developed by Joseph Fourier in 1822, to show how heat diffuses through a given region. [Wikipedia: Heat equation](https://en.wikipedia.org/wiki/Heat_equation)
In this project, we solve the 2D heat equation using the Forward Euler method. Initially, the code has been set up as serial C++ code, and then the solution is extended to a parallel version using MPI. It shows the physical process that how it diffuses on a square plate, which is a non-MPI process. After that, we started the demonstration of the MPI version to parallelize using domain decomposition and ghost cell communication.


##  Physical and Mathematical Background

A square plate initially has a hot region at the center. The heat diffuses outward as time progresses.

$\frac{\partial u}{\partial t} = \alpha \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)$

Where:

* $u(x, y, t)$: temperature field
* $\alpha$: thermal diffusivity constant (material-dependent)
* $x, y$: spatial coordinates
* $t$: time

This equation is derived from **Fourier’s Law** of heat conduction:
$\vec{q} = -k \nabla u$
combined with the **conservation of energy**:
$\rho c \frac{\partial u}{\partial t} = -\nabla \cdot \vec{q} \Rightarrow \frac{\partial u}{\partial t} = \alpha \nabla^2 u$
where:

* $\vec{q}$ is the heat flux
* $k$ is thermal conductivity
* $\rho$ is density, $c$ is specific heat
* $\alpha = \frac{k}{\rho c}$ is the diffusivity

### Discretization

Initially, we started to solve this equation  numerically by discretizing the domain into an $N \times N$ grid with spatial steps $\Delta x = \Delta y = h$, and time step $\Delta t$. The temperature $u(i, j, n)$ is the value at grid point $(i, j)$ and time step $n$.

We use the **explicit Forward Euler method**:
$u_{i,j}^{n+1} = u_{i,j}^n + r \left(u_{i+1,j}^n + u_{i-1,j}^n + u_{i,j+1}^n + u_{i,j-1}^n - 4u_{i,j}^n\right)$
where:
$r = \frac{\alpha \Delta t}{h^2}$

This method is conditionally stable. For 2D:
$r < \frac{1}{4} \Rightarrow \Delta t < \frac{h^2}{4\alpha}$

### Initial and Boundary Conditions
- **Initial Condition**:
$$
\[
u(x, y, 0) =
\begin{cases}
100 & \text{if } |x - 0.5| < 0.1 \text{ and } |y - 0.5| < 0.1 \\
0 & \text{otherwise}
\end{cases}
\]
$$

- **Boundary condition**: Dirichlet (fixed temperature = 0 at edges)


###   Physical Interpretation of Results

We expect that when the simulation progresses, we will see the following heat diffusion behavior.

- **Initially**: The center of the domain contains a high-temperature square region (e.g., 100°C), while the rest of the plate or edge of the frame is at 0°C, showing a localized thermal disturbance.

- **As time goes by**, the heat spreads outwards from the center as thermal energy flows from hotter to cooler regions.

- **Eventually**: The heat continues diffusing toward the edges. Since the domain has fixed-temperature boundary conditions set to 0°C, the system will reach **thermal equilibrium**
 
This physically represents how **entropy increases** in irreversible thermodynamic processes in a closed system, and energy is distributed evenly, as expected from the second law of thermodynamics. 



