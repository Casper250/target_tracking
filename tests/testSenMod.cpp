#include "SenMod.hpp"
#include <iostream>

void testLinearSensor()
{
    Eigen::MatrixXd R(2, 2);
    Eigen::MatrixXd H(2, 2);
    Eigen::VectorXd xk(2);

    H << 0, 1,
         1, 0; 
    
    xk << 1, 2;

    R << 1, 0,
         0, 1; 
    
    SenMod sensor(H, R);

    //Take measurement
    std::cout << "y1 : " << sensor.takeMeasurement(xk) << std::endl;


    if (H == sensor.getMeasurementMatrix())
    {
        std::cout << "Measurement Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Measurement Matrix returned : failure :(" << std::endl; 
    }
    
    if (R == sensor.getNoiseCovariance())
    {
        std::cout << "Covariance Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Covariance Matrix returned : failure :(" << std::endl; 
    }

}


//h(xk)
Eigen::VectorXd h(const Eigen::VectorXd& xk)
{
    Eigen::VectorXd xnext(xk.size()); 
    xnext(0) = xk(0)*xk(0) + xk(1);
    xnext(1) = -xk(1);
    return xnext;
}

//H(xk)
Eigen::MatrixXd H(const Eigen::VectorXd& xk)
{
    Eigen::MatrixXd J(xk.size(), xk.size());
    J(0, 0) = 2*xk(0);
    J(0, 1) = 1; 
    J(1, 0) = 0;
    J(1, 1) = -1; 

    return J; 
}

void testNonLinearSensor()
{

    Eigen::VectorXd xk(2);
    Eigen::MatrixXd R(2, 2);

    xk << 1, 1;

    R << 1, 0,
         0, 1; 


    SenMod sensor(h, H, R);

    //Take measurements
    std::cout << "y1 : " << sensor.takeMeasurement(xk) << std::endl;


    Eigen::MatrixXd A(2, 2);
    A << 2, 1,
         0, -1; 


    if (A == sensor.getLinearizedH(xk))
    {
        std::cout << "Measurement Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Measurement Matrix returned : failure :(" << std::endl; 
    }
    
    if (R == sensor.getNoiseCovariance())
    {
        std::cout << "Covariance Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Covariance Matrix returned : failure :(" << std::endl; 
    }
}