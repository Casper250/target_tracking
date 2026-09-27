#include "Target.hpp"
#include <iostream>

void testFunctionAdvanceMotion()
{
    //Define a motion target. 
    Target::MotionFunction motion = [](double t)
    {
        Eigen::Vector4d state;  
        state << t, t, 1.0, 1.0; 
        return state;
    };

    double deltaT = 0.1; 

    Target funcTarget(motion, deltaT);

    // Results

    Eigen::Vector4d step0; 
    Eigen::Vector4d step1; 
    Eigen::Vector4d step2; 

    step0 << 0.0, 0.0, 1.0, 1.0;
    step1 << 0.1, 0.1, 1.0, 1.0;
    step2 << 0.2, 0.2, 1.0, 1.0;

    // Compare
    if (funcTarget.getState() == step0)
    {   
        std::cout << "Step 0 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 0 failed" << std::endl; 
    }

    funcTarget.advanceState();

    if (funcTarget.getState() == step1)
    {   
        std::cout << "Step 1 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 1 failed" << std::endl; 
    }

    funcTarget.advanceState();

    if (funcTarget.getState() == step2)
    {   
        std::cout << "Step 2 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 2 failed" << std::endl; 
    }

}

void testDynModAdvanceMotion()
{
    const double deltaT = 0.1; 
    Eigen::MatrixXd F(4, 4); 
    
    F << 1, 0, deltaT, 0,
        0, 1, 0, deltaT,
        0, 0, 1, 0,
        0, 0, 0, 1; 

    Eigen::MatrixXd Q(4, 4);

    double dt2 = deltaT * deltaT;
    double dt3 = dt2 * deltaT;
    double dt4 = dt2 * dt2;
    double variance = 0; //sigma_a squared. 0 yields determenistic system

    Q << dt4 / 4.0, 0.0, dt3 / 2.0, 0.0,
        0.0, dt4 / 4.0, 0.0, dt3 / 2.0,
        dt3 / 2.0, 0.0, dt2, 0.0,
        0.0, dt3 / 2.0,  0.0, dt2;

    Q *= variance; 

    Eigen::VectorXd x0(4);

    x0 << 0, 0, 1, 1; 


    DynMod dynSys(F, x0, Q);
    Target dynModTarget(dynSys, deltaT);

    // Results
    Eigen::Vector4d step0; 
    Eigen::Vector4d step1; 
    Eigen::Vector4d step2; 

    step0 << 0.0, 0.0, 1.0, 1.0;
    step1 << 0.1, 0.1, 1.0, 1.0;
    step2 << 0.2, 0.2, 1.0, 1.0;




    // Compare
    if (dynModTarget.getState() == step0)
    {   
        std::cout << "Step 0 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 0 failed" << std::endl; 
    }

    dynModTarget.advanceState();

    if (dynModTarget.getState() == step1)
    {   
        std::cout << "Step 1 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 1 failed" << std::endl; 
    }

    dynModTarget.advanceState();

    if (dynModTarget.getState() == step2)
    {   
        std::cout << "Step 2 succeeded" << std::endl; 
    }
    else
    {
        std::cout << "Step 2 failed" << std::endl; 
    }
}