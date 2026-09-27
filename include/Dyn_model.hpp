#pragma once

#include <Eigen/dense>


class Dyn_model{

    int nStates;
    Eigen::Matrix4d F;
    Eigen::Matrix4d Q;


};