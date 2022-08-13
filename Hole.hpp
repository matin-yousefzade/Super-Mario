#ifndef HOLE_H
#define HOLE_H


#include "src/rsdl.hpp"
#include "Camera.hpp"


class Hole {

    public:
    Hole(int X, int Y) :x(X), y(Y) {};
    int get_x();
    int get_y();
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    
};


#endif