#include "./fb_main.h"
#include "./pong_game_elems.h"
#include "./pong_font.h"

int pos(int x, int y, int w) {
	return y * w + x;
}

// Font and Character class implimented in pong_font.h

/* rectangle object, used to create rectangles.
struct rectangle {
	int x;
	int y;
	int w;
	int h;
};*/

// textbox object definitions
#include <iostream>
bool textBox::charRender(char num, int x, int y, int w, int h) const {
	character* render = activeFont->getChar(num);
	//int charX = x/((double)w/(render->getW()));
	//int charY = y/((double)h/(render->getH()));
	int charX = ((double)x/(double)w) * render->getW();
	int charY = ((double)y/(double)h) * render->getH();
	bool * map = render->getMap();
	return map[charY * render->getW() + charX];
}

textBox::textBox() {
	numColumns = 0;
	numRows = 0;
	content = nullptr;
	cache_map = nullptr;
	
	box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = 0;
	
	text.x = 0;
	text.y = 0;
	text.w = 0;
	text.h = 0;
	
	fg_color.x = 0;
	fg_color.y = 0;
	fg_color.z = 0;
	
	bg_color.x = 0;
	bg_color.y = 0;
	bg_color.z = 0;
	
	activeFont = nullptr;
	
	return;
}

textBox::textBox(int columns, int rows) {
	numColumns = columns;
	numRows = rows;
	content = new char[rows * columns];
	for(int i = 0; i < rows * columns; i++) {
		content[i] = '0';
	}
	cache_map = nullptr;

	box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = 0;

	text.x = 0;
	text.y = 0;
	text.w = 0;
	text.h = 0;

	fg_color.x = 0;
	fg_color.y = 0;
	fg_color.z = 0;

	bg_color.x = 0;
	bg_color.y = 0;
	bg_color.z = 0;

	activeFont = nullptr;

	return;
}

void textBox::init(int columns, int rows) {
	numColumns = columns;
	numRows = rows;
	content = new char[rows * columns];
	for(int i = 0; i < rows * columns; i++) {
		content[i] = '0';
	}
}

void textBox::setActiveFont(font* in) {
	activeFont = in;
	return;
}

font* textBox::getActiveFont() const {
	return activeFont;
}

int textBox::getColumns() const {
	return numColumns;
}

int textBox::getRows() const {
	return numRows;
}

char textBox::getCharacter(int index) const {
	return content[index];
}

char textBox::getCharacter(int row, int column) const {
	return content[pos(row, column, numColumns)];
}

void textBox::setCharacter(char in, int index) {
	content[index] = in;
	return;
}

void textBox::setCharacter(char in, int row, int column) {
	content[pos(row, column, numColumns)] = in;
	return;
}

int textBox::getBoxW() const {
	return box.w;
}

int textBox::getBoxH() const {
	return box.h;
}

void textBox::setBoxW(int in) {
	box.w = in;
	return;
}

void textBox::setBoxH(int in) {
	box.h = in;
	return;
}

int textBox::getBoxX() const {
	return box.x;
}

int textBox::getBoxY() const {
	return box.y;
}

void textBox::setBoxX(int in) {
	box.x = in;
	return;
}

void textBox::setBoxY(int in) {
	box.y = in;
	return;
}

int textBox::getTextMarginHorizontal() const {
	return text.x * 2;
}

int textBox::getTextMarginVertical() const {
	return text.y * 2;
}

void textBox::setTextMarginHorizontal(int in) {
	text.x = in - 1;
	text.w = box.w - 2 * (in - 2);
	return;
}

void textBox::setTextMarginVertical(int in) {
	text.y = in - 1;
	text.h = box.h - 2 * (in - 2);
	return;
}

triple textBox::getFGColor() const {
	return fg_color;
}

triple textBox::getBGColor() const {
	return bg_color;
}

void textBox::setFGColor(triple in) {
	fg_color = in;
	return;
}

void textBox::setBGColor(triple in) {
	bg_color = in;
	return;
}

