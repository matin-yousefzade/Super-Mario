#include "Goomba.hpp"


int Goomba::get_x() { return x; }


int Goomba::get_y() { return y; }


std::string Goomba::get_status() { return status; }


int Goomba::get_dead_time() { return dead_time; }


void Goomba::set_status(std::string String) { status = String; }


void Goomba::dec_dead_time() { dead_time--; }


void Goomba::go_by_self(float time_delay) {

	if(dirx == "left")
		x -= vx * time_delay;
	else
		x += vx * time_delay;

}


void Goomba::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Goomba::draw(Window & win, float scale) {

	std::string image_address = "assets/sprites/enemies/little_goomba/";

	image_address += status;

	if(status != "dead") {

		image_address += "-" + std::to_string(walking_step);

		if(walking_step == 2) walking_step = 1;
		else walking_step++;

	}

	image_address += ".png";

	win.draw_img(image_address, Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}