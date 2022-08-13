#include "Camera.hpp"


void Camera::reset(int X) {

	x = X;
	vx = CAMERA_VX;

}


int Camera::get_x() { return x; }


float Camera::get_vx() { return vx; }


void Camera::go_right(float time_delay) {

	if(x < 10520) x += vx * time_delay;
	else x = 0;

}