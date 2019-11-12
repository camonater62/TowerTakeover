#include "main.h"

// 1850 // 1000 // 460
pros::Motor front_left_wheel(5, MOTOR_GEARSET_36);
pros::Motor front_right_wheel(10, MOTOR_GEARSET_36, true);
pros::Motor rear_left_wheel(6, MOTOR_GEARSET_36);
pros::Motor rear_right_wheel(20, MOTOR_GEARSET_36, true);
pros::Motor lift(17, MOTOR_GEARSET_36);
pros::Motor left_claw(1, MOTOR_GEARSET_36);
pros::Motor right_claw(19, MOTOR_GEARSET_36);
pros::Motor ramp(18, MOTOR_GEARSET_36, true);

pros::ADIPotentiometer ramp_angle('a');

void front_left_wheel_move(int velocity) {
	front_left_wheel.move(velocity);
}

void front_right_wheel_move(int velocity) {
	front_right_wheel.move(velocity);
}

void rear_right_wheel_move(int velocity) {
	rear_right_wheel.move(velocity);
}

void rear_left_wheel_move(int velocity) {
	rear_left_wheel.move(velocity);
}

void move_all(int velocity) {
	front_left_wheel_move(velocity);
	front_right_wheel_move(velocity);
	rear_left_wheel_move(velocity);
	rear_right_wheel_move(velocity);
}

void lift_jpid() {
	pros::lcd::clear_line(4);
	pros::lcd::set_text(4, "Lift: {" + to_string(-lift.get_actual_velocity()) + "}");
	lift.move(-lift.get_actual_velocity());
}

void move_lift(int velocity) {
	lift.move_velocity(velocity);
}

void move_claw(int velocity) {
	right_claw.move_velocity(-velocity);
	left_claw.move_velocity(velocity);
}

void move_ramp(int velocity) {
	ramp.move_velocity(velocity);
}

void ramp_jpid() {
/*	pros::lcd::clear_line(5);
	double amount = -ramp.get_actual_velocity();
	pros::lcd::set_text(5, "Ramp: {" + to_string(amount) + "}");
	ramp.move_velocity(amount);*/
	if(get_ramp_angle() >= 1800 && get_ramp_angle() <= 1850) {
		ramp.move_velocity(-1);
	} else {
		ramp.move_velocity(0);
	}
}

int get_ramp_angle() {
	return ramp_angle.get_value();
}

void full_ramp() {
	move_ramp(100);
	while(ramp_angle.get_value() > 900) {
	//	delay(1);
	}
	move_ramp(0);
	pros::delay(100);
	move_ramp(30);
	while(ramp_angle.get_value() > 640) {

	}
	move_ramp(0);
}

void lower_ramp() {
	move_ramp(-100);
	while(ramp_angle.get_value() < 1850) {
		// delay(1);
	}
	move_ramp(0);
}

void process_controller(int left, int right, int r1, int r2, int l1, int l2, int up, int down, int b) {
	front_left_wheel_move(left);
	front_right_wheel_move(right);
	rear_left_wheel_move(left);
	rear_right_wheel_move(right);


	// lift movement
	if(r1) {
		move_lift(100);
	} else if(r2) {
		move_lift(-100);
	} else {
		lift_jpid();
	}


	// claw movement
	if(l1) {
		move_claw(100);
	} else if(l2) {
		move_claw(-100);
	} else {
		move_claw(0);
	}


	// ramp movement
	if(up) {
		move_ramp(get_ramp_angle() <= 1100 ? 25 : 80);
	} else if(down) {
		move_ramp(-80);
	} else {
		ramp_jpid();
	}

	if(b) {
		deploy();
	}

	pros::lcd::clear_line(7);
	pros::lcd::set_text(7, "Ramp Pos: " + to_string(get_ramp_angle()));
}

void deploy() {
	move_lift(-50);
	move_all(100);
	pros::delay(100);
	move_all(0);
	move_ramp(100);
	while(ramp_angle.get_value() > 960);
	move_ramp(0);
	move_claw(-100);
	pros::delay(750);
	move_claw(0);
	lower_ramp();
	move_lift(0);
	pros::delay(100);
}
