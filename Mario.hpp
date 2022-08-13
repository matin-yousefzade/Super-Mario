#ifndef MARIO_H
#define MARIO_H


#include <string>
#include <vector>
#include "src/rsdl.hpp"
#include "Camera.hpp"


const float MARIO_VX = 0.15;


class Mario {

    public:
    Mario(int Y, int Lives, int Coins) :x(400), y(Y), vx(MARIO_VX), vy0(0), dirx("right"), mode("normal"), status("standing"), walking_step(1), lives(Lives), coins(Coins) {};
    void reset(int Y, int Lives, int Coins);
    int get_x();
    int get_y();
    float get_vy0();
    std::string get_status();
    int get_lives();
    int get_coins();
    void set_vy0(float VY0);
    void set_status(std::string Status);
    void add_y(int Y);
    void inc_lives();
    void dec_lives();
    void inc_coins();
    void go_left(float time_delay);
    void go_right(Camera & cam, float time_delay);
    void continue_jumping(int clay_number, float scale, float time_delay, float a, int y_cross, bool it_can_go_flag);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    float vx;
    float vy0;
    std::string dirx;
    std::string mode;
    std::string status;
    int walking_step;
    int lives;
    int coins;

};


#endif