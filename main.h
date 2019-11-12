/**
 * \file main.h
 *
 * Contains common definitions and header files used throughout your PROS
 * project.
 *
 * Copyright (c) 2017-2019, Purdue University ACM SIGBots.
 * All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef _PROS_MAIN_H_
#define _PROS_MAIN_H_

/**
 * If defined, some commonly used enums will have preprocessor macros which give
 * a shorter, more convenient naming pattern. If this isn't desired, simply
 * comment the following line out.
 *
 * For instance, E_CONTROLLER_MASTER has a shorter name: CONTROLLER_MASTER.
 * E_CONTROLLER_MASTER is pedantically correct within the PROS styleguide, but
 * not convienent for most student programmers.
 */
#define PROS_USE_SIMPLE_NAMES

/**
 * If defined, C++ literals will be available for use. All literals are in the
 * pros::literals namespace.
 *
 * For instance, you can do `4_mtr = 50` to set motor 4's target velocity to 50
 */
#define PROS_USE_LITERALS

#include "api.h"

/**
 * You should add more #includes here
 */
#include "okapi/api.hpp"
//#include "pros/api_legacy.h"

/**
 * If you find doing pros::Motor() to be tedious and you'd prefer just to do
 * Motor, you can use the namespace with the following commented out line.
 *
 * IMPORTANT: Only the okapi or pros namespace may be used, not both
 * concurrently! The okapi namespace will export all symbols inside the pros
 * namespace.
 */
// using namespace pros;
// using namespace pros::literals;
using namespace okapi;
using namespace std;

#include <fstream>
#include <string>
// #include <sstream>
// #include <iterator>

/**
 * Prototypes for the competition control tasks are redefined here to ensure
 * that they can be called from user code (i.e. calling autonomous from a
 * button press in opcontrol() for testing purposes).
 */
#ifdef __cplusplus
extern "C" {
#endif
void autonomous();
void initialize();
void disabled();
void competition_initialize();
void opcontrol();

void inc_auton_mode();
void dec_auton_mode();

// motor functions
void lift_jpid();
void move_lift(int);
void move_claw(int);
void move_ramp(int);
void move_all(int);
void ramp_jpid();
void front_left_wheel_move(int);
void front_right_wheel_move(int);
void rear_left_wheel_move(int);
void rear_right_wheel_move(int);
int get_ramp_angle();
void full_ramp();
void lower_ramp();
void set_max_velocity(int);

void deploy();

void process_controller(int, int, int, int, int, int, int, int, int);

void run_replay(string);
void busy_wait(int);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#endif

#endif  // _PROS_MAIN_H_
