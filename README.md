# C++ / Python Numerical Project

Numerical calculations are implemented in C++ and results are
visualized and analyzed using Python.


# TODO
1. Make a target class. Options for movement representation: parametric function, trajectories, DynModel
Should hold state, time and function for evolving to next time step, give time step if needed (parametric case)

2. Make EKF class
Should hold prior and posterior predictions, innovation, innovation matrix, prior and posterior covariance matrix.
Startup routine for CV perhaps (can wait with this) and just use guess
prior prediction step
posterior prediction step


2-5. Functionality for computing NIS and NEES
Where should this be? 

3. Main loop
Initialize target object. 
Initalize for example CV model.
Initialize sensor model.
Initialize 



## Build

```bash
cmake -S . -B build
cmake --build build