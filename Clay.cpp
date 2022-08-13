#include "Clay.hpp"


int Clay::get_x() { return x; }


int Clay::get_y() { return y; }


void Clay::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Clay::draw(Window & win, float scale) {

	win.draw_img("assets/sprites/objects/bricks_blocks/clay.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}