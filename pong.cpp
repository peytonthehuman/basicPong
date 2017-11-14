#include "./pong_field.h"

void paintTex(triple* surf, int x, int y, int w, int h, fb_driver* activeFB) {
	if(activeFB == nullptr) {
		return;
	}
	
	for(int ry = 0; ry < h; ry++) {
		for(int rx = 0; rx < w; rx++) {
			activeFB->setPixel(surf[ry * w + rx], x + rx, y + ry);
		}
	}
	
	return;
}

void draw(fb_driver& fb, field& game, int fps) {
	// put setup code here
	struct timespec start, end;
	int timestep = ((double)1/(double)fps) * 1e+6;

	clock_gettime(CLOCK_MONOTONIC_RAW , &start);
	fb.clearToBG(false);

	//put drawing code in here
	game.drawField();
	//end drawing code

	clock_gettime(CLOCK_MONOTONIC_RAW , &end);
	int timedif = (end.tv_nsec - start.tv_nsec)/1000;
	int wait = timestep - timedif;
	usleep(wait < 0 ? 0 : wait > timestep ? 0 : wait);
	fb.swapBuffer();
	return;
}

void AI(fb_driver& fb, field& game, unsigned int pid) {
	bool move;
	bool dir;
	if(pid == 0 ? game.getPuckDX() < 0 : game.getPuckDX() > 0) {
		move = true;
	} else {
		move = rand() % 3 == 0;
	}
	
	if(game.getPuckY() < (game.getPaddleY(pid) + game.getPaddleH(pid)/2)) {
		dir = true;
	} else if(game.getPuckY() > (game.getPaddleY(pid) - game.getPaddleH(pid)/2)) {
		dir = false;
	}
	
	if(move) {
		game.nudgePaddle(!dir, pid);
	}
	
	return;
}

int main() {
	system("setterm --cursor off");

	srand(time(NULL));
	fb_driver fb(true, false);
	fb.init();
	
	triple* pallete = new triple[2];
	pallete[0].x = 0;
	pallete[0].y = 0;
	pallete[0].z = 0;

	pallete[1].x = 255;
	pallete[1].y = 255;
	pallete[1].z = 255;
	
	font mainFont;
	field game(&fb);
	game.setPuckStartSpeed(4);
	game.setActiveFont(&mainFont);
	game.setMaxScore(3);
	game.setPallete(pallete);
	
	int i = 0;
	bool aboveMax = false;
	int winner = -1;
	while(!aboveMax) {
		bool tick = false;
		if(i % 2 == 0) {
			tick = game.tickPhysics();
		}
		i++;
		if(i % 1000 == 0) {
			int newspeed = game.getPuckDX() >= 0 ? 1 : -1;
			game.setPuckDX(game.getPuckDX() + newspeed);
		}
		for(int j = 0; j < game.getNumPlayers(); j++) {
			if(i % 2 == 0) {
				AI(fb, game, j);
			}
		}
		if(tick) {
			for(int i = 0; i < game.getNumPlayers(); i++) {
				aboveMax = aboveMax || game.getScore(i) >= game.getMaxScore();
				if(aboveMax) {
					winner = i;
					break;
				}
			}
		}
		draw(fb, game, 60);
	}
	
	textBox victory;
	int cols = 10;
	int rows = 2;
	victory.init(cols, rows);
	victory.setActiveFont(&mainFont);
	victory.setBoxW(fb.getScreenX()/2);
	victory.setBoxH(fb.getScreenY()/3);
	victory.setBoxX(fb.getScreenX()/2 - victory.getBoxW()/2);
	victory.setBoxY(fb.getScreenY()/2 - victory.getBoxH()/2);
	victory.setTextMarginVertical(fb.getScreenX()/70);
	victory.setTextMarginHorizontal(fb.getScreenY()/70);
	victory.setFGColor(pallete[0]);
	victory.setBGColor(pallete[1]);
	char* content = new char[cols * rows] {'P','L','A','Y','E','R',' ','E','R','R',' ',' ',' ','W','I','N','S',' ',' ',' '};
	
	switch(winner) {
		case 1:
			content[7] = 'O';
			content[8] = 'N';
			content[9] = 'E';
			break;
		case 0:
			content[7] = 'T';
			content[8] = 'W';
			content[9] = '0';
			break;
		default:
			break;
	}
	
	victory.setContentArray(content);
	victory.renderTextBox();
	
	paintTex(victory.getCache(), victory.getBoxX(), victory.getBoxY(), victory.getBoxW(), victory.getBoxH(), &fb);
	
	fb.swapBuffer();
	
	sleep(5);
	

	system("setterm --cursor on");
	return 0;
}
