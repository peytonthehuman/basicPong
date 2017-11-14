#ifndef PONG_FIELD_H
#define PONG_FIELD_H

#include <time.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "./fb_main.h"
#include "./pong_game_elems.h"
#include "./pong_font.h"

class field {
	private:
		fb_driver* activeFB;
		font* activeFont;
		
		unsigned int NUMPLAYERS;
		unsigned int maxScore;
		int* currentScore;
		unsigned int scoreWidth;
		textBox* scores;
		paddle* players;
		triple* pallete;
		line middle;
		
		rectangle puck;
		int puck_dx;
		int puck_dy;
		int puck_startspeed;
		
		int bounceRand;
		
		void init();
		
		void paintRec(triple color, int x, int y, int w, int h);
		void paintTex(triple* surf, int x, int y, int w, int h);
		
		void resetPuck(bool dir);
		void resetPaddles();
	public:
		field();
		field(fb_driver* fb);
	
		void setActiveFB(fb_driver* fbin);
		void setActiveFont(font* font);
		fb_driver* getActiveFB() const;
		font* getActiveFont() const;
		
		void setPuckStartSpeed(unsigned int speed);
		int getPuckStartSpeed() const;
		
		void setMaxScore(unsigned int score);
		int getMaxScore() const;
		int getNumPlayers() const;
		
		void setScore(unsigned int PID, int score);
		int getScore(unsigned int PID) const;
		
		int getPuckDX() const { return puck_dx; }
		void setPuckDX(int in) { puck_dx = in; }
		int getPuckDY() const { return puck_dy; }
		int getPuckX() const { return puck.x; }
		int getPuckY() const { return puck.y; }
		
		int getPaddleX(int pid) const { return players[pid].getPaddleX(); }
		int getPaddleY(int pid) const { return players[pid].getPaddleY(); }
		int getPaddleW(int pid) const { return players[pid].getPaddleW(); }
		int getPaddleH(int pid) const { return players[pid].getPaddleH(); }
		
		void setPallete(triple* inPallete);
		triple* getPallete() const;
		triple getColor(unsigned int ID) const;
		
		void nudgePaddle(bool direction, unsigned int PID);
		
		bool tickPhysics();
		void resetGame();
		
		void drawField();
		
		~field();
};

#endif