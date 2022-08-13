#include <iostream>
#include <fstream>
#include "src/rsdl.hpp"
#include "Camera.hpp"
#include "Mario.hpp"
#include "Clay.hpp"
#include "Hole.hpp"
#include "Brick.hpp"
#include "Block.hpp"
#include "Question.hpp"
#include "Pipe.hpp"
#include "Flag.hpp"
#include "Goomba.hpp"
#include "Koopa.hpp"
#include "Coin.hpp"
#include "Mushroom.hpp"


const float TIME_DELAY = 40;
const float MARIO_VY0 = -60 / TIME_DELAY;
const float A = 8 / (TIME_DELAY * TIME_DELAY);


using namespace std;


vector<string> read_map() {

	string line;
	vector<string> map;

	ifstream file ("assets/maps/1/1.txt");

	while(getline(file, line)) map.push_back(line);

	file.close();

	return map;

}


int calc_clay_number(vector<string> map) {

	int calc_clay_number = 0;

	for(int i = map.size() - 1; i >= 0; i--) {
		if(map[i][0] == '#') calc_clay_number++;
		else break;
	}

	return calc_clay_number;

}


void game_lose(Window & win, Mario & mario, float scale, bool & game_lose_flag) {

	win.play_sound_effect("assets/sounds/sound_effects/mario-death.wav");
	mario.dec_lives();
	mario.set_status("dead");

	for(int i = 0; i <= 14; i++) {
		mario.add_y(-10);
		mario.draw(win, scale);
		win.update_screen();
		delay(TIME_DELAY);
	}

	game_lose_flag = true;

}


void game_win(Window & win) {

	win.play_sound_effect("assets/sounds/sound_effects/level-clear.wav");
	win.draw_img("assets/images/gamewin.png", Rectangle(Point(0, 0), 1000, 720), Rectangle(Point(0, 0), 1000, 720));
	win.update_screen();
	delay(6000);

}


void game_over(Window & win) {

	win.play_sound_effect("assets/sounds/sound_effects/gameover.wav");
	win.draw_img("assets/images/gameover.png", Rectangle(Point(0, 0), 1000, 720), Rectangle(Point(0, 0), 1000, 720));
	win.update_screen();
	delay(4000);

}


void draw_background(Window & win, Camera cam, int clay_number, float scale) {

	win.draw_img("assets/background/background_image.png", Rectangle(Point(0, 0), 1000, 720 - clay_number * 16 * scale), Rectangle(Point(cam.get_x(), clay_number * 16 * scale), 1000, 720 - clay_number * 16 * scale));

}


void find_init_enemies_objects(vector<string> map, int clay_number, float scale, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list) {

	for(int i = 0; i < map.size(); i++) {

		for(int j = 0; j < 1000 / (16 * scale) + 2; j++) {

			if(map[i][j] == '#')
				clay_list.push_back(Clay(j * 16 * scale, i * 16 * scale));

			else if(map[i][j] == '.' && (map.size() - clay_number) <= i)
				hole_list.push_back(Hole(j * 16 * scale, i * 16 * scale));

			else if(map[i][j] == 'b')
				brick_list.push_back(Brick(j * 16 * scale, i * 16 * scale));

			else if(map[i][j] == '@')
				block_list.push_back(Block(j * 16 * scale, i * 16 * scale));

			else if(map[i][j] == '?' || map[i][j] == 'm' || map[i][j] == 'h')
				question_list.push_back(Question(j * 16 * scale, i * 16 * scale, map[i][j]));

			else if(map[i][j] == 'l')
				goomba_list.push_back(Goomba(j * 16 * scale, i * 16 * scale));

			else if(map[i][j] == 'k')
				koopa_list.push_back(Koopa(j * 16 * scale, i * 16 * scale - 8 * scale));

		}

	}

	int ii = map.size() - clay_number - 1, pipe_length, k;

	for(int j = 0; j < 1000 / (16 * scale) + 2; j++) {

		if(map[ii][j] == '|' && map[ii][j + 1] == '|') {
			pipe_length = 1;
			for(k = ii - 1; k >= 0; k--) {
				if(map[k][j] == '|' && map[k][j + 1] == '|')
					pipe_length++;
				else
					break;
			}
			pipe_list.push_back(Pipe(j * 16 * scale, (k + 1) * 16 * scale, pipe_length));
		}

	}

	int flag_length = 1;
	bool break_flag = false;

	for(int i = ii; i >= 0; i--) {

		for(int j = 0; j < 1000 / (16 * scale) + 2; j++) {

			if(map[i][j] == 'f') {
				for(k = i - 1; k >= 0; k--) {
					if(map[k][j] == 'f')
						flag_length++;
					else
						break;
				}
				flag_list.push_back(Flag(j * 16 * scale, (k + 1) * 16 * scale, flag_length));
				break_flag = true;
				break;
			}
			
		}

		if(break_flag)
			break;

	}

}


