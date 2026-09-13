#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
#include "../tests/testGaussian.cpp"
#include "../tests/testDynMod.cpp"
#include "../tests/testSenMod.cpp"

int main()
{    

     
     //testMahalanobis();
     //testLinearTransformation();
     //testSample();
     //testLinearSystem();
     //testNonLinearSystem();
     testLinearSensor();
     testNonLinearSensor();
     return 0;
} 