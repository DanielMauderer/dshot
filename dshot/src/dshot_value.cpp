#include "dshot_value.h"
#include "dshot_exception.h"
#include <math.h>
#include <bitset>

// !!!add lock for bufferBuffer!!!
void dshot_value::updateValue(double throttle, bool telemetry){
    this->throttle = throttle;
    this->telemetry = telemetry;

    convertThrottle();
    addTelemetry();
    addCRC();
}

bool dshot_value::nextBit(){
    auto nBit = ((package >> (15 - poshorter)) & 0b1);
    poshorter++;
    if (poshorter == 16)
        reset();
    return nBit;
}

void dshot_value::reset(){
    poshorter = 0;
    package = bufferPackage;
}

unsigned short dshot_value::getPackage(){
    reset();
    return package;
}

double dshot_value::getThrottle(){
    return throttle;
}

void dshot_value::convertThrottle(){
    if(throttle > 1 | throttle < 0)
        throw dshot_throttle_exception(throttle);
    
    bufferPackage = round(throttle * 1999) + 48;
}

void dshot_value::addTelemetry(){
    bufferPackage = bufferPackage << 1;
    if (telemetry)
        bufferPackage |= 1; 
}

void dshot_value::addCRC(){
    unsigned short x1 = (bufferPackage >> 8) & 0b1111;
    unsigned short x2 = (bufferPackage >> 4) & 0b1111;
    unsigned short x3 = (bufferPackage) & 0b1111;
    unsigned short crc = x1 ^ x2 ^ x3; 

    bufferPackage = bufferPackage << 4;
    bufferPackage |= crc;
}