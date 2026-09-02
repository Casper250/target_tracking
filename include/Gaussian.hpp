#pragma once

#include <string>
#include <Eigen/Dense>

class Gaussian
{
public:
    Eigen::VectorXd mean; 
    Eigen::MatrixXd cov;
};
