#include "Hole.hpp"


int Hole::get_x() { return x; }


int Hole::get_y() { return y; }


void Hole::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Hole::draw(Window & win, float scale) {

	win.draw_img("assets/images/hole.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}