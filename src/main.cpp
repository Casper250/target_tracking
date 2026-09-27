#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include "../tests/testGaussian.cpp"
#include "../tests/testDynMod.cpp"
#include "../tests/testSenMod.cpp"
#include "../tests/testTarget.cpp"

int main()
{    

     
     //testMahalanobis();
     //testLinearTransformation();
     //testSample();
     //testLinearSystem();
     //testNonLinearSystem();
     //testLinearSensor();
     //testNonLinearSensor();
     testFunctionAdvanceMotion();

     return 0;
} 