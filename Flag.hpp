#ifndef FLAG_H
#define FLAG_H


#include "src/rsdl.hpp"
#include "Camera.hpp"


class Flag {

    public:
    Flag(int X, int Y, int Length) :x(X), y(Y), length(Length) {};
    int get_x();
    int get_y();
    int get_length();
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    int length;
    
};


#endif