void move_enemies_objects_by_selves(vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	for(int i = 0; i < goomba_list.size(); i++)
		if(goomba_list[i].get_status() != "dead")
			goomba_list[i].go_by_self(TIME_DELAY);

	for(int i = 0; i < koopa_list.size(); i++)
		if(koopa_list[i].get_status() == "walking" || (koopa_list[i].get_status() == "dead" && koopa_list[i].get_dead_step() == "dynamic"))
			koopa_list[i].go_by_self(TIME_DELAY);

	for(int i = 0; i < coin_list.size(); i++)
		coin_list[i].go_by_self(TIME_DELAY);

	for(int i = 0; i < mushroom_list.size(); i++)
		mushroom_list[i].go_by_self(TIME_DELAY);
	
}


void move_enemies_objects_by_camera(Camera cam, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	for(int i = 0; i < clay_list.size(); i++)
		clay_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < hole_list.size(); i++)
		hole_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < brick_list.size(); i++)
		brick_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < block_list.size(); i++)
		block_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < question_list.size(); i++)
		question_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < pipe_list.size(); i++)
		pipe_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < flag_list.size(); i++)
		flag_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < goomba_list.size(); i++)
		goomba_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < koopa_list.size(); i++)
		koopa_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < coin_list.size(); i++)
		coin_list[i].go_by_camera(cam, TIME_DELAY);

	for(int i = 0; i < mushroom_list.size(); i++)
		mushroom_list[i].go_by_camera(cam, TIME_DELAY);

}


void find_new_enemies_objects(Camera cam, vector<string> map, int clay_number, float scale, int & old_shift, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list) {

	int shift = cam.get_x() / (16 * scale), j = 1000 / (16 * scale) + 1;

	if(shift == old_shift + 1) {

		old_shift++;

		for(int i = 0; i < map.size(); i++) {

			if(map[i][j + shift] == '#')
				clay_list.push_back(Clay(j * 16 * scale, i * 16 * scale));

			else if(map[i][j + shift] == '.' && (map.size() - clay_number) <= i)
				hole_list.push_back(Hole(j * 16 * scale, i * 16 * scale));

			else if(map[i][j + shift] == 'b')
				brick_list.push_back(Brick(j * 16 * scale, i * 16 * scale));

			else if(map[i][j + shift] == '@')
				block_list.push_back(Block(j * 16 * scale, i * 16 * scale));

			else if(map[i][j + shift] == '?' || map[i][j + shift] == 'm' || map[i][j + shift] == 'h')
				question_list.push_back(Question(j * 16 * scale, i * 16 * scale, map[i][j + shift]));

			else if(map[i][j + shift] == 'l')
				goomba_list.push_back(Goomba(j * 16 * scale, i * 16 * scale));

			else if(map[i][j + shift] == 'k')
				koopa_list.push_back(Koopa(j * 16 * scale, i * 16 * scale - 8 * scale));

		}

		int ii = map.size() - clay_number - 1, pipe_length = 1, k;

		if(map[ii][j + shift - 1] == '|' && map[ii][j + shift] == '|') {
			for(k = ii - 1; k >= 0; k--) {
				if(map[k][j + shift - 1] == '|' && map[k][j + shift] == '|')
					pipe_length++;
				else
					break;
			}
			pipe_list.push_back(Pipe((j - 1) * 16 * scale, (k + 1) * 16 * scale, pipe_length));
		}

		int flag_length = 1;
		bool break_flag = false;

		for(int i = ii; i >= 0; i--) {

			if(map[i][j + shift] == 'f') {
				for(k = i - 1; k >= 0; k--) {
					if(map[k][j + shift] == 'f')
						flag_length++;
					else
						break;
				}
				flag_list.push_back(Flag(j * 16 * scale, (k + 1) * 16 * scale, flag_length));
				break;
			}

		}

	}

}


