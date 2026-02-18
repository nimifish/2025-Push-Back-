#pragma once


#include "EZ-Template/api.hpp"
#include "api.h"


extern Drive chassis;
    
// intakes
inline pros::Motor intakeFirst(20);
inline pros::Motor intakeSecond(21);
inline pros::Motor intakeThird(8);

// // Sensors
// inline pros::Optical color_sort(21);

// Global Variables
// extern bool color_sort_state;
extern std::string teamcolor;
extern bool lwState;
extern bool dsState;
extern bool hdState;

void intakeLowerGoal();
void intakeUpperGoal();
void intakeHoard();
void intakeDebug();
void intakeSorters();
void outtake();
void cut_intake();
