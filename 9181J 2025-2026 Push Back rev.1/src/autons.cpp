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
  pros::adi::DigitalOut littleSirWilliam('F', false);
  pros::adi::DigitalOut descore_mech('G');
  descore_mech.set_value(true);
  intakeFirst.move_velocity(20000);
  chassis.pid_drive_set(40_in, 50, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-13_in, 80, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-70_deg, 70); 
  chassis.pid_wait();
  intakeFirst.move_velocity(0);
  chassis.pid_drive_set(13.8_in, 70, true); 
  chassis.pid_wait();
  intake_group.move_velocity(800);
  pros::delay(100);
  intake_group.move_velocity(-80000);
  pros::delay(1200);
  intake_group.move_velocity(800);
  pros::delay(200);
  intake_group.move_velocity(0);
  chassis.pid_drive_set(-44.5_in, 90, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(158_deg, 50); 
  chassis.pid_wait();
  intake_group.move_velocity(20000); 
  chassis.pid_drive_set(34_in, 60, true); 
  chassis.pid_wait(); 
  pros::delay(200);
  chassis.pid_drive_set(-21_in, 60, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(163_deg, 50); 
  chassis.pid_wait();
  descore_mech.set_value(false);
  intake_group.move_velocity(0); 
  chassis.pid_drive_set(-13_in, 100, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(-5000);
  pros::delay(200);
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(-1000); // score on long goal
  pros::delay(900);
  chassis.pid_drive_set(10_in, 100, true); 
  chassis.pid_drive_set(-10_in, 100, true); 
  // teamcolor = "Blue";
}

void red_autonomous_right() {
  pros::adi::DigitalOut littleSirWilliam('F', false);
  pros::adi::DigitalOut descore_mech('G');
  descore_mech.set_value(true);
  intakeFirst.move_velocity(20000);
  chassis.pid_drive_set(40_in, 50, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-13_in, 80, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-70_deg, 70); 
  chassis.pid_wait();
  intakeFirst.move_velocity(0);
  chassis.pid_drive_set(13.8_in, 70, true); 
  chassis.pid_wait();
  intake_group.move_velocity(800);
  pros::delay(100);
  intake_group.move_velocity(-80000);
  pros::delay(1200);
  intake_group.move_velocity(800);
  pros::delay(200);
  intake_group.move_velocity(0);
  chassis.pid_drive_set(-44.5_in, 90, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(158_deg, 50); 
  chassis.pid_wait();
  intake_group.move_velocity(20000); 
  chassis.pid_drive_set(34_in, 60, true); 
  chassis.pid_wait(); 
  pros::delay(200);
  chassis.pid_drive_set(-21_in, 60, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(163_deg, 50); 
  chassis.pid_wait();
  descore_mech.set_value(false);
  intake_group.move_velocity(0); 
  chassis.pid_drive_set(-13_in, 100, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(-5000);
  pros::delay(200);
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(-1000); // score on long goal
  pros::delay(900);
  chassis.pid_drive_set(10_in, 100, true); 
  chassis.pid_drive_set(-10_in, 100, true); 
  // teamcolor = "Red";
}

void red_autonomous_left() {
  // teamcolor = "Red";
  // skills code
  pros::adi::DigitalOut littleSirWilliam('F', false);
  pros::adi::DigitalOut descore_mech('G');
  littleSirWilliam.set_value(false);
  descore_mech.set_value(true);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  intakeFirst.move_velocity(20000);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  pros::delay(200);
  intake_group.move_velocity(-2000);
  pros::delay(300);
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(1500);
  pros::delay(1500);
  intakeFourth.move_velocity(0);
  chassis.pid_drive_set(45_in, 120, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intake_group.move_velocity(20000);
  chassis.pid_drive_set(32_in, 50, true); 
  chassis.pid_wait(); 
  pros::delay(600);
  chassis.pid_drive_set(-20_in, 60, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-153_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 60, true); 
  chassis.pid_wait(); 
  descore_mech.set_value(false);
  intake_group.move_velocity(-2000);
  pros::delay(200);
  intake_group.move_velocity(2000);
  intakeFourth.move_velocity(-1000);
  pros::delay(1400);
  intakeFourth.move_velocity(0);
  intake_group.move_velocity(0);
}

void blue_autonomous_left() {
  pros::adi::DigitalOut littleSirWilliam('F', false);
  pros::adi::DigitalOut descore_mech('G');
  littleSirWilliam.set_value(false);
  descore_mech.set_value(true);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  intakeFirst.move_velocity(20000);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  pros::delay(200);
  intake_group.move_velocity(-2000);
  pros::delay(300);
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(-1500);
  pros::delay(1500);
  intakeFourth.move_velocity(0);
  chassis.pid_drive_set(45_in, 120, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intake_group.move_velocity(20000);
  chassis.pid_drive_set(32_in, 50, true); 
  chassis.pid_wait(); 
  pros::delay(600);
  chassis.pid_drive_set(-20_in, 60, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-153_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 60, true); 
  chassis.pid_wait(); 
  descore_mech.set_value(false);
  intake_group.move_velocity(-2000);
  pros::delay(200);
  intake_group.move_velocity(2000);
  intakeFourth.move_velocity(-1000);
  pros::delay(1400);
  intakeFourth.move_velocity(0);
  intake_group.move_velocity(0);
}

void skills() {
  // skills code
  pros::adi::DigitalOut littleSirWilliam('F', false);
  littleSirWilliam.set_value(false);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  intakeFirst.move_velocity(20000);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(20000);
  pros::delay(500);
  intake_group.move_velocity(0);
  pros::delay(500);
  intake_group.move_velocity(-2000);
  pros::delay(200);
  intake_group.move_velocity(20000);
  intakeFourth.move_velocity(2000);
  pros::delay(2000);
  intakeFourth.move_velocity(0);
  chassis.pid_drive_set(45.5_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(34_in, 43, true); 
  chassis.pid_wait(); 
  pros::delay(2400);
  chassis.pid_drive_set(-32_in, 60, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(-2000);
  pros::delay(400);
  intake_group.move_velocity(2000);
  intakeFourth.move_velocity(-1000);
  pros::delay(1900);
  intakeFourth.move_velocity(0);
  intake_group.move_velocity(0);
  chassis.pid_drive_set(7_in, 40, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  chassis.pid_turn_set(-239_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(88_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-14_deg, TURN_SPEED); 
  chassis.pid_wait();
  intakeFirst.move_velocity(2000);
  chassis.pid_drive_set(36_in, 55, true); 
  chassis.pid_wait(); 
  pros::delay(700);
  intakeFirst.move_velocity(0);
  intake_group.move_velocity(-10000);
  pros::delay(2000);
  intake_group.move_velocity(2000);
  chassis.pid_drive_set(-46_in, 55, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-147_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(32_in, 40, true); 
  chassis.pid_wait(); 
  pros::delay(2400);
  littleSirWilliam.set_value(false);
  chassis.pid_drive_set(-20_in, 60, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-142_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-8_in, 60, true); 
  chassis.pid_wait(); 
  intake_group.move_velocity(-2000);
  pros::delay(200);
  intake_group.move_velocity(2000);
  intakeFourth.move_velocity(-1000);
  pros::delay(1500);
  intakeFourth.move_velocity(0);
  intake_group.move_velocity(0);
  chassis.pid_drive_set(2_in, 70, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-106_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(42_in, 70, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-61_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 70, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(37_in, 2000, true); 
  chassis.pid_wait(); 
}

void move_forward(){
  chassis.pid_drive_set(2_in, 70, true); 
  chassis.pid_wait(); 
}