// An implementation of
// Fjellstad & Fossen 1994: Quaternion Feedback Regulation of Underwater Vehicles,
// a nonlinear PD position and orientation controller.
// All variables are named as they appear in the paper.

#ifndef VORTEX_CONTROLLER_QUATERNION_PD_CONTROLLER_H
#define VORTEX_CONTROLLER_QUATERNION_PD_CONTROLLER_H

#include <Eigen/Dense>
#include "vortex/eigen_typedefs.h"

class QuaternionPdController
{
public:
  QuaternionPdController(double a,
                         double b,
                         double c,
                         double W,
                         double B,
                         const Eigen::Vector3d &r_G,
                         const Eigen::Vector3d &r_B);
  void setGains(double a, double b, double c);
  Eigen::Vector6d compute(const Eigen::Vector3d    &x,
                          const Eigen::Quaterniond &q,
                          const Eigen::Vector6d    &nu,
                          const Eigen::Vector3d    &x_d,
                          const Eigen::Quaterniond &q_d);
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
private:
  Eigen::Matrix6d proportionalGainMatrix(const Eigen::Matrix3d &R);
  Eigen::Vector6d errorVector(const Eigen::Vector3d    &p,
                              const Eigen::Vector3d    &p_d,
                              const Eigen::Quaterniond &q,
                              const Eigen::Quaterniond &q_d);
  Eigen::Vector6d restoringForceVector(const Eigen::Matrix3d &R);
  int             sgn(double x);

  double c;             // Orientation gain
  Eigen::Matrix6d K_d;  // Derivative gain matrix
  Eigen::Matrix3d K_x;  // Position error gain matrix

  Eigen::Vector3d r_G;  // Center of gravity, expressed in body frame
  Eigen::Vector3d r_B;  // Center of buoyancy, expressed in body frame
  double W;             // [N] Weight of ROV
  double B;             // [N] Buoyancy of ROV
};

#endif  // VORTEX_CONTROLLER_QUATERNION_PD_CONTROLLER_H
