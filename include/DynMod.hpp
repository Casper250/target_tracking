#pragma once

#include <functional>
#include <string>
#include <Eigen/Dense>
#include "Gaussian.hpp"

class DynMod
{
public:

    using Transition = std::function<Eigen::VectorXd(const Eigen::VectorXd&)>; 
    using JacobianTransition = std::function<Eigen::MatrixXd(const Eigen::VectorXd&)>;
    
    Eigen::MatrixXd getNoiseCovariance() const;
    Eigen::MatrixXd getLinearizedF(const Eigen::VectorXd& xe) const; //Linearized matrix about xe
    Eigen::MatrixXd getTransitionMatrix() const; 
    Eigen::VectorXd getState() const; 

    void transitionStep(); //modifies the state x

    //Constructor for general nonlinear case
    DynMod(
        Transition function, 
        JacobianTransition jacobianFunction, 
        const Eigen::VectorXd& initialState, 
        const Eigen::MatrixXd& processCovariance
    );

    //Constructor for linear case
    DynMod(
        const Eigen::MatrixXd& transitionMatrix, 
        const Eigen::VectorXd& initialState,
        const Eigen::MatrixXd& processCovariance
    );

private: 

    Eigen::VectorXd x; 
    Eigen::MatrixXd Q; 
    Gaussian noiseGaussian; 
    Transition f;
    JacobianTransition F; 


};