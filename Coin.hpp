#ifndef COIN_H
#define COIN_H


#include "src/rsdl.hpp"
#include "Camera.hpp"


const float COIN_VY = -1.25;


class Coin {

    public:
    Coin(int X, int Y) :x(X), y(Y), vy(COIN_VY), rising_step(6) {};
    int get_x();
    int get_y();
    int get_rising_step();
    void dec_rising_step();
    void go_by_self(float time_delay);
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    float vy;
    int rising_step;
    
};


#endif