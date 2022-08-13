#include "Pipe.hpp"


int Pipe::get_x() { return x; }


int Pipe::get_y() { return y; }


int Pipe::get_length() { return length; }


void Pipe::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Pipe::draw(Window & win, float scale) {

	win.draw_img("assets/sprites/objects/pipe/head-left.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));
	win.draw_img("assets/sprites/objects/pipe/head-right.png", Rectangle(Point(x + 16 * scale, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

	for(int i = 1; i < length; i++) {
		win.draw_img("assets/sprites/objects/pipe/left.png", Rectangle(Point(x, y + i * 16 * scale), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));
		win.draw_img("assets/sprites/objects/pipe/right.png", Rectangle(Point(x + 16 * scale, y + i * 16 * scale), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));
	}

}