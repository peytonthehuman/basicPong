#ifndef PONG_FONT_H
#define PONG_FONT_H

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
		int getIdx(char id) const;
		int pos(int idx, int x, int y) const;
	public:
		font();
		character& getChar(char id);
		bool getCharAt(char id, int index);
		bool getCharAt(char id, int x, int y);
		~font();
};

#endif
