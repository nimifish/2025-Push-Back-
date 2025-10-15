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
extern pros::ADIDigitalOut littleSirWilliam('H');
extern pros::ADIDigitalOut descore_mech('C');
bool lwState = false;
bool dsState = false;

// other stuffs yeah

pros::Optical color_sort(21);
std::string teamcolor = "Red"; //need a way to change this