#include "main.h"

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

pros::Controller master(pros::E_CONTROLLER_MASTER);

// LEFT RIGHT R1 R2 L1 L2 UP DOWN
// [-127, 127][0, 1]--------------

void opcontrol() {
	string filename = "/usd/recent";
	ofstream replay(filename);
	while (true) {

		int power = master.get_analog(ANALOG_LEFT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = power + turn;
		int right = power - turn;
		int r1 = master.get_digital(DIGITAL_R1);
		int r2 = master.get_digital(DIGITAL_R2);
		int l1 = master.get_digital(DIGITAL_L1);
		int l2 = master.get_digital(DIGITAL_L2);
		int up = master.get_digital(DIGITAL_UP);
		int down = master.get_digital(DIGITAL_DOWN);
		int b = master.get_digital(DIGITAL_B);

		process_controller(left, right, r1, r2, l1, l2, up, down, b);

		if(replay.is_open()) {
			replay << left << '\t' << right << '\t';
			replay << r1 << '\t' << r2 << '\t';
			replay << l1 << '\t' << l2 << '\t';
			replay << up << '\t' << down << '\t';
			replay << b << '\n';
		}

		if(master.get_digital(DIGITAL_Y)) {
			if(replay.is_open())
				replay.close();
		}
		pros::delay(2);
	}
}
