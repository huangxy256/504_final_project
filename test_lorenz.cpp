#include <iostream>

#include "lorenz.H"

using namespace std;

int main(){

    // One initial state, t = 0, x = 8, y = 1, z = 1

    OrbitState state(0,8.0,1.0,1.0);

    // RK4 Integration function takes "state" as initial condition, and integrate every dt to tmax

    double dt = 0.001;

    double tmax = 50.0;

    auto history = RK4Integrate(state, dt, tmax);

    write_history(history);

    // Change initial condition

    OrbitState state1(0, 8.0, 1.0, 1.01);

    auto history1 = RK4Integrate(state1, dt, tmax);

    // Compare at the end of integration

    auto last = history.back();
    auto last1 = history1.back();

    auto diff = last1 - last;

    cout << "Results for two initially close solutions: " << endl;

    cout << "First set of coordinates: " << endl;

    cout << last << endl;

    cout << "Second set of coordinates: " << endl;

    cout << last1 << endl;

    cout << "The difference is : " << endl;

    cout << diff << endl;


}