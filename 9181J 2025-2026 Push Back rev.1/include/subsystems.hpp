#pragma once


#include "EZ-Template/api.hpp"
#include "api.h"


extern Drive chassis;


inline pros::Motor intakeFirst(20);
inline pros::Motor intakeThird(11);
inline pros::Motor_Group intake_group({intakeFirst, intakeThird});
inline pros::Motor intakeFourth(15);


// Your motors, sensors, etc. should go here.  Below are examples


// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
