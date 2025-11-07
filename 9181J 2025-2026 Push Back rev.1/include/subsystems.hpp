#pragma once


#include "EZ-Template/api.hpp"
#include "api.h"


extern Drive chassis;

// intakes
inline pros::Motor intakeFirst(20);
inline pros::Motor intakeThird(21);
inline pros::MotorGroup intake_group({20, 21});
inline pros::Motor intakeFourth(15);

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
