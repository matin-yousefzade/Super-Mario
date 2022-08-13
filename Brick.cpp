#include "Brick.hpp"


int Brick::get_x() { return x; }


int Brick::get_y() { return y; }


void Brick::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Brick::draw(Window & win, float scale) {

	win.draw_img("assets/sprites/objects/bricks_blocks/brick.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}