bool textBox::renderTextBox() {
	// consider optimizing by selectively rerendering based on what has changed.
	if(cache_map != nullptr) {
		delete [] cache_map;
	}
	
	cache_map = new triple[box.w * box.h];
	
	rectangle* render = new rectangle[numRows * numColumns];
	for(int ry = 0; ry < numRows; ry++) {
		for(int rx = 0; rx < numColumns; rx++) {
			int idx = pos(rx, ry, numColumns);
			render[idx].w = text.w / numColumns;
			render[idx].h = text.h / numRows;
			render[idx].x = render[idx].w * rx;
			render[idx].y = render[idx].h * ry;
		}
	}
	
	for(int by = 0; by < box.h; by++) {
		for(int bx = 0; bx < box.w; bx++) {
			if(text.y <= by && by < (text.y + text.h) && text.x <= bx && bx < (text.x + text.w)) {
				for(int idx = 0; idx < numRows * numColumns; idx++) {
					bool test = render[idx].y + text.y <= by && by < (render[idx].y + text.y + render[idx].h);
					test = test && render[idx].x + text.x <= bx && bx < (render[idx].x + text.x + render[idx].w);
					if(test) {
						if(charRender(content[idx],
						bx - render[idx].x - text.x,
						by - render[idx].y - text.y,
						render[idx].w, render[idx].h)) {
							cache_map[pos(bx, by, box.w)] = fg_color;
						} else {
							cache_map[pos(bx, by, box.w)] = bg_color;
						}
					}
				}
			} else {
				cache_map[pos(bx, by, box.w)] = bg_color;
			}
		}
	}
	
	return 1;
}

triple* textBox::getCache() const {
	return cache_map;
}

textBox::~textBox() {
	delete [] content;
	if(cache_map != nullptr) {
		delete [] cache_map;
	}
	return;
}

paddle::paddle() {
	pid = '\0';
	
	color.x = 0;
	color.y = 0;
	color.z = 0;
	
	paddleobj.x = 0;
	paddleobj.y = 0;
	paddleobj.w = 0;
	paddleobj.h = 0;
	
	return;
}

paddle::paddle(char id) {
	pid = id;
	
	color.x = 0;
	color.y = 0;
	color.z = 0;
	
	paddleobj.x = 0;
	paddleobj.y = 0;
	paddleobj.w = 0;
	paddleobj.h = 0;
	
	return;
}

void paddle::setID(char id) {
	pid = id;
}

char paddle::getID() const {
	return pid;
}

void paddle::setPaddleDX(int in) {
	dx = in;
}

void paddle::setPaddleDY(int in) {
	dy = in;
}

int paddle::getPaddleDX() const {
	return dx;
}

int paddle::getPaddleDY() const {
	return dy;
}

void paddle::setPaddleX(int in) {
	paddleobj.x = in;
}

void paddle::setPaddleY(int in) {
	paddleobj.y = in;
}

int paddle::getPaddleX() const {
	return paddleobj.x;
}

int paddle::getPaddleY() const {
	return paddleobj.y;
}

void paddle::setPaddleW(int in) {
	paddleobj.w = in;
}

void paddle::setPaddleH(int in) {
	paddleobj.h = in;
}

int paddle::getPaddleW() const {
	return paddleobj.w;
}

int paddle::getPaddleH() const {
	return paddleobj.h;
}

triple paddle::getColor() const {
	return color;
}

void paddle::setColor(triple& in) {
	color = in;
}

int paddle::testCollide(const rectangle& collider) const {
	int colliderPoints[] = {collider.x, collider.x + collider.w, collider.y, collider.y + collider.h};
	bool collide1 = paddleobj.x <= colliderPoints[0] && colliderPoints[0] < (paddleobj.x + paddleobj.w);
	bool collide2 = paddleobj.x <= colliderPoints[1] && colliderPoints[1] < (paddleobj.x + paddleobj.w);
	bool collide3 = paddleobj.y <= colliderPoints[2] && colliderPoints[2] < (paddleobj.y + paddleobj.h);
	bool collide4 = paddleobj.y <= colliderPoints[3] && colliderPoints[3] < (paddleobj.y + paddleobj.h);
	
	if(collide1 && (collide3 || collide4)) {
		return 1;
	} else if(collide2 && (collide3 || collide4)) {
		return 2;
	} else if(collide3 && (collide1 || collide2)) {
		return 3;
	} else if(collide4 && (collide1 || collide2)) {
		return 4;
	} else {
		return 0;
	}
}

