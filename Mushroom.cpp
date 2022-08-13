#include "Mushroom.hpp"


int Mushroom::get_x() { return x; }


int Mushroom::get_y() { return y; }


std::string Mushroom::get_type() { return type; }


void Mushroom::go_by_self(float time_delay) { x += vx * time_delay; }


void Mushroom::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Mushroom::draw(Window & win, float scale) {

	std::string image_address = "assets/sprites/objects/mushroom/" + type + ".png";

    win.draw_img(image_address, Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}