#include "main.h"

// bool color_sort_state = false;
bool lwState = false;
bool dsState = false;
bool hdState = false;
std::string teamcolor = "Red"; //need a way to change this

void intakeLowerGoal() {
    intakeFirst.move_velocity(-1000);
    intakeSecond.move_velocity(-500);
}

void intakeUpperGoal() {
    intakeFirst.move_velocity(-1000);
    intakeSecond.move_velocity(1000);
}

void intakeHoard() {
    intakeFirst.move_velocity(-1000);
    intakeSecond.move_velocity(0);
}

void outtake() {
    intakeFirst.move_velocity(1000);
    intakeSecond.move_velocity(-1000);
}

void cut_intake() {
    intakeFirst.move_velocity(0);
    intakeSecond.move_velocity(0);
}

// void intakeSorter() {
//     intakeFirst.move_velocity(1000);
//     double getHue = color_sort.get_hue(); //get the raw color data of the block. 
//     if (((getHue < 20 or getHue > 340) and (teamcolor == "Red")) or ((270 > getHue > 180) and (teamcolor == "Blue"))){ // if the color is close enough to the one we want
//         intakeSecond.move_velocity(-1000);} // go in the top one, might not work because we have to tweak the delay and stuff.

//     else{
//         intakeSecond.move_velocity(1000);} // do not do that. no.
// }