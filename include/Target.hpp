#pragma once

#include <functional>
#include <string>
#include <Eigen/Dense>
#include "DynMod.hpp"

enum class TargetType
{
    Function, 
    Samples, 
    DynamicModel
};

class Target
{
public: 

    using MotionFunction = std::function<Eigen::VectorXd(double t)>

    //One constructor for each case
    //Function : function position(t)
    Target(MotionFunction motionFunction, double deltaT, double t0 = 0.0);

    //Samples : takes in csv formatted file with x, y coordinates (currently only 2D)
    Target(const std::string& filename, double deltaT, double t0 = 0.0); 

    //Dynamic Model. Assumes the first half of the states are position
    Target(DynMod dynamicModel, double deltaT, double to = 0.0);


    //Advance position to next timestep
    void advancePosition(); //changes currentPosition

    Eigen::VectorXd getPosition() const; 

private: 
    TargetType targetType; 
    double timeStep; 
    double t; 
    Eigen::VectorXd currentState; 

    //Note these members are only "active" based on the targetType
    std::string filepath; 
    MotionFunction stateFunction;
    DynMod system; 

};