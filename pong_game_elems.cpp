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

bool paddle::testCollide(const rectangle& collider) const {
	int colliderPoints[] = {collider.x, collider.x + collider.w, collider.y, collider.y + collider.h};
	bool collidetest = paddleobj.x <= colliderPoints[0] && colliderPoints[0] < (paddleobj.x + paddleobj.w);
	collidetest = collidetest || (paddleobj.x <= colliderPoints[1] && colliderPoints[1] < (paddleobj.x + paddleobj.w));
	collidetest = collidetest || (paddleobj.y <= colliderPoints[2] && colliderPoints[2] < (paddleobj.y + paddleobj.h));
	collidetest = collidetest || (paddleobj.y <= colliderPoints[3] && colliderPoints[3] < (paddleobj.y + paddleobj.h));
	
	return collidetest;
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
class line {
	private:
		bool orientation; //false - horizontal , true - vertical
		rectangle container;

		bool dashed;
		int dash_length;
		int dash_margin;

		triple fg_color;
		triple bg_color;
	public:
		line(bool orient);

		bool getOrientation() const;
		void flipOrientation();

		void setLineWidth(int in);
		void setLineHeight(int in);
		int getLineWidth() const;
		int getLineHeight() const;

		void setDashed(bool in);
		bool isDashed() const;

		void setDashLength(int in);
		void setDashMargin(int in);
		int getDashLength() const;
		int getDashMargin() const;

		void setFG_Color(triple& color);
		void setBG_Color(triple& color);
		triple getFG_Color() const;
		triple getBG_Color() const;

		triple* renderLine() const;

		~line();
};*/