void draw_enemies_objects(Window & win, float scale, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	for(int i = 0; i < clay_list.size(); i++)
		clay_list[i].draw(win, scale);

	for(int i = 0; i < hole_list.size(); i++)
		hole_list[i].draw(win, scale);

	for(int i = 0; i < brick_list.size(); i++)
		brick_list[i].draw(win, scale);

	for(int i = 0; i < block_list.size(); i++)
		block_list[i].draw(win, scale);

	for(int i = 0; i < question_list.size(); i++)
		question_list[i].draw(win, scale);

	for(int i = 0; i < pipe_list.size(); i++)
		pipe_list[i].draw(win, scale);

	for(int i = 0; i < flag_list.size(); i++)
		flag_list[i].draw(win, scale);

	for(int i = 0; i < goomba_list.size(); i++)
		goomba_list[i].draw(win, scale);

	for(int i = 0; i < koopa_list.size(); i++)
		koopa_list[i].draw(win, scale);

	for(int i = 0; i < coin_list.size(); i++)
		coin_list[i].draw(win, scale);

	for(int i = 0; i < mushroom_list.size(); i++)
		mushroom_list[i].draw(win, scale);

}


void remove_out_of_camera_enemies_objects(float scale, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	for(int i = 0; i < clay_list.size(); i++) {
		if(clay_list[i].get_x() + 16 * scale < 0) {
			clay_list.erase(clay_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < hole_list.size(); i++) {
		if(hole_list[i].get_x() + 16 * scale < 0) {
			hole_list.erase(hole_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < brick_list.size(); i++) {
		if(brick_list[i].get_x() + 16 * scale < 0) {
			brick_list.erase(brick_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < block_list.size(); i++) {
		if(block_list[i].get_x() + 16 * scale < 0) {
			block_list.erase(block_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < question_list.size(); i++) {
		if(question_list[i].get_x() + 16 * scale < 0) {
			question_list.erase(question_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < pipe_list.size(); i++) {
		if(pipe_list[i].get_x() + 32 * scale < 0) {
			pipe_list.erase(pipe_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < flag_list.size(); i++) {
		if(flag_list[i].get_x() + 16 * scale < 0) {
			flag_list.erase(flag_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_x() + 16 * scale < 0) {
			goomba_list.erase(goomba_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < koopa_list.size(); i++) {
		if(koopa_list[i].get_x() + 16 * scale < 0) {
			koopa_list.erase(koopa_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < coin_list.size(); i++) {
		if(coin_list[i].get_x() + 16 * scale < 0) {
			coin_list.erase(coin_list.begin() + i);
			i--;
		}
	}

	for(int i = 0; i < mushroom_list.size(); i++) {
		if(mushroom_list[i].get_x() + 16 * scale < 0) {
			mushroom_list.erase(mushroom_list.begin() + i);
			i--;
		}
	}

}


void remove_dead_enemies_objects(vector<Goomba> & goomba_list, vector<Coin> & coin_list) {

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_status() == "dead") {
			if(goomba_list[i].get_dead_time() == 0) {
				goomba_list.erase(goomba_list.begin() + i);
				i--;
			}
			else
				goomba_list[i].dec_dead_time();
		}
	}

	for(int i = 0; i < coin_list.size(); i++) {
		if(coin_list[i].get_rising_step() == 0) {
			coin_list.erase(coin_list.begin() + i);
			i--;
		}
		else
			coin_list[i].dec_rising_step();
	}

}


void check_right_side_of_mario(Window & win, Mario & mario, Camera cam, float scale, bool & it_can_go_flag, bool & it_lost_flag, bool & it_won_flag, vector<Clay> & clay_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Mushroom> & mushroom_list) {

	it_can_go_flag = true;
	it_lost_flag = false;
	it_won_flag = false;
	int new_x_right = mario.get_x() + 16 * scale + cam.get_vx() * TIME_DELAY;
	
	for(int i = 0; i < clay_list.size(); i++) {
		if(clay_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < clay_list[i].get_y() + 16 * scale) {
			if(mario.get_x() + 16 * scale <= clay_list[i].get_x() && clay_list[i].get_x() < new_x_right)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < brick_list.size(); i++) {
		if(brick_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < brick_list[i].get_y() + 16 * scale) {
			if(mario.get_x() + 16 * scale <= brick_list[i].get_x() && brick_list[i].get_x() < new_x_right)
				it_can_go_flag = false;
		}
	}
	
	for(int i = 0; i < block_list.size(); i++) {
		if(block_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < block_list[i].get_y() + 16 * scale) {
			if(mario.get_x() + 16 * scale <= block_list[i].get_x() && block_list[i].get_x() < new_x_right)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < question_list.size(); i++) {
		if(question_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < question_list[i].get_y() + 16 * scale) {
			if(mario.get_x() + 16 * scale <= question_list[i].get_x() && question_list[i].get_x() < new_x_right)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < pipe_list.size(); i++) {
		if(pipe_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < pipe_list[i].get_y() + pipe_list[i].get_length() * 16 * scale) {
			if(mario.get_x() + 16 * scale <= pipe_list[i].get_x() && pipe_list[i].get_x() < new_x_right)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < flag_list.size(); i++) {
		if(flag_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < flag_list[i].get_y() + flag_list[i].get_length() * 16 * scale) {
			if(mario.get_x() + 16 * scale <= flag_list[i].get_x() && flag_list[i].get_x() < new_x_right)
				it_won_flag = true;
		}
	}

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < goomba_list[i].get_y() + 16 * scale) {
			if(mario.get_x() + 16 * scale <= goomba_list[i].get_x() && goomba_list[i].get_x() < new_x_right) {
				if(goomba_list[i].get_status() == "walking") {
					it_lost_flag = true;
					it_can_go_flag = false;
				}
			}
		}
	}

	for(int i = 0; i < koopa_list.size(); i++) {
		if(koopa_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < koopa_list[i].get_y() + 24 * scale) {
			if(mario.get_x() + 16 * scale <= koopa_list[i].get_x() && koopa_list[i].get_x() < new_x_right) {
				it_lost_flag = true;
				it_can_go_flag = false;
			}
		}
	}

	for(int i = 0; i < mushroom_list.size(); i++) {
		if(mushroom_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < mushroom_list[i].get_y() + 24 * scale) {
			if(mario.get_x() + 16 * scale <= mushroom_list[i].get_x() && mushroom_list[i].get_x() < new_x_right) {
				if(mushroom_list[i].get_type() == "health")
					mario.inc_lives();
				mushroom_list.erase(mushroom_list.begin() + i);
				win.play_sound_effect("assets/sounds/sound_effects/powerup-appears.wav");
				i--;
			}
		}
	}

}


void check_left_side_of_mario(Window & win, Mario & mario, Camera cam, float scale, bool & it_can_go_flag, bool & it_lost_flag, vector<Clay> & clay_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Mushroom> & mushroom_list) {

	it_can_go_flag = true;
	it_lost_flag = false;
	int new_x_left = mario.get_x() - cam.get_vx() * TIME_DELAY;
	
	for(int i = 0; i < clay_list.size(); i++) {
		if(clay_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < clay_list[i].get_y() + 16 * scale) {
			if(clay_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < clay_list[i].get_x() + 16 * scale)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < brick_list.size(); i++) {
		if(brick_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < brick_list[i].get_y() + 16 * scale) {
			if(brick_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < brick_list[i].get_x() + 16 * scale)
				it_can_go_flag = false;
		}
	}
	
	for(int i = 0; i < block_list.size(); i++) {
		if(block_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < block_list[i].get_y() + 16 * scale) {
			if(block_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < block_list[i].get_x() + 16 * scale)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < question_list.size(); i++) {
		if(question_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < question_list[i].get_y() + 16 * scale) {
			if(question_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < question_list[i].get_x() + 16 * scale)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < pipe_list.size(); i++) {
		if(pipe_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < pipe_list[i].get_y() + pipe_list[i].get_length() * 16 * scale) {
			if(pipe_list[i].get_x() + 2 * 16 * scale <= mario.get_x() && new_x_left < pipe_list[i].get_x() + 2 * 16 * scale)
				it_can_go_flag = false;
		}
	}

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < goomba_list[i].get_y() + 16 * scale) {
			if(goomba_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < goomba_list[i].get_x() + 16 * scale) {
				if(goomba_list[i].get_status() == "walking") {
					it_lost_flag = true;
					it_can_go_flag = false;
				}
			}
		}
	}

	for(int i = 0; i < koopa_list.size(); i++) {
		if(koopa_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < koopa_list[i].get_y() + 24 * scale) {
			if(koopa_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < koopa_list[i].get_x() + 16 * scale) {
				it_lost_flag = true;
				it_can_go_flag = false;
			}
		}
	}

	for(int i = 0; i < mushroom_list.size(); i++) {
		if(mushroom_list[i].get_y() - 16 * scale < mario.get_y() && mario.get_y() < mushroom_list[i].get_y() + 24 * scale) {
			if(mushroom_list[i].get_x() + 16 * scale <= mario.get_x() && new_x_left < mushroom_list[i].get_x() + 16 * scale) {
				if(mushroom_list[i].get_type() == "health")
					mario.inc_lives();
				mushroom_list.erase(mushroom_list.begin() + i);
				win.play_sound_effect("assets/sounds/sound_effects/powerup-appears.wav");
				i--;
			}
		}
	}

}


int check_up_side_of_mario(Window & win, Mario & mario, int clay_number, float scale, float a, bool & it_can_go_flag, bool & it_lost_flag, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	it_can_go_flag = true;
	it_lost_flag = false;
	int y_cross = 0;
	int new_y_up = mario.get_y() + 0.5 * a * (TIME_DELAY * TIME_DELAY) + mario.get_vy0() * TIME_DELAY;
	
	for(int i = 0; i < brick_list.size(); i++) {
		if(brick_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < brick_list[i].get_x() + 16 * scale) {
			if(brick_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < brick_list[i].get_y() + 16 * scale) {
				it_can_go_flag = false;
				y_cross = brick_list[i].get_y() + 16 * scale;
			}
		}
	}
	
	for(int i = 0; i < block_list.size(); i++) {
		if(block_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < block_list[i].get_x() + 16 * scale) {
			if(block_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < block_list[i].get_y() + 16 * scale) {
				it_can_go_flag = false;
				y_cross = block_list[i].get_y() + 16 * scale;
			}
		}
	}

	for(int i = 0; i < question_list.size(); i++) {
		if(question_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < question_list[i].get_x() + 16 * scale) {
			if(question_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < question_list[i].get_y() + 16 * scale) {
				if(question_list[i].get_status() == "full") {
					if(question_list[i].get_content_type() == '?') {
						coin_list.push_back(Coin(question_list[i].get_x(), question_list[i].get_y()));
						win.play_sound_effect("assets/sounds/sound_effects/coin.wav");
						mario.inc_coins();
					}
					else if(question_list[i].get_content_type() == 'm') {
						mushroom_list.push_back(Mushroom(question_list[i].get_x(), question_list[i].get_y() - 16 * scale, "red"));
						win.play_sound_effect("assets/sounds/sound_effects/powerup.wav");
					}
					else if(question_list[i].get_content_type() == 'h') {
						mushroom_list.push_back(Mushroom(question_list[i].get_x(), question_list[i].get_y() - 16 * scale, "health"));
						win.play_sound_effect("assets/sounds/sound_effects/powerup.wav");
					}
					question_list[i].set_status("empty");
				}
				it_can_go_flag = false;
				y_cross = question_list[i].get_y() + 16 * scale;
			}
		}
	}

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < goomba_list[i].get_x() + 16 * scale) {
			if(goomba_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < goomba_list[i].get_y() + 16 * scale) {
				if(goomba_list[i].get_status() == "walking")
					it_lost_flag = true;
			}
		}
	}

	for(int i = 0; i < koopa_list.size(); i++) {
		if(koopa_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < koopa_list[i].get_x() + 16 * scale) {
			if(koopa_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < koopa_list[i].get_y() + 16 * scale) {
				it_lost_flag = true;
			}
		}
	}

	for(int i = 0; i < mushroom_list.size(); i++) {
		if(mushroom_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < mushroom_list[i].get_x() + 16 * scale) {
			if(mushroom_list[i].get_y() + 16 * scale <= mario.get_y() && new_y_up < mushroom_list[i].get_y() + 16 * scale) {
				if(mushroom_list[i].get_type() == "health")
					mario.inc_lives();
				y_cross = mushroom_list[i].get_y();
				mushroom_list.erase(mushroom_list.begin() + i);
				win.play_sound_effect("assets/sounds/sound_effects/powerup-appears.wav");
				i--;
			}
		}
	}

	return y_cross;

}


int check_down_side_of_mario(Window & win, Mario & mario, int clay_number, float scale, float a, bool & it_can_go_flag, bool & it_lost_flag, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Mushroom> & mushroom_list) {

	it_can_go_flag = true;
	it_lost_flag = false;
	int y_cross = 0;
	int new_y_down = mario.get_y() + 16 * scale + 0.5 * a * (TIME_DELAY * TIME_DELAY) + mario.get_vy0() * TIME_DELAY;
	
	for(int i = 0; i < clay_list.size(); i++) {
		if(clay_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < clay_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= clay_list[i].get_y() && clay_list[i].get_y() < new_y_down) {
				it_can_go_flag = false;
				y_cross = clay_list[i].get_y() - 16 * scale;
			}
		}
	}

	for(int i = 0; i < hole_list.size(); i++) {
		if(hole_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < hole_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= hole_list[i].get_y() && hole_list[i].get_y() < new_y_down)
				it_lost_flag = true;
		}
	}

	for(int i = 0; i < brick_list.size(); i++) {
		if(brick_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < brick_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= brick_list[i].get_y() && brick_list[i].get_y() < new_y_down) {
				it_can_go_flag = false;
				y_cross = brick_list[i].get_y() - 16 * scale;
			}
		}
	}
	
	for(int i = 0; i < block_list.size(); i++) {
		if(block_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < block_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= block_list[i].get_y() && block_list[i].get_y() < new_y_down) {
				it_can_go_flag = false;
				y_cross = block_list[i].get_y() - 16 * scale;
			}
		}
	}

	for(int i = 0; i < question_list.size(); i++) {
		if(question_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < question_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= question_list[i].get_y() && question_list[i].get_y() < new_y_down) {
				it_can_go_flag = false;
				y_cross = question_list[i].get_y() - 16 * scale;
			}
		}
	}

	for(int i = 0; i < pipe_list.size(); i++) {
		if(pipe_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < pipe_list[i].get_x() + 2 * 16 * scale) {
			if(mario.get_y() + 16 * scale <= pipe_list[i].get_y() && pipe_list[i].get_y() < new_y_down) {
				it_can_go_flag = false;
				y_cross = pipe_list[i].get_y() - 16 * scale;
			}
		}
	}

	for(int i = 0; i < goomba_list.size(); i++) {
		if(goomba_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < goomba_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= goomba_list[i].get_y() && goomba_list[i].get_y() < new_y_down) {
				if(goomba_list[i].get_status() == "walking") {
					goomba_list[i].set_status("dead");
					win.play_sound_effect("assets/sounds/sound_effects/enemy-stomp.wav");
					y_cross = goomba_list[i].get_y() - 16 * scale;
				}
			}
		}
	}

	for(int i = 0; i < koopa_list.size(); i++) {
		if(koopa_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < koopa_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= koopa_list[i].get_y() && koopa_list[i].get_y() < new_y_down) {
				if(koopa_list[i].get_status() != "dead")
					koopa_list[i].set_status("dead");
				else {
					if(koopa_list[i].get_dead_step() == "static")
						koopa_list[i].set_dead_step("dynamic");
					else
						koopa_list[i].set_dead_step("static");
				}
				win.play_sound_effect("assets/sounds/sound_effects/enemy-stomp.wav");
				y_cross = koopa_list[i].get_y() - 8 * scale;
			}
		}
	}

	for(int i = 0; i < mushroom_list.size(); i++) {
		if(mushroom_list[i].get_x() - 16 * scale < mario.get_x() && mario.get_x() < mushroom_list[i].get_x() + 16 * scale) {
			if(mario.get_y() + 16 * scale <= mushroom_list[i].get_y() && mushroom_list[i].get_y() < new_y_down) {
				if(mushroom_list[i].get_type() == "health")
					mario.inc_lives();
				y_cross = mushroom_list[i].get_y();
				mushroom_list.erase(mushroom_list.begin() + i);
				win.play_sound_effect("assets/sounds/sound_effects/powerup-appears.wav");
				i--;
			}
		}
	}

	return y_cross;

}


void handling_event(Event event, Window & win, Mario & mario, Camera & cam, float scale, bool & quit_flag, bool & game_lose_flag, bool & game_win_flag, vector<Clay> & clay_list, vector<Hole> & hole_list, vector<Brick> & brick_list, vector<Block> & block_list, vector<Question> & question_list, vector<Pipe> & pipe_list, vector<Flag> & flag_list, vector<Goomba> & goomba_list, vector<Koopa> & koopa_list, vector<Coin> & coin_list, vector<Mushroom> & mushroom_list) {

	bool it_can_go_flag, it_lost_flag;

	if(event.get_type() == Event::KEY_PRESS) {

		if(event.get_pressed_key() == 'd') {
			check_right_side_of_mario(win, mario, cam, scale, it_can_go_flag, it_lost_flag, game_win_flag, clay_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list, mushroom_list);
			if(game_win_flag)
				return;
			if(it_lost_flag) {
				game_lose(win, mario, scale, game_lose_flag);
				return;
			}
			if(it_can_go_flag) {
				mario.go_right(cam, TIME_DELAY);
				if(500 <= mario.get_x())
					move_enemies_objects_by_camera(cam, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list, coin_list, mushroom_list);
			}
		}

		if(event.get_pressed_key() == 'a') {
			check_left_side_of_mario(win, mario, cam, scale, it_can_go_flag, it_lost_flag, clay_list, brick_list, block_list, question_list, pipe_list, goomba_list, koopa_list, mushroom_list);
			if(it_lost_flag) {
				game_lose(win, mario, scale, game_lose_flag);
				return;
			}
			if(it_can_go_flag)
				mario.go_left(TIME_DELAY);
		}

		if(mario.get_status() != "jumping" && event.get_pressed_key() == 'w') {
			mario.set_vy0(MARIO_VY0);
			mario.set_status("jumping");
			win.play_sound_effect("assets/sounds/sound_effects/jump-small.wav");
		}

		if(event.get_pressed_key() == 'q') {
			quit_flag = true;
			return;
		}

	}

	if(event.get_type() == Event::KEY_RELEASE) {
		if(mario.get_status() != "jumping")
			mario.set_status("standing");
	}

}


void game_loop(Window & win, Mario & mario, Camera & cam, vector<string> map, int clay_number, float scale, bool & quit_flag, bool & game_win_flag) {

	Event event;
	int old_shift = 0, y_cross;
	bool game_lose_flag = false, it_can_go_flag, it_lost_flag;
	vector<Clay> clay_list;
	vector<Hole> hole_list;
	vector<Brick> brick_list;
	vector<Block> block_list;
	vector<Question> question_list;
	vector<Pipe> pipe_list;
	vector<Flag> flag_list;
	vector<Goomba> goomba_list;
	vector<Koopa> koopa_list;
	vector<Coin> coin_list;
	vector<Mushroom> mushroom_list;

	win.play_music("assets/sounds/Super Mario Bros. theme music.mp3");
	
	find_init_enemies_objects(map, clay_number, scale, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list);
	
	while(true) {

		move_enemies_objects_by_selves(goomba_list, koopa_list, coin_list, mushroom_list);

		while(win.has_pending_event()) {

			event = win.poll_for_event();

			handling_event(event, win, mario, cam, scale, quit_flag, game_lose_flag, game_win_flag, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list, coin_list, mushroom_list);

		}

		if(quit_flag || game_lose_flag || game_win_flag) {
			win.stop_music();
			return;
		}

		draw_background(win, cam, clay_number, scale);
		remove_out_of_camera_enemies_objects(scale, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list, coin_list, mushroom_list);
		remove_dead_enemies_objects(goomba_list, coin_list);
		find_new_enemies_objects(cam, map, clay_number, scale, old_shift, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list);
		draw_enemies_objects(win, scale, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, flag_list, goomba_list, koopa_list, coin_list, mushroom_list);

		if(mario.get_vy0() <= - 0.5 * A)
			y_cross = check_up_side_of_mario(win, mario, clay_number, scale, A, it_can_go_flag, it_lost_flag, brick_list, block_list, question_list, goomba_list, koopa_list, coin_list, mushroom_list);
		else
			y_cross = check_down_side_of_mario(win, mario, clay_number, scale, A, it_can_go_flag, it_lost_flag, clay_list, hole_list, brick_list, block_list, question_list, pipe_list, goomba_list, koopa_list, mushroom_list);
		if(it_lost_flag) {
			game_lose(win, mario, scale, game_lose_flag);
			win.stop_music();
			break;
		}

		mario.continue_jumping(clay_number, scale, TIME_DELAY, A, y_cross, it_can_go_flag);
		mario.draw(win, scale);
		win.update_screen();
		delay(TIME_DELAY);

	}

}


int main() {

	float scale;
	int clay_number;
	vector<string> map;
	bool quit_flag = false, game_win_flag = false;

	map = read_map();
	scale = 720.0 / map.size() / 16;
	clay_number = calc_clay_number(map);

	Camera cam(0);
	Window win(1000, 720, "Super Mario Bros");
	Mario mario(720 - 16 * scale - clay_number * 16 * scale, 3, 0);

	while(mario.get_lives() > 0) {
		
		game_loop(win, mario, cam, map, clay_number, scale, quit_flag, game_win_flag);

		if(quit_flag || game_win_flag)
			break;

		cam.reset(0);
		mario.reset(720 - 16 * scale - clay_number * 16 * scale, mario.get_lives(), mario.get_coins());

	}

	if(game_win_flag == true)
		game_win(win);
	else if(quit_flag == false)
		game_over(win);

	return 0;

}