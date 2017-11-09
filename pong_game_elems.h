#ifndef PONG_GAME_ELEMS_U
#define PONG_GAME_ELEMS_H
#include "../fb_main.h"

// character object, which is used to display characters on screen
class character {
	private:
		int w;
		int h;
		char id;
		bool* map;
	public:
		character();
		void init(char inId, bool* inMap, int inW, int inH);

		int getW() const;
		int getH() const;
		char getID() const;
		bool* getMap() const;

		~character();
};

class font { // font class
	private:
		character* charArray;
		int numChars;
	public:
		font();
		character& getChar(char id);
		bool getCharAt(char id, int index);
		bool getCharAt(char id, int x, int y);
		~font();
};

// rectangle object, used to create rectangles.
struct rectangle {
	int x;
	int y;
	int w;
	int h;
};

// textbox object, used to display textboxes on screen
class textBox {
	private:
		rectangle box;
		rectangle text;

		int numColumns;
		int numRows;
		char* content;

		triple fg_color;
		triple bg_color;

		font* activeFont;
		fb_driver* fb_dev;
		
		bool charRender(char num, int x, int y, int w, int h) const;

	public:
		textBox(int numColumns, int numRows);

		void setActiveFont(font* in);
		font* getActiveFont() const;

		void setActiveFB(fb_driver* in);
		fb_driver* getActiveFB() const;

		int getColumns() const;
		int getRows() const;

		char getCharacter(int index) const;
		char getCharacter(int row, int column) const;
		void setCharacter(char in, int index);
		void setCharacter(char in, int row, int column);

		int getBoxWidth() const;
		int getBoxHeight() const;
		void setBoxWidth(int in);
		void setBoxHeight(int in);

		int getBoxX() const;
		int getBoxY() const;
		void setBoxX(int in);
		void setBoxY(int in);

		int getTextMarginHorizontal() const;
		int getTextMarginVertical() const;
		void setTextMarginHorizontal(int in);
		void setTextMarginVertical(int in);

		triple getFGColor() const;
		triple getBGColor() const;
		void setFGColor(triple in);
		void setBGColor(triple in);
		
		triple* renderTextBox() const;

		~textBox();
};

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
};

#endif
