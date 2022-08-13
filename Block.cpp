#include "Block.hpp"


int Block::get_x() { return x; }


int Block::get_y() { return y; }


void Block::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Block::draw(Window & win, float scale) {

	win.draw_img("assets/sprites/objects/bricks_blocks/block.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}