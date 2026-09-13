#pragma once

#include <string>
#include <Eigen/Dense>

class Gaussian
{
public:
    Eigen::VectorXd mean; 
    Eigen::MatrixXd cov;

    Gaussian(const Eigen::VectorXd& inp_mean, const Eigen::MatrixXd& inp_cov);

    double mahalanobis(const Eigen::VectorXd& x) const;
    Gaussian linearTransformation(const Eigen::MatrixXd& L) const;
    Eigen::VectorXd sample() const;

};
