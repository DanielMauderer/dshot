#include "string"
#include "dshot_exception.h"
    
dshot_flow_exception::dshot_flow_exception(dshot_state state){
    this->state = state;
}

std::string dshot_flow_exception::get_message() const{
    switch (state)
    {
    case RUNNING:
        return "dhsot not started";
        break;
    case INITIALIZED:
        return "dhsot not initialized";
        break;    
    case UNINITIALIZED:
        return "dhsot already initialized";
        break;
    default:
        return "unknown dhsot state";
    }
}


dshot_throttle_exception::dshot_throttle_exception(double throttle){
    this->throttle = throttle;
}

std::string dshot_throttle_exception::get_message() const{
    return "wrong throttle value: " + std::to_string(this->throttle);
}