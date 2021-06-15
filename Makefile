CC = g++
FLAGS = -fno-asm -Wall -Wextra -std=c++17 -lmpdclient
files = mpd-update-queue

install : mpd-update-queue

mpd-update-queue : main.cpp
	$(CC) $(FLAGS) main.cpp -o mpd-update-queue

clear :
	rm -f $(files)
