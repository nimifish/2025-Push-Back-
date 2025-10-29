#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

void blue_autonomous_right() {
  // teamcolor = "Blue";
}

void red_autonomous_right() {
  // teamcolor = "Red";
}

void red_autonomous_left() {
  // teamcolor = "Red";
  pros::adi::DigitalOut littleSirWilliam('H', false);
  pros::adi::DigitalOut descore_mech('G');
  descore_mech.set_value(true);
  intake_group.move_velocity(20000);
  chassis.pid_drive_set(40_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(1000);
  pros::delay(1000);
  intakeFourth.move_velocity(0);
  descore_mech.set_value(false);
  chassis.pid_drive_set(46_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intake_group.move_velocity(20000);
  littleSirWilliam.set_value(true);
  chassis.pid_drive_set(29_in, 30, true); 
  chassis.pid_wait(); 
  pros::delay(2000);
  chassis.pid_drive_set(-30_in, 60, true); 
  chassis.pid_wait(); 
  intakeFourth.move_velocity(-1000);
  pros::delay(4000);
}

void blue_autonomous_left() {
  // teamcolor = "Blue";
  pros::adi::DigitalOut littleSirWilliam('H', false);
  pros::adi::DigitalOut descore_mech('G');
  descore_mech.set_value(true);
  chassis.pid_drive_set(30_in, 55, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  chassis.pid_drive_set(10_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(700);
  pros::delay(1000);
  intakeFourth.move_velocity(0);
  descore_mech.set_value(false);
  chassis.pid_drive_set(46_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intake_group.move_velocity(20000);
  littleSirWilliam.set_value(true);
  chassis.pid_drive_set(29_in, 30, true); 
  chassis.pid_wait(); 
  pros::delay(2000);
  chassis.pid_drive_set(-30_in, 60, true); 
  chassis.pid_wait(); 
  intakeFourth.move_velocity(-1000);
  pros::delay(4000);
}

void skills() {
  // skills code
}
