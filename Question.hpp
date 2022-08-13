#ifndef QUESTION_H
#define QUESTION_H


#include "src/rsdl.hpp"
#include "Camera.hpp"


class Question {

    public:
    Question(int X, int Y, char Content) :x(X), y(Y), content_type(Content), status("full"), showing_step(0) {};
    int get_x();
    int get_y();
    char get_content_type();
    std::string get_status();
    void set_status(std::string String);
    void go_by_camera(Camera cam, float time_delay);
    void draw(Window & win, float scale);

    private:
    int x;
    int y;
    char content_type;
    std::string status;
    int showing_step;
    
};


#endif