//
// Created by Daniel on 30.11.2020.
//
#include <exception>
#include <string>

#ifndef DSHOT_EXCEPTION_H
#define DSHOT_EXCEPTION_H

class dshot_exception : public std::exception
{
public:
    virtual std::string get_message() const = 0;
private:
};


enum dshot_state {
    RUNNING = 0,
    INITIALIZED = 1,
    UNINITIALIZED = 2
};

class dshot_flow_exception : public dshot_exception
{
public:
    dshot_flow_exception(dshot_state state);
    std::string get_message() const override ;
private:
    dshot_state state;
};

class dshot_throttle_exception : public dshot_exception
{
public:
    dshot_throttle_exception(double throttle);
    std::string get_message() const override ;
private:
    double throttle;
};

#endif //DSHOT_EXCEPTION_H
