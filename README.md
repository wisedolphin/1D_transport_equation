# 1D_transport_equation
In progress...

This is one dimensional transport equation solver.

**Stack**

Boost property_tree


**Build**
- go to project dir
- mkdir build
- cd build
- cmake ..
- make

**Src map**

*Zone class*

Fluid domains are presented as Zone claas. Filed of Zone class are fluid field and flued fluxes.
If N - number of real cells, then fluid field has N+2 cells (N real and two fiction cells), fluid fluxes has N+1 cells - one cell for each face.
For MUSCL scheme we need additional fluid field for each cell face. 

*Config*

Class config. Parsing config.json class with boost/property_tree


**Mathematical model**
- Explicit unsteady solver
- Upwind scheme (CIR)
- MUSCL scheme

**To Do**

- python scripts to collect data and compare with exact solution
- unit tests
- lax-wendroff scheme
- openmp parallelism
