#ifndef PONG_GAME_ELEMS_U
#define PONG_GAME_ELEMS_H

#include "./fb_main.h"
#include "./pong_font.h"

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
		triple* cache_map;

		font* activeFont;
		
		bool charRender(char num, int x, int y, int w, int h) const;

	public:
		textBox();
		textBox(int numColumns, int numRows);
		void init(int numColumns, int numRows);

		void setActiveFont(font* in);
		font* getActiveFont() const;

		int getColumns() const;
		int getRows() const;

		char getCharacter(int index) const;
		char getCharacter(int row, int column) const;
		void setCharacter(char in, int index);
		void setCharacter(char in, int row, int column);
		
		char* getContentArray() const;
		void setContentArray(char* in);

		int getBoxW() const;
		int getBoxH() const;
		void setBoxW(int in);
		void setBoxH(int in);

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
		
		bool renderTextBox();
		triple* getCache() const;

		~textBox();
};

class paddle {
	private:
		rectangle paddleobj;
		char pid;
		triple color;
		int dx;
		int dy;
	public:
		paddle();
		paddle(char id);
		
		void setID(char id);
		char getID() const;

		void setPaddleDX(int in);
		void setPaddleDY(int in);
		int getPaddleDX() const;
		int getPaddleDY() const;

		void setPaddleX(int in);
		void setPaddleY(int in);
		int getPaddleX() const;
		int getPaddleY() const;

		void setPaddleW(int in);
		void setPaddleH(int in);
		int getPaddleW() const;
		int getPaddleH() const;

		triple getColor() const;
		void setColor(triple& in);
		
		void tickMovement();

		int testCollide(const rectangle& collider) const;

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
		triple* cache_map;
	public:
		line();

		bool getOrientation() const;
		void flipOrientation();

		void setLineX(int in);
		void setLineY(int in);
		int getLineX() const;
		int getLineY() const;
		
		void setLineW(int in);
		void setLineH(int in);
		int getLineW() const;
		int getLineH() const;

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

		bool renderLine();
		triple* getCache() const;

		~line();
};

#endif
