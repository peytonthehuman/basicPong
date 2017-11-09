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

int font::getIdx(char id) {
	int retIdx = -1;
	for(int i = 0; i < numChars; i++) {
		if(charArray[i].getID()) {
			retIdx = 0;
			break;
		}
	}
	
	return retIdx;
}

int font::pos(int idx, int x, int y) {
	if(x > charArray[idx].getW()) {
		return -1;
	} else if(y > charArray[idx].getH()) {
		return -1;
	}
	
	return (y * charArray[idx].getW() + x);
}

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
	character* retCharacter = new character;
	int index = getIdx(id);
	if(index != -1) {
		retCharacter = charArray[index];
	}
	return retCharacter;
}

bool font::getCharAt(char id, int index) {
	character* temp = getChar(id);
	bool tempPoint = false;
	if(temp->getMap()) {
		if(index < (temp->getW() * temp->getH())) {
			tempPoint = temp->getMap()[index];
		}
	}
	return tempPoint;
}

bool font::getCharAt(char id, int x, int y) {
	character* temp = getChar(id);
	bool tempPoint = false;
	if(temp->getMap()) {
		if(index < (temp->getW() * temp->getH())) {
			tempPoint = temp->getMap()[pos(x, y, temp->getW())];
		}
	}
	return tempPoint;
}

font::~font() {
	delete [] charArray;
	return;
}
