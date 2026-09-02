#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>

int main()
{
    std::ofstream file("data/results.csv");

    Eigen::Matrix2d A;
    Eigen::Matrix2d B;

    A << 1, 2,
         3, 4;

    B << 5, 6,
         7, 8;

    std::cout << "A =\n" << A << "\n\n";
    std::cout << "B =\n" << B << "\n\n";

    Eigen::Matrix2d C = A * B;

    std::cout << "A * B =\n" << C << "\n";


    return 0;
} 