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

bool textBox::charRender(char num, int x, int y, int w, int h) const {
	int charX = x / ((double)w/activeFont->getChar(num).getW());
	int charY = y / ((double)h/activeFont->getChar(num).getH());
	character render = activeFont->getChar(num);
	return render.getMap()[charY * render.getW() + charX];
}

textBox::textBox(int columns, int rows) {
	numColumns = columns;
	numRows = rows;
	content = new char[rows * columns];

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
	fb_dev = nullptr;

	return;
}

void textBox::setActiveFont(font* in) {
	activeFont = in;
	return;
}

font* textBox::getActiveFont() const {
	return activeFont;
}

void textBox::setActiveFB(fb_driver* in) {
	fb_dev = in;
	return;
}

fb_driver* textBox::getActiveFB() const {
	return fb_dev;
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

int textBox::getBoxWidth() const {
	return box.w;
}

int textBox::getBoxHeight() const {
	return box.h;
}

void textBox::setBoxWidth(int in) {
	box.w = in;
	return;
}

void textBox::setBoxHeight(int in) {
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
	text.x = in/2;
	text.w = box.w - in/2;
	return;
}

void textBox::setTextMarginVertical(int in) {
	text.y = in/2;
	text.h = box.h - in/2;
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
		
triple* textBox::renderTextBox() const {
	triple* pixelArray = new triple[box.w * box.h];
	rectangle* render = new rectangle[numRows * numColumns];
	for(int i = 0; i < numColumns; i++) {
		for(int j = 0; j < numRows; j++) {
			int idx = pos(j, i, numColumns);
			render[idx].w = text.w / numColumns;
			render[idx].h = text.h / numRows;
			render[idx].x = render[idx].w * j;
			render[idx].y = render[idx].h * i;
		}
	}

	for(int i = 0; i < box.h; i++) {
		for(int j = 0; j < box.w; j++) {
			if(text.x < j && j <= (text.w + text.x) && text.y < i && i <= (text.h + text.y)) {
				for(int h = 0; h < numRows * numColumns; h++) {
					if((render[h].x + text.x) < j && j <= (render[h].x + text.x + render[h].w) &&
						(render[h].y + text.y) < i && i <= (render[h].y + text.y + render[h].h)
					  ) {
						if(activeFont->getCharAt(content[pos(j, i, numColumns)], 
									j - text.x - render[h].x, i - text.y - render[h].y)) {
							pixelArray[pos(j, i, box.w)] = fg_color;
						} else {
							pixelArray[pos(j, i, box.w)] = bg_color;
						}
					}
				}
			} else {
				pixelArray[pos(j, i, box.w)] = bg_color;
			}
		}
	}

	delete [] render;

	return pixelArray;
}

textBox::~textBox() {
	delete [] content;
	return;
}
/*
class paddle {
	private:
		rectangle paddleobj;
		char pid;
		triple color;
	public:
		paddle(char pid);
		paddle(char pid, int x, int y);

		void setPaddleDX(int in);
		void setPaddleDY(int in);
		int getPaddleDX() const;
		int getPaddleDY() const;

		void setPaddlePosX(int in);
		void setPaddlePosY(int in);
		int getPaddlePosX() const;
		int getPaddlePosY() const;

		void setPaddleWidth(int in);
		void setPaddleHeight(int in);
		int getPaddleWidth() const;
		int getPaddleHeight() const;

		triple getColor() const;
		void setColor(triple& in);

		triple* renderPaddle() const;

		bool testCollide(const rectangle& collider) const;

		~paddle();
};

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
