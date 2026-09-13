#include "DynMod.hpp"
#include <iostream>

void testLinearSystem()
{
    Eigen::MatrixXd F(2, 2);
    Eigen::VectorXd x0(2);
    Eigen::MatrixXd Q(2, 2);

    F << 1, 1,
         1, 1; 
    
    x0 << 1, 1;

    Q << 1, 0,
         0, 1; 
    
    DynMod system(F, x0, Q);

    //Transition steps
    system.transitionStep();
    std::cout << "x1 : " << system.getState() << std::endl;
    system.transitionStep();
    std::cout << "x2 : " << system.getState() << std::endl;

    if (F == system.getTransitionMatrix())
    {
        std::cout << "Transition Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Transition Matrix returned : failure :(" << std::endl; 
    }
    
    if (Q == system.getNoiseCovariance())
    {
        std::cout << "Covariance Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Covariance Matrix returned : failure :(" << std::endl; 
    }

}


//f(xk)
Eigen::VectorXd f(const Eigen::VectorXd& xk)
{
    Eigen::VectorXd xnext(xk.size()); 
    xnext(0) = xk(0)*xk(0) + xk(1);
    xnext(1) = -xk(1);
    return xnext;
}

//F(xk)
Eigen::MatrixXd F(const Eigen::VectorXd& xk)
{
    Eigen::MatrixXd J(xk.size(), xk.size());
    J(0, 0) = 2*xk(0);
    J(0, 1) = 1; 
    J(1, 0) = 0;
    J(1, 1) = -1; 

    return J; 
}

void testNonLinearSystem()
{

    Eigen::VectorXd x0(2);
    Eigen::MatrixXd Q(2, 2);

    x0 << 1, 1;

    Q << 1, 0,
         0, 1; 


    DynMod system(f, F, x0, Q);

    //Transition steps
    system.transitionStep();
    std::cout << "x1 : " << system.getState() << std::endl;
    system.transitionStep();
    std::cout << "x2 : " << system.getState() << std::endl;

    Eigen::MatrixXd A(2, 2);
    A << 2, 1,
         0, -1; 


    if (A == system.getLinearizedF(x0))
    {
        std::cout << "Transition Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Transition Matrix returned : failure :(" << std::endl; 
    }
    
    if (Q == system.getNoiseCovariance())
    {
        std::cout << "Covariance Matrix returned : success :)" << std::endl; 
    }
    else
    {
        std::cout << "Covariance Matrix returned : failure :(" << std::endl; 
    }
}