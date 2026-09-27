#pragma once

#include <Eigen/Dense>
#include "Gaussian.hpp"
#include <functional>

class SenMod
{
public:

    using MeasureMod = std::function<Eigen::VectorXd(const Eigen::VectorXd&)>;
    using JacobianMeasureMod = std::function<Eigen::MatrixXd(const Eigen::VectorXd&)>;


    Eigen::MatrixXd getMeasurementMatrix() const;  //For linear case
    Eigen::MatrixXd getLinearizedH(const Eigen::VectorXd& xe) const; 
    Eigen::MatrixXd getNoiseCovariance() const;
    
    Eigen::VectorXd takeMeasurement(const Eigen::VectorXd& xk) const;
    Eigen::VectorXd predictMeasurement(const Eigen::VectorXd& xk) const;

    SenMod(MeasureMod function, JacobianMeasureMod jacobianFunction, const Eigen::MatrixXd& noiseCovariance);
    SenMod(const Eigen::MatrixXd& modelMatrix, const Eigen::MatrixXd& noiseCovariance);
    

private:

    Eigen::MatrixXd R; 
    MeasureMod h; 
    JacobianMeasureMod H; 
    Gaussian noiseGaussian; 

};