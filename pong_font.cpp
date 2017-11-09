#include "./fb_main.h"
#include "./pong_font.h"

// character object, which is used to display characters on screen

character::character() {
	id = '\0';
	w = 0;
	h = 0;
	map = nullptr;
}

void character::init(char inId, bool* inMap, int inW, int inH) {
	id = inId;
	w = inW;
	h = inH;
	map = inMap;
}

int character::getW() const {
	return w;
}

int character::getH() const {
	return h;
}

char character::getID() const {
	return id;
}

bool* character::getMap() const {
	return map;
}

character::~character() {
	delete [] map;
	return;
}

// Font Class definitions. The Font class contains all font data for the game

//character* charArray;
//int numChars;

font::font() {
	numChars = 1;
	charArray = new character [numChars];
	bool* temp = new bool[6 * 6] {
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0};
	charArray[1].init('0', temp, 6, 6);
	delete [] temp;
	return;
}

character& font::getChar(char id) {
	character* nullChar = new character;
	for(int i = 0; i < numChars; i++) {
		if(charArray[i].getID()) {
			return charArray[i];
		}
	}
	return *nullChar;
}

bool font::getCharAt(char id, int index) {
	bool* temp = getChar(id).getMap();
	if(temp) {
		return temp[index];
	}
	return false;
}

bool font::getCharAt(char id, int x, int y) {
	return false;
}

font::~font() {
	delete [] charArray;
	return;
}
