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

int font::getIdx(char id) const {
	int retIdx = -1;
	for(int i = 0; i < numChars; i++) {
		if(charArray[i].getID() == id) {
			retIdx = i;
			break;
		}
	}
	
	return retIdx;
}

int font::pos(int idx, int x, int y) const {
	if(x > charArray[idx].getW()) {
		return -1;
	} else if(y > charArray[idx].getH()) {
		return -1;
	}
	
	return (y * charArray[idx].getW() + x);
}

font::font() {
	numChars = 37;
	charArray = new character [numChars];
	
	bool* temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0};
	charArray[0].init(' ', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0,};
	charArray[1].init('0', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,0,1,0,0,
		0,0,1,1,0,0,
		0,0,0,1,0,0,
		0,0,0,1,0,0,
		0,0,0,1,0,0,
		0,1,1,1,1,0,
		0,0,0,0,0,0};
	charArray[2].init('1', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,0,0,0,1,0,
		0,0,0,1,0,0,
		0,0,1,0,0,0,
		0,1,1,1,1,0,
		0,0,0,0,0,0};
	charArray[3].init('2', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,0,0,1,0,0,
		0,0,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[4].init('3', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,0,0,1,0,
		0,0,0,1,1,0,
		0,0,1,0,1,0,
		0,1,1,1,1,0,
		0,0,0,0,1,0,
		0,0,0,0,1,0,
		0,0,0,0,0,0};
	charArray[5].init('4', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,0,0,
		0,1,1,1,0,0,
		0,0,0,0,1,0,
		0,0,0,0,1,0,
		0,1,1,1,0,0,
		0,0,0,0,0,0};
	charArray[6].init('5', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[7].init('6', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,1,0,
		0,0,0,0,1,0,
		0,0,0,0,1,0,
		0,0,0,1,0,0,
		0,0,0,1,0,0,
		0,0,1,0,0,0,
		0,0,0,0,0,0};
	charArray[8].init('7', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[9].init('8', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,1,0,
		0,0,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[10].init('9', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[11].init('A', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,0,0,
		0,0,0,0,0,0,};
	charArray[12].init('B', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,1,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,0,1,1,1,0,
		0,0,0,0,0,0,};
	charArray[13].init('C', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,0,0,
		0,0,0,0,0,0,};
	charArray[14].init('D', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,1,0,
		0,1,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,1,1,1,0,
		0,0,0,0,0,0,};
	charArray[15].init('E', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,1,0,
		0,1,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,0,0,0,0,0,};
	charArray[16].init('F', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,1,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,1,1,0,
		0,1,0,0,1,0,
		0,0,1,1,1,0,
		0,0,0,0,0,0,};
	charArray[17].init('G', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0,};
	charArray[18].init('H', temp, 6, 8);
	
	temp = new bool[7 * 8] {
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,0,0,0,0};
	charArray[19].init('I', temp, 7, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,1,0,
		0,0,0,0,1,0,
		0,0,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[20].init('J', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,0,1,0,0,
		0,1,1,0,0,0,
		0,1,0,1,0,0,
		0,1,0,1,0,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[21].init('K', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,1,1,1,1,0,
		0,0,0,0,0,0};
	charArray[22].init('L', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,1,1,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[23].init('M', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,1,0,1,0,
		0,1,1,0,1,0,
		0,1,0,1,1,0,
		0,1,0,1,1,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[24].init('N', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[25].init('O', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,0,0,
		0,1,0,0,0,0,
		0,1,0,0,0,0,
		0,0,0,0,0,0};
	charArray[26].init('P', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,1,1,0,
		0,0,1,1,1,0,
		0,0,0,0,0,0};
	charArray[27].init('Q', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,1,1,0,0,
		0,1,0,1,0,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[28].init('R', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,0,1,1,1,0,
		0,1,0,0,0,0,
		0,0,1,1,0,0,
		0,0,0,0,1,0,
		0,0,0,0,1,0,
		0,1,1,1,0,0,
		0,0,0,0,0,0};
	charArray[29].init('S', temp, 6, 8);
	
	temp = new bool[7 * 8] {
		0,0,0,0,0,0,0,
		0,1,1,1,1,1,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0};
	charArray[30].init('T', temp, 7, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[31].init('U', temp, 6, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,1,1,0,0,
		0,0,0,0,0,0};
	charArray[32].init('V', temp, 6, 8);
	
	temp = new bool[7 * 8] {
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,1,0,1,0,1,0,
		0,1,1,1,1,1,0,
		0,0,1,0,1,0,0,
		0,0,0,0,0,0,0};
	charArray[33].init('W', temp, 7, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,1,1,0,0,
		0,0,1,1,0,0,
		0,1,0,0,1,0,
		0,1,0,0,1,0,
		0,0,0,0,0,0};
	charArray[34].init('X', temp, 6, 8);
	
	temp = new bool[7 * 8] {
		0,0,0,0,0,0,0,
		0,1,0,0,0,1,0,
		0,1,0,0,0,1,0,
		0,0,1,0,1,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,1,0,0,0,
		0,0,0,0,0,0,0};
	charArray[35].init('Y', temp, 7, 8);
	
	temp = new bool[6 * 8] {
		0,0,0,0,0,0,
		0,1,1,1,1,0,
		0,0,0,1,0,0,
		0,0,0,1,0,0,
		0,0,1,0,0,0,
		0,0,1,0,0,0,
		0,1,1,1,1,0,
		0,0,0,0,0,0};
	charArray[36].init('Z', temp, 6, 8);
	
	return;
}

character* font::getChar(char id) {
	character* retCharacter = nullptr;
	int index = getIdx(id);
	if(index != -1) {
		retCharacter = &charArray[index];
	}
	return retCharacter;
}

bool font::getCharAt(char id, int index) {
	character* temp = getChar(id);
	bool tempPoint = false;
	if(temp->getMap()) {
		int arraySize = temp->getW() * temp->getH();
		if(index < arraySize) {
			tempPoint = temp->getMap()[index];
		}
	}
	return tempPoint;
}

bool font::getCharAt(char id, int x, int y) {
	character *temp = getChar(id);
	bool tempPoint = false;
	if(temp->getMap()) {
		int arraySize = temp->getW() * temp->getH();
		if(pos(x, y, temp->getW()) < arraySize) {
			tempPoint = temp->getMap()[pos(x, y, temp->getW())];
		}
	}
	return tempPoint;
}

font::~font() {
	delete [] charArray;
	return;
}
