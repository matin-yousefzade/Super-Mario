#ifndef MUSHROOM_H
#define MUSHROOM_H


#include <string>
#include "src/rsdl.hpp"
#include "Camera.hpp"


const float MUSHROOM_VX = 0.125;


class Mushroom {

    public:
    Mushroom(int X, int Y, std::string Type) :x(X), y(Y), vx(MUSHROOM_VX), dirx("right"), type(Type) {};
    int get_x();
    int get_y();
    std::string get_type();
    void go_by_self(float time_delay);
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    float vx;
    std::string dirx;
    std::string type;
    
};


#endif