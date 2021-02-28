//
// Created by Daniel on 30.11.2020.
//
#include "dshot.h"

void dshot_client::initialize(dshot_rates rate){
    checkState(UNINITIALIZED)
    dshot_rate = rate;
    error_state = INITIALIZED;
}

void dshot_client::start(){
    checkState(INITIALIZED)
    error_state = RUNNING;
}

void dshot_client::update(motor_throtle_matrix motor_matrix){
    checkState(RUNNING)

    this->motor_matrix = motor_matrix;
}