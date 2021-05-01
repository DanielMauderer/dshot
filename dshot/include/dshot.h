//
// Created by Daniel on 30.11.2020.
//
#include "dshot_exception.h"
#include "dshot_rate.h"

#ifndef DSHOT_H
#define DSHOT_H

#define checkState(state) if(error_state != state){\
                       throw dshot_flow_exception(state);\
                   }

// motor_throtle_matrix (0 - 1) left to right top to bottom
//   m1     m2
//    \     /
//     \   /
//      |=|
//     /   \ 
//    /     \ 
//   m3     m4
struct motor_throtle_matrix
{
    double m1;
    double m2;
    double m3;
    double m4;
};


class dshot_client {
public:
    void initialize(dshot_rates rate);
    void start();
    void update(motor_throtle_matrix motor_matrix);
private:
    dshot_state error_state = UNINITIALIZED;
    dshot_rates dshot_rate;
    motor_throtle_matrix motor_matrix;
};

#endif //DSHOT_H
