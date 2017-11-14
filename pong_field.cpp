#include "./pong_field.h"

void field::init() {
	scoreWidth = 3;
	maxScore = 0;
	
	scores = new textBox[NUMPLAYERS];
	players = new paddle[NUMPLAYERS];
	pallete = new triple[2];
	
	pallete[0].x = 0;
	pallete[0].y = 0;
	pallete[0].z = 0;
	
	pallete[1].x = 255;
	pallete[1].y = 255;
	pallete[1].z = 255;
	
	for(int i = 0; i < NUMPLAYERS; i++) {
		scores[i].init(scoreWidth, 1);
		scores[i].setActiveFont(activeFont);
		scores[i].setBoxW(activeFB->getScreenX() / 6);
		scores[i].setBoxH(activeFB->getScreenY() / 10);
		scores[i].setTextMarginHorizontal(6);
		scores[i].setTextMarginVertical(6);
		scores[i].setBoxY(activeFB->getScreenY()/20);
		scores[i].setFGColor(pallete[1]);
		scores[i].setBGColor(pallete[0]);
	}
	
	scores[0].setBoxX(activeFB->getScreenX()/2 + scores[0].getBoxW() * 2 - scores[0].getBoxW());
	scores[1].setBoxX(activeFB->getScreenX()/2 - scores[1].getBoxW() * 2);
	
	for(int i = 0; i < NUMPLAYERS; i++) {
		players[i].setID('0' + i);
		players[i].setPaddleW(activeFB->getScreenX()/80);
		players[i].setPaddleH(activeFB->getScreenY()/7);
		players[i].setPaddleY(activeFB->getScreenY()/2 - players[i].getPaddleH()/2);
		players[i].setColor(pallete[1]);
	}
	
	players[0].setPaddleX(activeFB->getScreenX()/2 - (activeFB->getScreenX()/2 - activeFB->getScreenX()/10) - players[0].getPaddleW());
	players[1].setPaddleX(activeFB->getScreenX()/2 + (activeFB->getScreenX()/2 - activeFB->getScreenX()/10));
	
	middle.setLineW(2);
	middle.setLineH(activeFB->getScreenY() - scores[0].getBoxY() - scores[0].getBoxH() - activeFB->getScreenY()/20);
	middle.setLineX(activeFB->getScreenX()/2 - middle.getLineW()/2);
	middle.setLineY(scores[0].getBoxH() + scores[0].getBoxY());
	middle.setDashed(true);
	middle.setDashLength(activeFB->getScreenY()/10);
	middle.setDashMargin(activeFB->getScreenY()/15);
	middle.setFG_Color(pallete[1]);
	middle.setBG_Color(pallete[0]);
	middle.renderLine();
	
	puck.w = activeFB->getScreenX()/80;
	puck.h = puck.w;
	resetPuck(true);
	
	return;
}

void field::paintRec(triple color, int x, int y, int w, int h) {
	if(activeFB == nullptr) {
		return;
	}
	
	for(int ry = 0; ry < h; ry++) {
		for(int rx = 0; rx < w; rx++) {
			activeFB->setPixel(color, x + rx, y + ry);
		}
	}
	
	return;
}