void paddle::tickMovement() {
	if(dx > 0) {
		paddleobj.x++;
		dx--;
	} else if(dx < 0) {
		paddleobj.x--;
		dx++;
	}
	
	if(dy > 0) {
		paddleobj.y++;
		dy--;
	} else if(dy < 0) {
		paddleobj.y--;
		dy++;
	}
}

paddle::~paddle() {
	return;
}

/*
bool orientation; //false - horizontal , true - vertical
rectangle container;

bool dashed;
int dash_length;
int dash_margin;

triple fg_color;
triple bg_color;
triple* cache_map;
*/

line::line() {
	orientation = false;

	container.x = 0;
	container.y = 0;
	container.w = 0;
	container.h = 0;
	
	dashed = false;
	dash_length = 0;
	dash_margin = 0;
	
	fg_color.x = 0;
	fg_color.y = 0;
	fg_color.z = 0;
	
	bg_color.x = 0;
	bg_color.y = 0;
	bg_color.z = 0;
	
	cache_map = nullptr;
}

bool line::getOrientation() const {
	return orientation;
}

void line::flipOrientation() {
	orientation = !orientation;
	return;
}

void line::setLineX(int in) {
	container.x = in;
	return;
}

void line::setLineY(int in) {
	container.y = in;
	return;
}

int line::getLineX() const {
	return container.x;
}

int line::getLineY() const {
	return container.y;
}

void line::setLineW(int in) {
	container.w = in;
	return;
}

void line::setLineH(int in) {
	container.h = in;
	return;
}

int line::getLineW() const {
	return container.w;
}

int line::getLineH() const {
	return container.h;
}

void line::setDashed(bool in) {
	dashed = in;
	return;
}

bool line::isDashed() const {
	return dashed;
}

void line::setDashLength(int in) {
	dash_length = in;
	return;
}

void line::setDashMargin(int in) {
	dash_margin = in;
	return;
}

int line::getDashLength() const {
	return dash_length;
}

int line::getDashMargin() const {
	return dash_margin;
}

void line::setFG_Color(triple& color) {
	fg_color = color;
}

void line::setBG_Color(triple& color) {
	bg_color = color;
}

triple line::getFG_Color() const {
	return fg_color;
}

triple line::getBG_Color() const {
	return bg_color;
}

bool line::renderLine() {
	if(cache_map != nullptr) {
		delete [] cache_map;
	}
	
	cache_map = new triple[container.w * container.h];
	
	if(!dashed) {
		for(int i = 0; i < container.w * container.h; i++) {
			cache_map[i] = fg_color;
		}
	} else {
		if(orientation) {
			for(int sy = 0; sy < container.h; sy++) {
				int current = 0;
				for(int sx = 0; sx < container.w; sx++) {
					current++;
					if(current >= dash_length + dash_margin) {
						current = 0;
					}
					
					if(current < dash_length) {
						cache_map[sy * container.w + sx] = fg_color;
					} else if(dash_length <= current && current < dash_length + dash_margin) {
						cache_map[sy * container.w + sx] = bg_color;
					}
				}
			}
		} else {
			for(int sx = 0; sx < container.w; sx++) {
				int current = 0;
				for(int sy = 0; sy < container.h; sy++) {
					current++;
					if(current >= dash_length + dash_margin) {
						current = 0;
					}
					
					if(current < dash_length) {
						cache_map[sy * container.w + sx] = fg_color;
					} else if(dash_length <= current && current < dash_length + dash_margin) {
						cache_map[sy * container.w + sx] = bg_color;
					}
				}
			}
		}
	}
	
	return cache_map;
}

triple* line::getCache() const {
	return cache_map;
}

line::~line() {
	delete [] cache_map;
	return;
}