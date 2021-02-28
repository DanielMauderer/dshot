
#ifndef DSHOT_VALUE_H
#define DSHOT_VALUE_H


class dshot_value
{
private:
    double telemetry;
    double throttle;
    unsigned short package;
    unsigned short bufferPackage;
    unsigned short poshorter;

    void convertThrottle();
    void addTelemetry();
    void addCRC();
    void reset();

public:
    dshot_value(double throttle, bool telemetry)
    {
        updateValue(throttle, telemetry);
        reset();
    }    
    
    ~dshot_value()
    {
    }

    void updateValue(double throttle, bool telemetry = false);
    bool nextBit();
    unsigned short getPackage();
    double getThrottle();
};

#endif
