#include "Question.hpp"


int Question::get_x() { return x; }


int Question::get_y() { return y; }


char Question::get_content_type() { return content_type; }


std::string Question::get_status() { return status; }


void Question::set_status(std::string Status) { status = Status; }


void Question::go_by_camera(Camera cam, float time_delay) { x -= cam.get_vx() * time_delay; }


void Question::draw(Window & win, float scale) {

	std::string image_address = "assets/sprites/objects/bricks_blocks/question-";

	if(status == "full") {
		image_address += std::to_string(showing_step / 5 + 1);
		if(showing_step == 14)
			showing_step = 0;
		else
			showing_step++;
	}
	else
		image_address += status;

	image_address += ".png";

	win.draw_img(image_address, Rectangle(Point(x, y), 16 * scale, 16 * scale), Rectangle(Point(0, 0), 16, 16));

}