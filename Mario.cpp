#include "Mario.hpp"


void Mario::reset(int Y, int Lives, int Coins) {

	x = 400;
	y = Y;
	vx = MARIO_VX;
	vy0 = 0;
	dirx = "right";
	mode = "normal";
	status = "standing";
	walking_step = 1;
	lives = Lives;
	coins = Coins;

}


int Mario::get_x() { return x; }


int Mario::get_y() { return y; }


float Mario::get_vy0() { return vy0; }


std::string Mario::get_status() { return status; }


int Mario::get_lives() { return lives; }


int Mario::get_coins() { return coins; }


void Mario::set_vy0(float VY0) { vy0 = VY0; }


void Mario::set_status(std::string Status) { status = Status; }


void Mario::add_y(int Y) { y += Y; }


void Mario::inc_lives() { lives++; }


void Mario::dec_lives() { lives--; }


void Mario::inc_coins() { coins++; }


void Mario::go_left(float time_delay) {

	dirx = "left";

	if(x > 0) x -= vx * time_delay;

	if(status != "jumping")
		status = "walking";

}


void Mario::go_right(Camera & cam, float time_delay) {

	dirx = "right";

	if(x < 500) x += vx * time_delay;

	else cam.go_right(time_delay);

	if(status != "jumping")
		status = "walking";

}


void Mario::continue_jumping(int clay_number, float scale, float time_delay, float a, int y_cross, bool it_can_go_flag) {

	int h0 = 720 - clay_number * 16 * scale - 16 * scale;

	if(status == "jumping") {

		if(it_can_go_flag) {	

			int h0 = 720 - clay_number * 16 * scale - 16 * scale;

			y += 0.5 * a * (time_delay * time_delay) + vy0 * time_delay;
			vy0 += a * time_delay;
			
			if(y >= h0) {
				status = "standing";
				y = h0;
			}

		}

		else {

			y = y_cross;

			if(vy0 <= - 0.5 * a)
				vy0 = -0.5 * a;
			else
				status = "standing";

		}

		if(y >= h0) {
			y = h0;
			status = "standing";
		}

	}

}


void Mario::draw(Window & win, float scale) {

	std::string image_address = "assets/sprites/mario/";

	image_address += mode + "/" + status;

	if(status != "dead") {

		image_address += "-" + dirx;

		if(status == "walking") {

			image_address += "-" + std::to_string(walking_step);

			if(walking_step == 3) walking_step = 1;
			else walking_step++;

		}

	}

	image_address += ".png";

	win.draw_img(image_address, Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}