#include "Flag.hpp"


int Flag::get_x() { return x; }


int Flag::get_y() { return y; }


int Flag::get_length() { return length; }


void Flag::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Flag::draw(Window & win, float scale) {

	win.draw_img("assets/sprites/objects/flag/head.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

	for(int i = 1; i < length; i++)
		win.draw_img("assets/sprites/objects/flag/body.png", Rectangle(Point(x, y + i * 16 * scale), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}