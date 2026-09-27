#include "DynMod.hpp"
#include <iostream>


//Constructor general nonlinear case
DynMod::DynMod(
    Transition function, 
    JacobianTransition jacobianFunction, 
    const Eigen::VectorXd& initialState, 
    const Eigen::MatrixXd& processCovariance
)
    : f(function), 
      F(jacobianFunction),
      x(initialState), 
      Q(processCovariance),
      noiseGaussian(Eigen::VectorXd::Zero(initialState.size()), processCovariance)
{
}

//Constructor linear case
DynMod::DynMod(
    const Eigen::MatrixXd& transitionMatrix,
    const Eigen::VectorXd& initialState,
    const Eigen::MatrixXd& processCovariance)
    :  x(initialState), 
       Q(processCovariance), 
       noiseGaussian(Eigen::VectorXd::Zero(initialState.size()), processCovariance)
{

    Transition function = 
        [transitionMatrix](const Eigen::VectorXd& xk)
        {
            return transitionMatrix*xk;
        };
    
    JacobianTransition jacobianFunction = 
        [transitionMatrix](const Eigen::VectorXd& xk)
        {
            return transitionMatrix; 
        };

    f = function;
    F = jacobianFunction;
}

//Transition step x_k -> x_k+1
void DynMod::transitionStep()
{   
    x = f(x) + noiseGaussian.sample(); //xk+1 = f(xk) + wk
}


//Getter functions
Eigen::MatrixXd DynMod::getNoiseCovariance() const
{
    return Q; 
}

Eigen::MatrixXd DynMod::getLinearizedF(const Eigen::VectorXd& xe) const
{
    return F(xe); 
}

//Should only be used in linear case
Eigen::MatrixXd DynMod::getTransitionMatrix() const
{
    //Chooses correct dimension on input only as to not crash in nonlinear case.
    return F(Eigen::VectorXd::Zero(x.size()));
}

Eigen::VectorXd DynMod::transitionFunction(const Eigen::VectorXd& x) const
{
    return f(x); 
}



Eigen::VectorXd DynMod::getState() const
{
    return x;
}

void DynMod::setState(const Eigen::VectorXd& state)
{
    x = state; 
}


