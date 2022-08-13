#include "Coin.hpp"


int Coin::get_x() { return x; }


int Coin::get_y() { return y; }


int Coin::get_rising_step() { return rising_step; }


void Coin::dec_rising_step() { rising_step--; }


void Coin::go_by_self(float time_delay) { y += vy * time_delay; }


void Coin::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Coin::draw(Window & win, float scale) {

    win.draw_img("assets/sprites/objects/coin.png", Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}