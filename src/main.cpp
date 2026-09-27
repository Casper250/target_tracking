#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include "../tests/testGaussian.cpp"
#include "../tests/testDynMod.cpp"
#include "../tests/testSenMod.cpp"
#include "../tests/testTarget.cpp"
#include "../tests/testKalmanfilter.cpp"

int main()
{    
     
     //testMahalanobis();
     //testLinearTransformation();
     //testSample();
     //testLinearSystem();
     //testNonLinearSystem();
     //testLinearSensor();
     //testNonLinearSensor();
     //testFunctionAdvanceMotion();
     //testDynModAdvanceMotion();
     testCV2d(); 

     

     return 0;
} 