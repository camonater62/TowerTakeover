#include "main.h"

// Selection

int mode = -1;



string replay_directory = "/usd/";

string replays[] {
	"latest",
	"red_right",
	"red_left",
	"blue_right",
	"blue_left",
	"test"
};
int num_replays = *(&replays + 1) - replays;

void update_lcd() {
	pros::lcd::clear_line(2);
	string auton;
  if(mode < 0 || mode > num_replays)
		auton = "INVALID";
	else
		auton = replays[mode];
	pros::lcd::set_text(2, "Auton mode: " + auton);
}

void inc_auton_mode() {
	if(mode < num_replays)
		mode++;
	update_lcd();
}

void dec_auton_mode() {
	if(mode > 0)
		mode--;
	update_lcd();
}

void run_replay(string filename) {
	ifstream replay(filename);
	int left, right, r1, r2, l1, l2, up, down, b;
	vector<vector<int>> values = vector<vector<int>>();

	// read file into RAM
	while(replay >> left >> right >> r1 >> r2 >> l1 >> l2 >> up >> down >> b) {
		int line[] = {left, right, r1, r2, l1, l2, up, down, b};
		vector<int> vecline(begin(line), end(line));
		values.push_back(vecline);
	}

	// Run replay
	for(int i = 0; i < values.size(); i++) {
		left = values[i][0];
		right = values[i][1];
		r1 = values[i][2];
		r2 = values[i][3];
		l1 = values[i][4];
		l2 = values[i][5];
		up = values[i][6];
		down = values[i][7];
		b = values[i][8];

		process_controller(left, right, r1, r2, l1, l2, up, down, b);
		pros::delay(2);
		busy_wait(9000);
	}
}

// Wait for less then a millisecond
// Roughly 93.6 ns
void busy_wait(int num) {
	vector<int> vec(3, 100);
	for(int i = 0; i < num; i++) {
		int t = vec.back();
		vec.pop_back();
		vec.insert(vec.begin(), t);
	}
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	if(mode < 0 || mode >= num_replays)
		return;
	run_replay(replay_directory + replays[mode]);
}
