# 504_final_project

This is the final project for PHY504

Author: 

Xiangyu Huang

This is a Lorenz attractor solver using the RK4 method.

The following files are contained in this project:

1. lorenz.H

    A header file that contains:
    
    data type "OrbitState" used to store t,x,y,z data in this problem;

    a 3-dimensional integrator using RK4 method for 1st order ODE's;

    a write-data-to-file function that generates a file named "orbit_data.txt".

2. parameter.H

    A header file that contains:

    initialization of the three parameters: beta, sigma and rho as in Lorenz problem.

    variation of these numbers are done with this file.

3. test_lorenz.cpp

    A test file that explore the output. 

4. orbit_data.txt

    A .txt file used for data storage: 

    data corresponding to one set of initial condition is stored here.

5. plot_command.txt

    Visualization of the results are done via gnuplot. 

    To generate the trajectory, type in terminal:

        $ gnuplot

        > load 'plot_command.txt'

        > q




