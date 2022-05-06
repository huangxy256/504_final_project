#ifndef LORENZ_H
#define LORENZ_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>

#include "parameter.H"

using namespace std;

// This class of OrbitState is used to describe the set of coordinates (t, x, y, z) in the Lorenz problem

class OrbitState {

    private: 

    // Member data

    double t{};
    double x{};
    double y{};
    double z{};

    public: 

    // Constructor

    OrbitState()
    : t{0.0}, x{0.0}, y{0.0}, z{0.0}
    {}

    // Another constructor

    OrbitState(double _t, double _x, double _y, double _z)
    : t{_t}, x{_x}, y{_y}, z{_z}
    {}

    // Setter

    inline void set_t(double _t) {t = _t;}
    inline void set_x(double _x) {x = _x;}
    inline void set_y(double _y) {y = _y;}
    inline void set_z(double _z) {z = _z;}

    // Operators

    // Assignment operator

    OrbitState& operator=(const OrbitState& state){

        t = state.t;
        x = state.x; 
        y = state.y;
        z = state.z;

        return *this;
    }

    // Addition operator

    OrbitState operator+(const OrbitState& state){

        OrbitState state_out;

        state_out.t = state.t + t;
        state_out.x = state.x + x;
        state_out.y = state.y + y;
        state_out.z = state.z + z;

        return state_out;
    }

    // Subtraction operator

    OrbitState operator-(const OrbitState& state){

        OrbitState state_out;

        state_out.t = state.t - t;
        state_out.x = state.x - x;
        state_out.y = state.y - y;
        state_out.z = state.z - z;

        return state_out;
    }

    // Multiplication operators

    OrbitState operator*(double a){

        OrbitState state_out;

        state_out.t = a * t;
        state_out.x = a * x;
        state_out.y = a * y;
        state_out.z = a * z;

        return state_out;

    }

    friend OrbitState operator*(double a, const OrbitState& state){

        OrbitState state_out;

        state_out.t = a * state.t;
        state_out.x = a * state.x;
        state_out.y = a * state.y;
        state_out.z = a * state.z;

        return state_out;
    }

    // >> used in output

    friend ostream& operator<< (ostream& os, const OrbitState& state);


    // Functions

    OrbitState lorenz_rhs(double t){

        OrbitState dodt;

        // Get the derivatives of x, y and z

        dodt.t = t;  // since the rhs of these equations are time-independent, this time derivative is randomly refined
        dodt.x = sigma * (y - x);
        dodt.y = x * (rho - z) - y;
        dodt.z = x * y - beta * z;

        return dodt;

    }

    // A set of GET functions to access private components 

    double get_t(){

        return t;
    }

    double get_x(){

        return x;
    }

    double get_y(){

        return y;
    }

    double get_z(){

        return z;
    }


};

ostream& operator<< (ostream& os, const OrbitState& state){

    os << setw(14) << state.t << setw(14) << state.x << setw(14) << state.y << setw(14) << state.z << endl;

    return os;
}

// *******************************************************************************************************

// Function part

//  Used two functions for this project: write_history to record data and RK4Integrate for integration


void write_history(const vector<OrbitState>& history);

vector<OrbitState> RK4Integrate(OrbitState& state0, double dt, double tmax);



// This is the integration function using RK4 method minited to the 3 dimentional use of this problem

// This RK4 Integrater solves the first order ODE with the form:

// dy/dt = f (t, y);
// y(t0) = y0;

// Solution to this ODE is:

// y_n+1 = y_n + 1/6 * dt * (k1 + 2 * k2 + 2 * k3 + k4);
// t_n+1 = t_n + dt;

// where 

// k1 = f (t_n, y_n);
// k2 = f (t_n + dt / 2, y_n + 1 / 2 * dt * k1)
// k3 = f (t_n + dt / 2, y_n + 1 / 2 * dt * k2)
// k4 = f (t_n = dt, y_n + dt * k3)

// Input: 

// OrbitState state0, initial conditions
// dt, time step
// tmax, end time of integration

// Output: 

// vector<OrbitState> as the trajectory

vector<OrbitState> RK4Integrate(OrbitState& state0, double dt, double tmax){

    // Store data in a vector called history

    vector<OrbitState> history{};

    // Check for positive integration time

    // if(tmax < state0.get_t()){

    //     return -1;
    // }

    OrbitState state;

    state = state0;

    history.push_back(state);

    // Integration loop

    while(state.get_t() < tmax){

        double t0 = state.get_t();

        OrbitState k1 = state.lorenz_rhs(state.get_t());

        OrbitState state1;

        state1 = state + 1.0 / 2.0 * dt * k1;

        double tmid = state.get_t() + dt / 2.0;

        state1.set_t(tmid);

        OrbitState k2 = state1.lorenz_rhs(state1.get_t());

        OrbitState state2;

        state2 = state + 1.0 / 2.0 * dt * k2;

        state2.set_t(tmid);

        OrbitState k3 = state2.lorenz_rhs(state2.get_t());

        OrbitState state3;

        state3 = state + dt * k3;

        state3.set_t(state.get_t() + dt);

        OrbitState k4 = state3.lorenz_rhs(state3.get_t());

        state = state + 1.0 / 6.0 * dt * (k1 + 2 * k2 + 2 * k3 + k4);

        state.set_t(t0 + dt);

        history.push_back(state);

    }


    return history;
}








// This write_history function writes all the data into a file named "orbit_data.txt"

void write_history(const vector<OrbitState>& history){

    // for (auto e : history){

    //     cout << e << endl;
    // }

    ofstream of;

    of.open("orbit_data.txt");

    for (auto e : history){

        of << e << endl;
    }

    of.close();

    cout << "Created data file: " << "orbit_data.txt" << endl; 


}



#endif