#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    {14, -12, -16},     // Left Chassis Ports (negative port reverse it) port 12 one is screwey..
    {-6, 17, 15},  // Right Chassis Ports (negative port everse it)


    18,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM


  ez::tracking_wheel vert_tracker(2, 2.0, 4.0, 1.0);
/**
 * Runs initialization code. This occurs as soon as the program is started.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configures chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.0);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0.0, 0.0);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to constants from autons.cpp!
  default_constants();

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      {"Skills (just position block below park zone)", skills},
      {"SoloAWP (starts from right)", soloAWP_lower},
      {"Elim Right 4 block + Middle bottom", elim_right_middle},
      {"Elim Left Middle", elim_left_middle},
      {"Elim Left 4 block", elim_left},
      {"Elim Right 4 block", elim_right}
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
}


/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}


/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}


/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}


/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}


/**
 * Ez screen task
 * Adding new pages here will let you view them during user control or autonomous
 * and will help you debug problems you're having
 */
void ez_screen_task() {
  while (true) {
    // Only run this when not connected to a competition switch
    if (!pros::competition::is_connected()) {
      // Blank page for odom debugging
      if (chassis.odom_enabled() && !chassis.pid_tuner_enabled()) {
        // If we're on the first blank page...
        if (ez::as::page_blank_is_on(0)) {
          // Display X, Y, and Theta
          ez::screen_print("x: " + util::to_string_with_precision(chassis.odom_x_get()) +
                               "\ny: " + util::to_string_with_precision(chassis.odom_y_get()) +
                               "\na: " + util::to_string_with_precision(chassis.odom_theta_get()),
                           1);  // Don't override the top Page line
          // Display all trackers that are being used
          screen_print_tracker(chassis.odom_tracker_left, "l", 4);
          screen_print_tracker(chassis.odom_tracker_right, "r", 5);
          screen_print_tracker(chassis.odom_tracker_back, "b", 6);
          screen_print_tracker(chassis.odom_tracker_front, "f", 7);
        }
      }
    }
    // Remove all blank pages when connected to a comp switch
    else {
      if (ez::as::page_blank_amount() > 0)
        ez::as::page_blank_remove_all();
    }
    pros::delay(ez::util::DELAY_TIME);
  }
}
pros::Task ezScreenTask(ez_screen_task);


/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp


    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_LEFT))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }


  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  // pneumatics
  pros::adi::DigitalOut littleSirWilliam('A');
  pros::adi::DigitalOut descore_mech('B');
  // pros::adi::DigitalOut hood('C');

  while (true) {
    // Gives you some extras to make EZ-Template easier
    ez_template_extras();

    // DRIVE TRAIN
    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Currently using Standard Split Arcade drivetrain controls

    // LITTLE WILL

    if (master.get_digital_new_press(DIGITAL_Y)){ // L2 button toggle for little will
      if (lwState == false){ // if the little will mechanism is not extended, activate the piston
        littleSirWilliam.set_value(true);
        lwState = true;}
      else if (lwState == true){ // if the little will mechanism is extended, deactivate the piston
        littleSirWilliam.set_value(false);
        lwState = false;}
      pros::delay(10); // in case of "double pressing"
    }

    // DESCORE MECHANISM

    if (master.get_digital_new_press(DIGITAL_X)){ // Y button toggle for descore mechanism
      if (dsState == false){ // if descore mech is deactivated, activate it
        descore_mech.set_value(true);
        dsState = true;}
      else if (dsState == true){ // if descore mech is activated, deactivate it
        descore_mech.set_value(false);
        dsState = false;}
      pros::delay(10); // in case of "double pressing"
    }

    // HOOD MECHANISM

    // if (master.get_digital_new_press(DIGITAL_RIGHT)){ // L2 button toggle for little will
    //   if (hdState == false){ // if the little will mechanism is not extended, activate the piston
    //     hood.set_value(true);
    //     hdState = true;}
    //   else if (hdState == true){ // if the little will mechanism is extended, deactivate the piston
    //     hood.set_value(false);
    //     hdState = false;}
    //   pros::delay(10); // in case of "double pressing"
    // }

    // INTAKE

    if (master.get_digital(DIGITAL_R2)){ //outtake
      outtake();}
    
    else if (master.get_digital(DIGITAL_R1)){ //intake

      if (master.get_digital(DIGITAL_L2)){ //4th intake switch lowergoal
        intakeLowerGoal();}

      else if (master.get_digital(DIGITAL_L1)){ // hold button to hoard
        intakeUpperGoal();} // hoard intake
      else { //this part is all for uppergoal
        intakeHoard();
      }
    }
    
    else { //if no buttons are pressed i surely hope the motors arent spinning.
      cut_intake();
    }

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
