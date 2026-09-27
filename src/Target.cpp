#include "Target.hpp"


Target::Target(MotionFunction motionFunction, double deltaT, double t0)
: stateFunction(motionFunction), 
  timeStep(deltaT),
  t(t0), 
  targetType(TargetType::Function),
  currentState(motionFunction(t0))
{
}


//Samples : takes in csv formatted file with x, y, x', y' coordinates. Only 2D
Target::Target(const std::string& filename,  double deltaT, double t0)
: filepath(filename), 
  timeStep(deltaT),
  t(t0),
  targetType(TargetType::Samples)
{
    //std::ifstream = file; //We wait with this
    //std::string line; 
}

//Dynamic Model
Target::Target(DynMod dynamicModel, double deltaT, double t0)
: system(std::move(dynamicModel)),
  timeStep(deltaT),
  t(t0),
  targetType(TargetType::DynamicModel),
  currentState(dynamicModel.getState())
{   
}


//Advance state to next timestep
void Target::advanceState() //changes currentState
{
    switch(targetType)
    {
        case TargetType::Function:
            t += timeStep; 
            currentState = stateFunction(t);
            break; 

        case TargetType::Samples:
            //Todo
            break; 

        case TargetType::DynamicModel:
            system -> transitionStep();
            currentState = system -> getState();
            break; 
    }
}

Eigen::VectorXd Target::getState() const
{
    return currentState;
}