void field::paintTex(triple* surf, int x, int y, int w, int h) {
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

void field::resetPuck(bool dir) {
	puck_dx = dir ? puck_startspeed : -puck_startspeed;
	puck_dy = 0;
	puck.x = activeFB->getScreenX() / 2 - puck.w / 2;
	puck.y = activeFB->getScreenY() / 2 - puck.h / 2;
	
	return;
}

void field::resetPaddles() {
	for(int i = 0; i < NUMPLAYERS; i++) {
		players[i].setPaddleY(activeFB->getScreenY() / 2 - players[i].getPaddleH() / 2);
		players[i].setPaddleDY(0);
	}
	
	return;
}

field::field() {
	activeFB = nullptr;
	activeFont = nullptr;
	NUMPLAYERS = 2;
	puck_startspeed = 0;
	currentScore = new int[NUMPLAYERS];
	bounceRand = 3;
	
	init();
	return;
}

field::field(fb_driver* fb) {
	activeFB = fb;
	activeFont = nullptr;
	NUMPLAYERS = 2;
	puck_startspeed = 0;
	currentScore = new int[NUMPLAYERS];
	bounceRand = 3;
	
	init();
	return;
}

void field::setActiveFB(fb_driver* fbin) {
	activeFB = fbin;
	return;
}

void field::setActiveFont(font* font) {
	activeFont = font;
	for(int i = 0; i < NUMPLAYERS; i++) {
		scores[i].setActiveFont(activeFont);
		scores[i].renderTextBox();
	}
	return;
}

fb_driver* field::getActiveFB() const {
	return activeFB;
}

font* field::getActiveFont() const {
	return activeFont;
}

void field::setPuckStartSpeed(unsigned int speed) {
	puck_startspeed = speed;
	resetPuck(rand()%2);
	return;
}

int field::getPuckStartSpeed() const {
	return puck_startspeed;
}

void field::setMaxScore(unsigned int score) {
	maxScore = score;
	return;
}

int field::getMaxScore() const {
	return maxScore;
}

int field::getNumPlayers() const {
	return NUMPLAYERS;
}

void field::setScore(unsigned int PID, int score) {
	currentScore[PID] = score;
	for(int i = 0; i < scores[PID].getColumns(); i++) {
		int digit = (currentScore[PID]/((int)pow(10, i)))%10;
		scores[PID].setCharacter('0' + digit, scores[PID].getColumns() - i - 1);
	}
	scores[PID].renderTextBox();
	return;
}

int field::getScore(unsigned int PID) const {
	return currentScore[PID];
}

void field::setPallete(triple* inPallete) {
	pallete = inPallete;
	for(int i = 0; i < NUMPLAYERS; i++) {
		players[i].setColor(pallete[1]);
		scores[i].setFGColor(pallete[1]);
		scores[i].setBGColor(pallete[0]);
		scores[i].renderTextBox();
	}
	middle.setFG_Color(pallete[1]);
	middle.setBG_Color(pallete[0]);
	middle.renderLine();
	return;
}

triple* field::getPallete() const {
	return pallete;
}

triple field::getColor(unsigned int ID) const {
	return pallete[ID];
}

void field::nudgePaddle(bool direction, unsigned int PID) {
	if(direction) {
		players[PID].setPaddleDY(players[PID].getPaddleDY() + 2);
	} else {
		players[PID].setPaddleDY(players[PID].getPaddleDY() - 2);
	}
	
	return;
}
#include <iostream>
bool field::tickPhysics() { 
	puck.x += puck_dx;
	puck.y += puck_dy;
	
	int topY = scores[0].getBoxH() + scores[0].getBoxY();
	for(int i = 0; i < NUMPLAYERS; i++) {
		if(players[i].getPaddleY() >= topY && players[i].getPaddleY() + players[i].getPaddleH() < activeFB->getScreenY()) {
			players[i].tickMovement();
		} else {
			players[i].setPaddleDY(0);
			if(players[i].getPaddleY() < topY) {
				players[i].setPaddleY(topY + 1);
			} else {
				players[i].setPaddleY(activeFB -> getScreenY() - players[i].getPaddleH() - 1);
			}
		}
	}
	
	if(puck.x + puck.w >= activeFB->getScreenX()) {
		setScore(1, getScore(1) + 1);
		resetPuck(false);
		resetPaddles();
		return true;
	} else if(puck.x < 0) {
		setScore(0, getScore(0) + 1);
		resetPuck(true);
		resetPaddles();
		return true;
	}
	
	if(puck.y < topY) {
		puck.y = topY + 1;
		puck_dy *= -1;
	} else if(puck.y + puck.h >= activeFB->getScreenY()) {
		puck.y = activeFB->getScreenY() - puck.h - 1;
		puck_dy *= -1;
	}
	
	for(int i = 0; i < NUMPLAYERS; i++) {
		int result = players[i].testCollide(puck);
		switch(result) {
			case 0:
				break;
			case 1:
				puck.x = players[i].getPaddleX() + players[i].getPaddleW() + 1;
				puck_dx *= -1;
				puck_dy += rand() % bounceRand == 0 ? rand() % 2 ? -1 : 1 : 0;
				puck_dy += players[i].getPaddleDY();
				break;
			case 2:
				puck.x = players[i].getPaddleX() - players[i].getPaddleW() - 1;
				puck_dx *= -1;
				puck_dy += rand() % bounceRand == 0 ? rand() % 2 ? -1 : 1 : 0;
				puck_dy += players[i].getPaddleDY();
				break;
			case 3:
				puck.y = players[i].getPaddleY() + players[i].getPaddleH() + 1;
				puck_dy *= -1;
				break;
			case 4:
				puck.y = players[i].getPaddleY() - players[i].getPaddleH() - 1;
				puck_dy *= -1;
				break;
		}
	}
	
	return false;
}

void field::resetGame() {
	resetPaddles();
	resetPuck(true);
	for(int i = 0; i < NUMPLAYERS; i++) {
		setScore(i, 0);
	}
	
	return;
}

void field::drawField() {
	for(int i = 0; i < NUMPLAYERS; i++) {
		paintTex(scores[i].getCache(), scores[i].getBoxX(), scores[i].getBoxY(), scores[i].getBoxW(), scores[i].getBoxH());
		
		paintRec(players[i].getColor(), players[i].getPaddleX(), players[i].getPaddleY(), players[i].getPaddleW(), players[i].getPaddleH());
	}
	
	paintTex(middle.getCache(), middle.getLineX(), middle.getLineY(), middle.getLineW(), middle.getLineH());
	paintRec(pallete[1], puck.x, puck.y, puck.w, puck.h);
	
	return;
}

field::~field() {
	delete [] scores;
	delete [] players;
	delete [] currentScore;
	
	return;
}