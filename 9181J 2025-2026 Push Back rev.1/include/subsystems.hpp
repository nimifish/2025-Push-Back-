#pragma once


#include "EZ-Template/api.hpp"
#include "api.h"


extern Drive chassis;

// intakes
inline pros::Motor intakeFirst(20);
inline pros::Motor intakeSecond(21);

// // pneumatics
// extern pros::ADIDigitalOut littleSirWilliam ('H', false);
// extern pros::ADIDigitalOut descore_mech('C');

// // Sensors
// inline pros::Optical color_sort(21);

// Global Variables
// extern bool color_sort_state;
extern std::string teamcolor;
extern bool lwState;
extern bool dsState;

void intakeLowerGoal();
void intakeUpperGoal();
void intakeHoard();
void intakeSorters();
void outtake();


// tracking wheel
double odom_distance = 5.0; // replace with actual distance later
ez::tracking_wheel vertical(1, 2.0, odom_distance, 1.0);