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

void draw(fb_driver& fb, textBox* scores, paddle* players, triple* colors, line& divide, rectangle& puck, const int NUMPLAYERS) {
	// put setup code here
	triple white;
	white.x = 255;
	white.y = 255;
	white.z = 255;
	
	int fps = 30;

	struct timespec start, end;
	int timestep = ((double)1/(double)fps) * 1e+6;

	clock_gettime(CLOCK_MONOTONIC_RAW , &start);
	fb.clearToBG(false);

	//put drawing code in here
	for(int i = 0; i < NUMPLAYERS; i++) {
		paintTex(scores[i].getCache(), scores[i].getBoxX(), scores[i].getBoxY(), scores[i].getBoxW(), scores[i].getBoxH(), fb);
		paintRec(players[i].getColor(), players[i].getPaddleX(), players[i].getPaddleY(), players[i].getPaddleW(), players[i].getPaddleH(), fb);
	}
	
	paintTex(divide.getCache(), divide.getLineX(), divide.getLineY(), divide.getLineW(), divide.getLineH(), fb);
	paintRec(white, puck.x, puck.y, puck.w, puck.h, fb);
	
	//fb.swapBuffer();
	//end drawing code

	clock_gettime(CLOCK_MONOTONIC_RAW , &end);
	int timedif = (end.tv_nsec - start.tv_nsec)/1000;
	int wait = timestep - timedif;
	usleep(wait < 0 ? 0 : wait > timestep ? 0 : wait);
	fb.swapBuffer();
	return;
}

void resetPuck(bool x_dir, rectangle& puck, int& puck_dx, int& puck_dy, fb_driver& fb) {
	int x_speed = 4;
	puck_dx = x_dir ? x_speed : -x_speed;
	puck_dy = 0;
	puck.w = fb.getScreenX()/50;
	puck.h = puck.w;
	puck.x = fb.getScreenX()/2 - puck.w/2;
	puck.y = fb.getScreenY()/2 - puck.h/2;
	return;
}

int main() {
	system("setterm --cursor off");

	srand(time(NULL));
	fb_driver fb(true, false);
	fb.init();
	
	const int NUMPLAYERS = 2;
	font mainFont;
	int* score = new int[NUMPLAYERS];
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
	
	scores[0].renderTextBox();
	scores[1].renderTextBox();
	
	// need a reset players function
	for(int i = 0; i < NUMPLAYERS; i++) {
		players[i].setID('0' + i);
		players[i].setPaddleW(fb.getScreenX()/80);
		players[i].setPaddleH(fb.getScreenY()/7);
		players[i].setPaddleY(fb.getScreenY()/2 - players[i].getPaddleH()/2);
		players[i].setColor(colors[1]);
	}
	
	players[0].setPaddleX(fb.getScreenX()/2 - (fb.getScreenX()/2 - fb.getScreenX()/10) - players[0].getPaddleW());
	players[1].setPaddleX(fb.getScreenX()/2 + (fb.getScreenX()/2 - fb.getScreenX()/10));
	
	line middle;
	middle.setLineW(2);
	middle.setLineH(fb.getScreenY() - scores[0].getBoxY() - scores[0].getBoxH() - fb.getScreenY()/20);
	middle.setLineX(fb.getScreenX()/2 - middle.getLineW()/2);
	middle.setLineY(scores[0].getBoxH() + scores[0].getBoxY());
	middle.setDashed(true);
	middle.setDashLength(fb.getScreenY()/10);
	middle.setDashMargin(fb.getScreenY()/15);
	middle.setFG_Color(colors[1]);
	middle.setBG_Color(colors[0]);
	middle.renderLine();
	
	rectangle puck;
	int puck_dx, puck_dy;
	resetPuck(true, puck, puck_dx, puck_dy, fb);
	
	while(score[0] < 1 || score[1] < 1) {
		puck.x += puck_dx;
		puck.y += puck_dy;
		if (puck.x + puck.w >= fb.getScreenX()) {
			score[1]++;
			scores[1].setCharacter('0' + score[1]%10, 2);
			scores[1].setCharacter('0' + (score[1]/10)%10, 1);
			scores[1].setCharacter('0' + ((score[1]/10)/10)%10, 0);
			resetPuck(false, puck, puck_dx, puck_dy, fb);
			scores[1].renderTextBox();
			continue;
		} else if(puck.x < 0) {
			score[0]++;
			scores[0].setCharacter('0' + score[0]%10, 2);
			scores[0].setCharacter('0' + (score[0]/10)%10, 1);
			scores[0].setCharacter('0' + ((score[0]/10)/10)%10, 0);
			resetPuck(true, puck, puck_dx, puck_dy, fb);
			scores[0].renderTextBox();
			continue;
		} else if(puck.y + puck.h >= fb.getScreenY()) {
			puck.y = fb.getScreenY() - 1 - puck.h;
			puck_dy *= -1;
		} else if(puck.y < scores[0].getBoxH() + scores[0].getBoxY()) {
			puck.y = scores[0].getBoxH() + scores[0].getBoxY();
			puck_dy *= -1;
		}
		int result;
		for(int p = 0; p < NUMPLAYERS; p++) {
			result = players[p].testCollide(puck);
			if(result == 0) {
				continue;
			} else if(result == 1) {
				puck.x = players[p].getPaddleX() + players[p].getPaddleW() + 1;
				puck_dx *= -1;
				puck_dy += rand() % 3 == 0 ? rand() % 2 ? -1 : 1 : 0;
				break;
			} else if(result == 2) {
				puck.x = players[p].getPaddleX() - puck.w - 1;
				puck_dx *= -1;
				puck_dy += rand() % 3 == 0 ? rand() % 2 ? -1 : 1 : 0;
				break;
			} else if(result == 3) {
				puck.y = players[p].getPaddleY() + players[p].getPaddleH() + 1;
				puck_dy *= -1;
				break;
			} else if(result == 4) {
				puck.y = players[p].getPaddleY() - puck.h - 1;
				puck_dy *= -1;
				break;
			}
		}
		
		draw(fb, scores, players, colors, middle, puck, NUMPLAYERS);
	}
	
	delete [] score;
	delete [] scores;
	delete [] players;
	delete [] colors;

	system("setterm --cursor on");
	return 0;
}
