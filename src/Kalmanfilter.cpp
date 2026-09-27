#include "Kalmanfilter.hpp"

//we have dynmod, sensmod and true target.

// EKF loop for testing CV and CT model.
void EKF_filtering (Target target, DynMod model, SenMod sensor, int steps, std::string filepath)
{

    //Open csv file
    std::ofstream outFile; 
    outFile.open(filepath);
    outFile << "x_hat_1,x_hat_2,x_hat_3,x_hat_4,"
        << "x_1,x_2,x_3,x_4\n";

    //Initialize matrices
    Eigen::MatrixXd I = Eigen::MatrixXd::Identity(4, 4);
    Eigen::MatrixXd P = I; 

    Eigen::VectorXd x_hat(4); 
    Eigen::VectorXd x(4); 
    x_hat = model.getState();

    Eigen::VectorXd z(2); //The measurement
    Eigen::VectorXd z_hat(2); //The predicted measurement

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
        W = P*H.transpose()*S.inverse();
        x_hat = x_hat + W*nu; 
        P = (I - W*H)*P*(I-W*H).transpose() + W*R*W.transpose(); 

        //Write results to CSV file; 
        
        for (int i = 0; i < 4; ++i)
        {
            outFile << x_hat(i) << ","; 
        }

        x = target.getState();
        for (int i = 0; i < 3; ++i)
        {
            outFile << x(i) << ","; 
        }
        outFile << x(3) <<"\n";
        
        step ++; 
    }

    outFile.close(); 


}

