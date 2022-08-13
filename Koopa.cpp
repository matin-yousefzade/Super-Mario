#include "Koopa.hpp"


int Koopa::get_x() { return x; }
    

int Koopa::get_y() { return y; }


std::string Koopa::get_status() { return status; }


std::string Koopa::get_dead_step() { return dead_step; }


void Koopa::set_status(std::string String) { status = String; }


void Koopa::set_dead_step(std::string Dead_step) { dead_step = Dead_step; }


void Koopa::go_by_self(float time_delay) {

	if(status == "dead" && dead_step == "dynamic")
		vx = DEAD_KOOPA_VX;

	if(dirx == "left")
		x -= vx * time_delay;
	else
		x += vx * time_delay;

}


void Koopa::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Koopa::draw(Window & win, float scale) {

	std::string image_address = "assets/sprites/enemies/koopa_troopa/";

	image_address += status;

	if(status != "dead") {

		image_address += "-" + dirx + "-" + std::to_string(walking_step);

		if(walking_step == 2) walking_step = 1;
		else walking_step++;

	}

	image_address += ".png";

	if(status == "dead")
		win.draw_img(image_address, Rectangle(Point(x, y + 8 * scale), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));
	else
		win.draw_img(image_address, Rectangle(Point(x, y), 16 * scale, 24 * scale), Rectangle(Point(0, 0), 16, 24));

}