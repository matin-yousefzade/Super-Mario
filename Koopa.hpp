#ifndef KOOPA_H
#define KOOPA_H


#include <string>
#include "src/rsdl.hpp"
#include "Camera.hpp"


const float KOOPA_VX = 0.125;
const float DEAD_KOOPA_VX = 0.5;


class Koopa {

    public:
    Koopa(int X, int Y) :x(X), y(Y), vx(KOOPA_VX), dirx("left"), status("walking"), walking_step(1), dead_step("static") {};
    int get_x();
    int get_y();
    std::string get_status();
    std::string get_dead_step();
    void set_status(std::string Status);
    void set_dead_step(std::string Dead_step);
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
    std::string dead_step;

};


#endif