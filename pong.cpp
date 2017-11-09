#include <time.h>
#include <cstdlib>
#include <ctime>
#include "../fb_main.h"
#include "./pong_game_elems.h"

void wipeScreen(triple& bg_color, fb_driver& fb) {
	for(int i = 0; i < fb.getScreenY(); i++) {
		for(int j = 0; j < fb.getScreenX(); j++) {
			fb.setPixel(bg_color, j, i);
		}
	}
}

void draw(fb_driver& fb) {
// put color defs here
	triple black;
	black.x = 0;
	black.y = 0;
	black.z = 0;

// put setup code here

	unsigned int fps = 60;
	unsigned int secs = 5;
	int width = fb.getScreenX();
	int height = fb.getScreenY();
	srand(time(NULL));

	wipeScreen(black, fb);

	struct timespec cursor;
	clock_gettime(CLOCK_MONOTONIC, &cursor);
	int timestep = ((double)1/(double)fps) * 1000000000;
	int wait;

	for(int i = 0; i < (fps * secs); i++) {
		int start = cursor.tv_nsec;
		wipeScreen(black, fb);

		//put drawing code in here

		//end drawing code

		fb.swapBuffer();

		wait = timestep - (cursor.tv_nsec - start);
		usleep(wait < 0 ? 0 : wait/1000);
	}
	wipeScreen(black, fb);
	return;
}

int main() {
	system("setterm --cursor off");
	system("clear");
	fb_driver fb(false, false);
	fb.init();

	draw(fb);

	system("setterm --cursor on");
	return 0;
}
