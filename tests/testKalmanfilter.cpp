#include "Kalmanfilter.hpp"


void testCV2d()
{
    //create dynamical model: 
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
    double variance = 0.3; //sigma_a squared. 0 yields determenistic system

    Q << dt4 / 4.0, 0.0, dt3 / 2.0, 0.0,
        0.0, dt4 / 4.0, 0.0, dt3 / 2.0,
        dt3 / 2.0, 0.0, dt2, 0.0,
        0.0, dt3 / 2.0,  0.0, dt2;

    Q *= variance; 

    Eigen::VectorXd x0(4);

    x0 << 0, 0, 0.7, 0.9; 

    DynMod model(F, x0, Q);

    //Create sensor model
    double r = 0.2; //scalar for measurement noise 
    Eigen::MatrixXd R = Eigen::MatrixXd::Identity(2, 2);
    R *= r;
    Eigen::MatrixXd H(2, 4);

    H << 1, 0, 0, 0,
         0, 1, 0, 0; 
    
    
    SenMod sensor(H, R);


    //Create target
    Target::MotionFunction motion = [](double t)
    {
        Eigen::Vector4d state;  
        state << t, t, 1.0, 1.0; 
        return state;
    };

    Target target(motion, deltaT);

    //Set up kalman filter 
    int steps = 30; 
    std::string filepath = "../data/CVresults.csv";

    EKF_filtering(target, model, sensor, steps, filepath); 


}