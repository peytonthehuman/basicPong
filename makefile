CC = g++

CFLAGS = -c

all: pong

pong: main.o fb_driver.o field.o font.o elems.o
	$(CC) main.o fb_driver.o field.o font.o elems.o -o pong

main.o: pong.cpp
	$(CC) $(CFLAGS) pong.cpp -o main.o

fb_driver.o: fb_main.cpp
	$(CC) $(CFLAGS) fb_main.cpp -o fb_driver.o

field.o: pong_field.cpp
	$(CC) $(CFLAGS) pong_field.cpp -o field.o

font.o: pong_font.cpp
	$(CC) $(CFLAGS) pong_font.cpp -o font.o

elems.o: pong_game_elems.cpp
	$(CC) $(CFLAGS) pong_game_elems.cpp -o elems.o

clean:
	rm *.o
