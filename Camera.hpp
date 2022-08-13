#ifndef CAMERA_H
#define CAMERA_H


const float CAMERA_VX = 0.15;


class Camera {

    public:
    Camera(int X) :x(X), vx(CAMERA_VX) {};
    void reset(int X);
    int get_x();
    float get_vx();
    void go_right(float time_delay);

    private:
    int x;
    float vx;

};


#endif