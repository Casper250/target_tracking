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
    return 0; 
}