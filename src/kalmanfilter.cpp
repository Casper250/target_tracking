#include "DynMod.hpp"
#include "SenMod.hpp"
#include "Target.hpp"

//we have dynmod, sensmod and true target.

// EKF loop for testing CV and CT model.
void EKF_filtering (Target target, DynMod model, SenMod sensor, int steps, std::string filepath)
{

    //Open csv file
    std::ofstream outFile; 
    outFile.open(filepath);

    //Initialize matrices
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(4, 4);
    Eigen::MatrixXd = I; 

    Eigen::VectorXd x(4); 
    x_hat << 0, 0, 0, 0; //initial state. Can also add start up scheme.

    Eigen::VectorXd z(2); //The measurement
    Eigen::VectorXd nu(2); //The innovation

    Eigen::MatrixXd F(4, 4); 

    Eigen::MatrixXd Q(4, 4);
    Q = model.getNoiseCovariance();

    Eigen::MatrixXd H(2, 2);
    Eigen::MatrixXd S(2, 2);
    Eigen::MatrixXd W(4, 2); //kalman gain

    Eigen::MatrixXd R(2, 2);
    R = sensor.getNoiseCovariance(); 


    int step = 0; 
    while (step < steps)
    {
        target.advanceState(); 

        //prior prediction
        x_hat = model.transitionFunction(x_hat);
        F = model.getLinearizedF(x_hat);
        P = F*P*F.transpose() + Q;
        
        //Measurement
        z = sensor.takeMeasurement(target.getState()); 
        z_hat = sensor.predictMeasurement(x_hat); 
        nu = z - z_hat; 
        
        H = sensor.getLinearizedH(x_hat);
        S = H*P*H.transpose() + R; 

        //posterior prediction
        W = P*H.transpose()*s.inverse();
        x = x + W*nu; 
        P = (I - W*H)*P*(I-W*H).transpose() + W*R*W.transpose(); 

        //Write results to CSV file; 
        
        outFile << x_hat.transpose() << ", " << target.getState().transpose() << ", \n";
        
        step ++; 
    }

    outfile.close(); 


}

