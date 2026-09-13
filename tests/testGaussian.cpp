#include "Gaussian.hpp"
#include <iostream>
#include <fstream>

void testMahalanobis()
{
    //test 1

    double tol = 1e-5;

    Eigen::VectorXd x1(2); 
    Eigen::VectorXd mean1(2);
    Eigen::MatrixXd cov1(2, 2);

    x1 << 3.0, 2.0;
    mean1 << 1.0, 2.0;
    cov1 << 1.0, 0.5,
             0.5, 1.0;

    double expectedMahalanobis1 = 5.333333;
    Gaussian gauss1(mean1, cov1);
    double computedMahalanobis1 = gauss1.mahalanobis(x1);

    if (std::abs(expectedMahalanobis1 - computedMahalanobis1) < tol)
    {
        std::cout << "Test 1 : Mahalanobis succeded :)" << std::endl; 
    } 
    else 
    {
        std::cout << "Test 1 : Mahalanobis failed :(" << std::endl; 
    }

}


void testLinearTransformation()
{

    // test 1
    
    double tol = 1e-5; 

    Eigen::VectorXd mean1(2);
    Eigen::MatrixXd cov1(2, 2);
    Eigen::MatrixXd transformationMatrix1(2, 2);
    Eigen::VectorXd expectedMean1(2);
    Eigen::MatrixXd expectedCov1(2, 2);

    mean1 << 1.0, 2.0;
    cov1 << 1.0, 0.5,
             0.5, 1.0;
    transformationMatrix1 << 1.0, 2.0,
                             3.0, 4.0;

    expectedMean1 << 5.0, 11.0;
    expectedCov1 << 7.0, 16.0,
                    16.0, 37.0;

    Gaussian gauss1(mean1, cov1);
    Gaussian transformedGauss1 = gauss1.linearTransformation(transformationMatrix1);
                
    double meanError = (expectedMean1 - transformedGauss1.mean).norm();
    double covError = (expectedCov1 - transformedGauss1.cov).norm();

    if (meanError < tol)
    {
        std::cout << "Test 1 : linear transformation mean succeded :)" << std::endl; 
    } 
    else
    {
        std::cout << "Test 1 : linear transformation mean failed :(" << std::endl; 
    }

    if (covError < tol)
    {
        std::cout << "Test 1 : linear transformation covariance succeded :)" << std::endl; 
    } 
    else
    {
        std::cout << "Test 1 : linear transformation covariance failed :(" << std::endl; 
    }

}

void testSample()
{
    // Samples a bunch of points to be plotted in Python. Does not validate the function here

    std::ofstream outFile; 
    outFile.open("data/results.csv");
    int nSamples = 100; 

    Eigen::VectorXd mean1(2);
    Eigen::MatrixXd cov1(2, 2);
    Eigen::VectorXd sample(2);
    mean1 << 1.0, 2.0;
    cov1 << 1.0, 0.5,
             0.5, 1.0;

    Gaussian gauss1(mean1, cov1);


    for (int i = 0; i < nSamples; ++i)
    {
        sample = gauss1.sample(); 
        outFile << sample[0] << ", " << sample[1] << ", \n";
    }

    outFile.close();
}
