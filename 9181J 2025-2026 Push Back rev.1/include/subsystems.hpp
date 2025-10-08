#pragma once


#include "EZ-Template/api.hpp"
#include "api.h"


extern Drive chassis;

// intakes
inline pros::Motor intakeFirst(20);
inline pros::Motor intakeThird(11);
inline pros::MotorGroup intake_group({20, 11});
inline pros::Motor intakeFourth(15);

// pneumatics
// extern pros::ADIDigitalOut littleSirWilliam('A');


// Your motors, sensors, etc. should go here.  Below are examples


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
