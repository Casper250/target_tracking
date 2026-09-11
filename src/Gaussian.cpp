#include "Gaussian.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>


Gaussian::Gaussian(const Eigen::VectorXd& inp_mean, const Eigen::MatrixXd& inp_cov)
    : mean(inp_mean), cov(inp_cov)
{
}


double Gaussian::mahalanobis(const Eigen::VectorXd& x)
{
    //Return the mahalanobis distance squared
    return (x-mean).transpose()*cov.inverse()*(x -mean);
}


Gaussian Gaussian::linearTransformation(const Eigen::MatrixXd& L)
{
    Gaussian transformedGaussian(L * mean, L * cov * L.transpose());    
    return transformedGaussian;
}


Eigen::VectorXd Gaussian::sample()
{
    Eigen::LLT<Eigen::MatrixXd> llt(cov);
    if (llt.info() != Eigen::Success)
    {
        throw std::runtime_error("Cholesky factorization of Covariance matrix failed. Not positive definite.");
    }
    Eigen::MatrixXd L = llt.matrixL(); //This is the cholesky factor L such that cov = LL^T

    //We create the sample by transforming from a uniform sample. This is just for fun :)
    //Should perhaps take uniform distritbution as input later
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    const double PI = 3.14159265; //can later to move to its own constant file
    int n = mean.size();

    //Create an n-dimensional vector of independent standard normal distribution samples using Box-Muller.
    Eigen::VectorXd x(n);
    double U1, U2;
    double magnitude;

    for (int i = 0; i < n; i += 2)
    {
        do {
            U1 = distribution(generator);
        }
        while (U1 == 0);
        U2 = distribution(generator);

        magnitude = std::sqrt(-2.0 * std::log(U1));
        x(i) = magnitude * std::cos(2 * PI * U2);
        if (i + 1 < n)
        {
            x(i+1) = magnitude * std::sin(2 * PI * U2);
        }
    }

    return mean + L*x;
} 