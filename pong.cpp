#include <time.h>
#include <cstdlib>
#include <ctime>
#include "./fb_main.h"
#include "./pong_game_elems.h"
#include "./pong_font.h"

void paintRec(triple color, int x, int y, int w, int h, fb_driver& fb) {
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			fb.setPixel(color, x + j, y + i);
		}
	}
}

void paintTex(triple* surface, int x, int y, int w, int h, fb_driver& fb) {
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			fb.setPixel(surface[(i * w) + j], x + j, y + i);
		}
	}
}

void draw(fb_driver& fb, textBox* scores, paddle* players, triple* colors, const int NUMPLAYERS) {
// put setup code here
	unsigned int fps = 30;
	unsigned int secs = 10;

	fb.clearToBG(true);

	struct timespec start, end;
	int timestep = ((double)1/(double)fps) * 1e+6;

	for(int i = 0; i < (fps * secs); i++) {
		clock_gettime(CLOCK_MONOTONIC, &start);
		fb.clearToBG(false);

		//put drawing code in here
		for(int i = 0; i < NUMPLAYERS; i++) {
			scores[i].renderTextBox();
			paintTex(scores[i].getCache(), scores[i].getBoxX(), scores[i].getBoxY(), scores[i].getBoxW(), scores[i].getBoxH(), fb);
			paintRec(players[i].getColor(), players[i].getPaddleX(), players[i].getPaddleY(), players[i].getPaddleW(), players[i].getPaddleH(), fb);
		}
		
		fb.swapBuffer();
		//end drawing code

		clock_gettime(CLOCK_MONOTONIC, &end);
		if(timestep > (end.tv_nsec - start.tv_nsec)/1000) {
			usleep(timestep - (end.tv_nsec - start.tv_nsec)/1000);
		} else if(timestep <= (end.tv_nsec - start.tv_nsec)/1000) {
			i += (double)((end.tv_nsec - start.tv_nsec)/1000 - timestep) / (double)timestep;
		}
	}
	fb.clearToBG(true);
	return;
}

int main() {
	system("setterm --cursor off");

	fb_driver fb(false, false);
	fb.init();
	
	const int NUMPLAYERS = 2;
	font mainFont;
	textBox* scores = new textBox[NUMPLAYERS];
	paddle* players = new paddle[NUMPLAYERS];
	triple* colors = new triple[2];
	
	colors[0].x = 0;
	colors[0].y = 0;
	colors[0].z = 0;
	
	colors[1].x = 255;
	colors[1].y = 255;
	colors[1].z = 255;
	
	for(int i = 0; i < NUMPLAYERS; i++) {
		scores[i].init(3, 1);
		scores[i].setActiveFont(&mainFont);
		scores[i].setBoxW(fb.getScreenX() / 6);
		scores[i].setBoxH(fb.getScreenY() / 10);
		scores[i].setTextMarginHorizontal(6);
		scores[i].setTextMarginVertical(6);
		scores[i].setBoxY(fb.getScreenY()/20);
		scores[i].setFGColor(colors[1]);
		scores[i].setBGColor(colors[0]);
	}
	
	scores[0].setBoxX(fb.getScreenX()/2 + scores[0].getBoxW() * 2 - scores[0].getBoxW());
	scores[1].setBoxX(fb.getScreenX()/2 - scores[1].getBoxW() * 2);
	
	for(int i = 0; i < NUMPLAYERS; i++) {
		players[i].setID('0' + i);
		players[i].setPaddleW(fb.getScreenX()/80);
		players[i].setPaddleH(fb.getScreenY()/7);
		players[i].setPaddleY(fb.getScreenY()/2 - players[i].getPaddleH()/2);
		players[i].setColor(colors[1]);
	}
	
	players[0].setPaddleX(fb.getScreenX()/2 - (fb.getScreenX()/2 - fb.getScreenX()/10) - players[0].getPaddleW());
	players[1].setPaddleX(fb.getScreenX()/2 + (fb.getScreenX()/2 - fb.getScreenX()/10));

	draw(fb, scores, players, colors, NUMPLAYERS);
	
	delete [] scores;
	delete [] players;
	delete [] colors;

	system("setterm --cursor on");
	return 0;
}
