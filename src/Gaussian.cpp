#include "Gaussian.hpp"
#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>


Gaussian::Gaussian(const Eigen::VectorXd& inp_mean, const Eigen::MatrixXd& inp_cov)
    : mean(inp_mean), cov(inp_cov)
{
}


double Gaussian::mahalanobis(const Eigen::VectorXd& x) const
{
    //Return the mahalanobis distance squared
    return (x-mean).transpose()*cov.inverse()*(x -mean);
}


Gaussian Gaussian::linearTransformation(const Eigen::MatrixXd& L) const
{
    Gaussian transformedGaussian(L * mean, L * cov * L.transpose());    
    return transformedGaussian;
}


Eigen::VectorXd Gaussian::sample() const
{
    if (cov.isZero(1e-9))
    {
        return mean; 
    }

    //Check if symmetric
    if (!cov.isApprox(cov.transpose(), 1e-9))
    {
        throw std::runtime_error(
            "Covariance matrix is not symmetric.");
    }

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(cov);

    //Check if diagonialization failed
    if (solver.info() != Eigen::Success)
    {
        throw std::runtime_error("Diagonalization of covariance matrix failed.");
    }


    const Eigen::VectorXd& eigenvalues = solver.eigenvalues();
    const Eigen::MatrixXd& eigenvectors = solver.eigenvectors();


    //Check for positive semidefiniteness

    for (int i = 0; i < eigenvalues.size(); ++i)
    {
        if (eigenvalues(i) < -1e-10)
        {
            throw std::runtime_error ("Covariance matrix not positive semidefinite.");
        }
    }


    //We create the sample by transforming from a uniform sample. This is just for fun :)
    //Should perhaps take uniform distritbution as input later
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    constexpr double PI = 3.14159265; 
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

    //Compute cov^(1/2) = V * sqrt(Lambda)
    Eigen::VectorXd sqrtEigenvalues = eigenvalues.cwiseMax(0.0).cwiseSqrt(); //Replace every eigenvalue smaller than zero with zero and take square root
    Eigen::MatrixXd L = eigenvectors * sqrtEigenvalues.asDiagonal(); 


    return mean + L*x;
} 