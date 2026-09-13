#include "SenMod.hpp"

SenMod::SenMod(
    MeasureMod function,
    JacobianMeasureMod jacobianFunction,
    const Eigen::MatrixXd& noiseCovariance
):
    h(function),
    H(jacobianFunction),
    R(noiseCovariance),
    noiseGaussian(Eigen::VectorXd::Zero(noiseCovariance.rows()), noiseCovariance)
{
}

SenMod::SenMod(
    const Eigen::MatrixXd& modelMatrix,
    const Eigen::MatrixXd& noiseCovariance
):
    R(noiseCovariance),
    noiseGaussian(Eigen::VectorXd::Zero(noiseCovariance.rows()), noiseCovariance)
{
    MeasureMod function = 
        [modelMatrix](const Eigen::VectorXd& xk)
        {
            return modelMatrix*xk; 
        };

    JacobianMeasureMod jacobianFunction = 
        [modelMatrix](const Eigen::VectorXd& xk)
        {
            return modelMatrix;
        };
    
    h = function;
    H = jacobianFunction;

}




Eigen::VectorXd SenMod::takeMeasurement(const Eigen::VectorXd& xk) const
{
    return h(xk) + noiseGaussian.sample();
}

//getter functions

Eigen::MatrixXd SenMod::getMeasurementMatrix() const
{
    return H(Eigen::VectorXd::Zero(R.rows()));
}

Eigen::MatrixXd SenMod::getLinearizedH(const Eigen::VectorXd& xe) const
{
    return H(xe);
} 

Eigen::MatrixXd SenMod::getNoiseCovariance() const
{
    return R; 
}

