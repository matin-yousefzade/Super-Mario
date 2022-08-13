#ifndef GOOMBA_H
#define GOOMBA_H


#include <string>
#include "src/rsdl.hpp"
#include "Camera.hpp"


const float GOOMBA_VX = 0.125;


class Goomba {

    public:
    Goomba(int X, int Y) :x(X), y(Y), vx(GOOMBA_VX), dirx("left"), status("walking"), walking_step(1), dead_time(75) {};
    int get_x();
    int get_y();
    std::string get_status();
    int get_dead_time();
    void set_status(std::string Status);
    void dec_dead_time();
    void go_by_self(float time_delay);
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    float vx;
    std::string dirx;
    std::string status;
    int walking_step;
    int dead_time;

};


#endif