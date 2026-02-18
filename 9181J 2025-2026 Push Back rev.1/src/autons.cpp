#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 80;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(17, 0.0, 82.0);         // Fwd/rev constants, used for odom and non odom motions
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

void skills() {
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  descore_mech.set_value(false);
  // Goes to the MIDDLE first
  intakeHoard();
  chassis.pid_drive_set(22_in, 40, true);
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_drive_set(8_in, 70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-135_deg, 70);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intakeLowerGoal();
  pros::delay(800); // score middle goal
  // go to left loader
  chassis.pid_drive_set(51_in, 70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-180_deg, 90);
  chassis.pid_wait();
  // Activates little will and moves to matchloader
  littleSirWilliam.set_value(true);
  intakeHoard();
  chassis.pid_drive_set(14.3_in, 60, true);
  chassis.pid_wait();
  pros::delay(1200); // wait enough to Matchload ALL Blocks
  // Moves backwards and moves across the field
  chassis.pid_drive_set(-14.2_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  chassis.pid_turn_set(-45_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(18_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(0.3_deg, 50); 
  chassis.pid_wait();
  descore_mech.set_value(true);
  chassis.pid_drive_set(86_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  descore_mech.set_value(false);
  chassis.pid_turn_set(-45_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  // Turn and then score on long goal
  chassis.pid_turn_set(0_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intakeDebug();
  intakeUpperGoal();
  littleSirWilliam.set_value(true);
  pros::delay(2000); // wait enough to score ALL Blocks
  intakeHoard();
  chassis.pid_turn_set(0.5_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(38_in, 60, true);
  chassis.pid_wait();
  pros::delay(1700); // wait enough to matchload ALL Blocks
  chassis.pid_drive_set(-32_in, 70, true);
  chassis.pid_wait();
  intakeDebug();
  intakeUpperGoal();
  pros::delay(1800); // wait enough to score ALL Blocks
  chassis.pid_drive_set(14_in, DRIVE_SPEED, true);
  littleSirWilliam.set_value(false);
  chassis.pid_wait();

  // go from side code
  // chassis.pid_turn_set(88.5_deg, 50); // get the park zone blocks
  // chassis.pid_wait();
  // chassis.pid_drive_set(10.5_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // chassis.pid_turn_set(45_deg, 50);
  // chassis.pid_wait();
  // chassis.pid_drive_set(27_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // intakeHoard();
  // chassis.pid_turn_set(90_deg, 50);
  // chassis.pid_wait();
  // descore_mech.set_value(true);
  // chassis.drive_set(100, 100); // PARK ZONE CLEARING
  // pros::delay(1500);
  // chassis.drive_set(0, 0);
  // descore_mech.set_value(false);
  // chassis.pid_turn_set(-45_deg, 50);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-25_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // chassis.pid_turn_set(45_deg, 50);
  // chassis.pid_wait();
  // chassis.pid_drive_set(-45_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();
  // intakeDebug();
  // intakeLowerGoal();
  // pros::delay(800);
  // chassis.pid_drive_set(45_in, DRIVE_SPEED, true); 
  // chassis.pid_wait();

  // go from front code
  chassis.pid_turn_set(88.5_deg, 80);
  chassis.pid_wait();
  chassis.pid_drive_set(30_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, 80);
  chassis.pid_wait();
  intakeHoard();
  descore_mech.set_value(true);
  chassis.pid_drive_set(15_in, 80, true); 
  chassis.pid_wait();
  chassis.pid_drive_set(-20_in, 80, true); 
  chassis.pid_wait();
  descore_mech.set_value(false);
  chassis.pid_turn_set(-45_deg, 80);
  chassis.pid_wait();
  chassis.pid_drive_set(-20_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(45_deg, 80);
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(800);
  chassis.pid_drive_set(-35_in, DRIVE_SPEED, true); 
  chassis.pid_wait();

  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-0.3_deg, 40);
  chassis.pid_wait();
  chassis.pid_drive_set(20.5_in, 70, true);
  chassis.pid_wait();
  intakeHoard();
  pros::delay(1200); // wait enough to Matchload ALL Blocks
  // Moves backwards and moves across the field
  chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  chassis.pid_turn_set(-45_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(17.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-180_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(86_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(-45_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  // Turn and then score on long goal
  chassis.pid_turn_set(-179.5_deg, 50); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intakeDebug();
  intakeUpperGoal();
  littleSirWilliam.set_value(true);
  pros::delay(1800); // wait enough to score ALL Blocks
  intakeHoard();
  chassis.pid_drive_set(38_in, 60, true);
  chassis.pid_wait();
  pros::delay(1000); // wait enough to matchload ALL Blocks
  chassis.pid_drive_set(-33_in, 90, true);
  chassis.pid_wait();
  intakeDebug();
  intakeUpperGoal();
  pros::delay(1800); // wait enough to score ALL Blocks
  chassis.pid_drive_set(12_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  chassis.pid_turn_set(90_deg, 70); 
  chassis.pid_wait();
  chassis.pid_drive_set(-43_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  chassis.pid_turn_set(0_deg, 70); 
  chassis.pid_wait();
  chassis.pid_drive_set(-45_in, 80, true);
  chassis.pid_wait();
}

void elim_right(){
  // 4 blocks push
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(90_deg, 50); 
  chassis.pid_wait();

  intakeHoard();
  chassis.pid_drive_set(14_in, 60, true); 
  chassis.pid_wait();
  // pros::delay(80); // enough to get 3 blocks)
  hood.set_value(true);
  chassis.pid_drive_set(-34_in, 110, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(1000); // (enough to score 4 blocks)
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  chassis.pid_turn_set(0_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(90_deg, 50); 
  chassis.pid_wait();

  chassis.pid_drive_set(-25_in, 50, true); 
  chassis.pid_wait();
}

void elim_right_middle(){
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(90_deg, 50); 
  chassis.pid_wait();

  intakeHoard();
  chassis.pid_drive_set(14_in, 60, true); 
  chassis.pid_wait();
  // pros::delay(80); // enough to get 3 blocks)
  hood.set_value(true);
  chassis.pid_drive_set(-34_in, 110, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(1000); // (enough to score 4 blocks)
  chassis.pid_drive_set(8_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(false);
  cut_intake();
  chassis.pid_turn_set(0_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-135_deg, 50); 
  chassis.pid_wait();
  intakeHoard();
  chassis.pid_drive_set(30.5_in, 70, true); 
  chassis.pid_wait();
  outtake();
  pros::delay(1100); // enough to score 3 blocks
  chassis.pid_drive_set(-32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(30_in, 60, true); 
  chassis.pid_wait();
}

void elim_right_all(){
  // 7 block push
  chassis.pid_drive_set(35_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
}

void elim_left(){
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-90_deg, 50); 
  chassis.pid_wait();

  intakeHoard();
  chassis.pid_drive_set(14_in, 60, true); 
  chassis.pid_wait();
  // pros::delay(80); // enough to get 3 blocks)
  hood.set_value(true);
  chassis.pid_drive_set(-34_in, 110, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(1000); // (enough to score 4 blocks)
  littleSirWilliam.set_value(false);

  chassis.pid_drive_set(8_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  cut_intake();
  chassis.pid_turn_set(0_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-9.5_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, 50); 
  chassis.pid_wait();

  chassis.pid_drive_set(-23_in, 40, true); 
  chassis.pid_wait();
}

void elim_left_middle(){
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-90_deg, 50); 
  chassis.pid_wait();

  intakeHoard();
  chassis.pid_drive_set(14_in, 60, true); 
  chassis.pid_wait();
  // pros::delay(80); // enough to get 3 blocks)
  hood.set_value(true);
  chassis.pid_drive_set(-34_in, 110, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(800); // (enough to score 4 blocks)
  littleSirWilliam.set_value(false);

  chassis.pid_drive_set(20_in, 110, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(135_deg, 80); 
  chassis.pid_wait();
  intakeHoard();
  chassis.pid_drive_set(40_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-44_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 110, true); 
  chassis.pid_wait();
  outtake();
  pros::delay(200);
  intakeLowerGoal();
  pros::delay(1200);
  chassis.pid_drive_set(33_in, 110, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-90_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-33_in, 50, true); 
  chassis.pid_wait();
}
void elim_left_all(){

}

void blue_autonomous_right() {
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  descore_mech.set_value(true);
  intakeHoard();
  chassis.pid_drive_set(40_in, 50, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-12.5_in, 80, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-70_deg, 70); 
  chassis.pid_wait();
  cut_intake();
  chassis.pid_drive_set(12.8_in, 70, true); 
  chassis.pid_wait();
  outtake();
  pros::delay(100);
  intakeHoard();
  pros::delay(1200);
  outtake();
  pros::delay(200);
  cut_intake();
  chassis.pid_drive_set(-44.5_in, 90, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(158_deg, 50); 
  chassis.pid_wait();
  intakeHoard(); 
  chassis.pid_drive_set(34_in, 60, true); 
  chassis.pid_wait(); 
  pros::delay(200);
  chassis.pid_drive_set(-21_in, 60, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(163_deg, 50); 
  chassis.pid_wait();
  descore_mech.set_value(false);
  cut_intake(); 
  chassis.pid_drive_set(-13_in, 100, true); 
  chassis.pid_wait(); 
  cut_intake();
  pros::delay(200);
  intakeUpperGoal(); // score on long goal
  pros::delay(900);
  chassis.pid_drive_set(10_in, 100, true); 
  chassis.pid_drive_set(-10_in, 100, true); 
  // teamcolor = "Blue";
}

void red_autonomous_right() {
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  descore_mech.set_value(true);
  intakeHoard();
  chassis.pid_drive_set(40_in, 50, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-13_in, 80, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(-70_deg, 70); 
  chassis.pid_wait();
  cut_intake();
  chassis.pid_drive_set(13.8_in, 70, true); 
  chassis.pid_wait();
  outtake();
  pros::delay(100);
  intakeHoard();
  pros::delay(1200);
  outtake();
  pros::delay(200);
  cut_intake();
  chassis.pid_drive_set(-44.5_in, 90, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(158_deg, 50); 
  chassis.pid_wait();
  intakeHoard(); 
  chassis.pid_drive_set(34_in, 60, true); 
  chassis.pid_wait(); 
  pros::delay(200);
  chassis.pid_drive_set(-21_in, 60, true); 
  chassis.pid_wait();
  chassis.pid_turn_set(163_deg, 50); 
  chassis.pid_wait();
  descore_mech.set_value(false);
  cut_intake(); 
  chassis.pid_drive_set(-13_in, 100, true); 
  chassis.pid_wait(); 
  cut_intake();
  pros::delay(200);
  intakeUpperGoal(); // score on long goal
  pros::delay(900);
  chassis.pid_drive_set(10_in, 100, true); 
  chassis.pid_drive_set(-10_in, 100, true); 
  // teamcolor = "Red";
}

void red_autonomous_left() {
  // teamcolor = "Red";
  // skills code
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  littleSirWilliam.set_value(false);
  descore_mech.set_value(true);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  intakeHoard();
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intakeHoard();
  pros::delay(200);
  outtake();
  pros::delay(300);
  intakeUpperGoal();
  pros::delay(1500);
  cut_intake();
  chassis.pid_drive_set(45_in, 120, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intakeHoard();
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
  outtake();
  pros::delay(200);
  intakeUpperGoal();
  pros::delay(1400);
  cut_intake();
}

void blue_autonomous_left() {
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  littleSirWilliam.set_value(false);
  descore_mech.set_value(true);
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  intakeHoard();
  chassis.pid_drive_set(20_in, 55, true); 
  chassis.pid_wait(); 
  chassis.pid_drive_set(-9_in, 80, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-100_deg, 50); 
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, DRIVE_SPEED, true); 
  chassis.pid_wait(); 
  intakeHoard();
  pros::delay(200);
  outtake();
  pros::delay(300);
  intakeUpperGoal();
  pros::delay(1500);
  cut_intake();
  chassis.pid_drive_set(45_in, 120, true); 
  chassis.pid_wait(); 
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(-149_deg, TURN_SPEED); 
  chassis.pid_wait();
  intakeHoard();
  chassis.pid_drive_set(32_in, 45, true); 
  chassis.pid_wait(); 
  pros::delay(600);
  chassis.pid_drive_set(-20_in, 60, true); 
  chassis.pid_wait(); 
  chassis.pid_turn_set(-153_deg, TURN_SPEED); 
  chassis.pid_wait();
  chassis.pid_drive_set(-12_in, 60, true); 
  chassis.pid_wait(); 
  descore_mech.set_value(false);
  outtake();
  pros::delay(200);
  intakeUpperGoal();
  pros::delay(1400);
  cut_intake();
}

void soloAWP_lower() {
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  pros::adi::DigitalOut hood('C');
  chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
  chassis.pid_wait();
  littleSirWilliam.set_value(true);
  chassis.pid_turn_set(90_deg, 80); 
  chassis.pid_wait();

  intakeHoard();
  chassis.pid_drive_set(14_in, 60, true); 
  chassis.pid_wait();
  // pros::delay(80); // enough to get 3 blocks)
  chassis.pid_drive_set(-32_in, 110, true); 
  chassis.pid_wait();
  intakeUpperGoal();
  pros::delay(600);

  chassis.pid_drive_set(21_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  littleSirWilliam.set_value(false);

  chassis.pid_turn_set(-135_deg, 100); 
  chassis.pid_wait();
  intakeHoard();

  chassis.pid_drive_set(50_in, 90, true);
  chassis.pid_wait();
  
  outtake();
  pros::delay(400);

  chassis.pid_drive_set(-5_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(170_deg, 100); 
  chassis.pid_wait();
  littleSirWilliam.set_value(false);

  intakeHoard();
  chassis.pid_drive_set(45_in, 80, true);
  chassis.pid_wait();
  littleSirWilliam.set_value(true);

  chassis.pid_turn_set(140_deg, 100); 
  chassis.pid_wait();

  chassis.pid_drive_set(25.5_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intakeHoard();
  hood.set_value(true);
  chassis.pid_turn_set(90_deg, 100); 
  chassis.pid_wait();
  chassis.pid_drive_set(-14_in, DRIVE_SPEED, true);
  chassis.pid_wait();
  intakeUpperGoal(); // LONG GOAL SCORING
  pros::delay(1500);
}

// void soloAWP(){
//   pros::adi::DigitalOut littleSirWilliam('A');
//   pros::adi::DigitalOut descore_mech('B');
//   pros::adi::DigitalOut hood('C');
//   chassis.pid_drive_set(32_in, DRIVE_SPEED, true); 
//   chassis.pid_wait();
//   littleSirWilliam.set_value(true);
//   chassis.pid_turn_set(90_deg, 50); 
//   chassis.pid_wait();

//   intakeUpperGoal();
//   chassis.pid_drive_set(14_in, 60, true); 
//   chassis.pid_wait();
//   // pros::delay(80); // enough to get 3 blocks)
//   hood.set_value(true);
//   chassis.pid_drive_set(-34_in, 110, true); 
//   chassis.pid_wait();
//   intakeFirst.move_velocity(-100000);
//   intakeSecond.move_velocity(100000);
//   pros::delay(200);

//   chassis.pid_drive_set(16_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   littleSirWilliam.set_value(false);

//   chassis.pid_turn_set(-135_deg, 100); 
//   chassis.pid_wait();

//   chassis.pid_drive_set(30_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   hood.set_value(false);
//   intakeHoard();
//   littleSirWilliam.set_value(true);

//   chassis.pid_turn_set(175_deg, 100); 
//   chassis.pid_wait();
//   littleSirWilliam.set_value(false);

//   intakeHoard();
//   intakeFirst.move_velocity(-5000);
//   chassis.pid_drive_set(52.5_in, 100, true);
//   chassis.pid_wait();
//   littleSirWilliam.set_value(true);

//   chassis.pid_turn_set(138_deg, 100); 
//   chassis.pid_wait();
//   intakeFirst.move_velocity(-5000);
//   intakeSecond.move_velocity(200); // MIDDLE GOAL SCORING
//   chassis.pid_drive_set(-22_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   intakeFirst.move_velocity(-5000);
//   intakeSecond.move_velocity(1000);
//   pros::delay(100);
//   intakeFirst.move_velocity(100);
//   intakeSecond.move_velocity(-100);
//   littleSirWilliam.set_value(false);

//   chassis.pid_drive_set(46_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   intakeHoard();
//   hood.set_value(true);
//   chassis.pid_turn_set(90_deg, 100); 
//   chassis.pid_wait();
//   chassis.pid_drive_set(-16_in, DRIVE_SPEED, true);
//   chassis.pid_wait();
//   intakeFirst.move_velocity(-100000);
//   intakeSecond.move_velocity(100000); // LONG GOAL SCORING
//   pros::delay(1500);
// }
