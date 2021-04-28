CC = g++
FLAGS = -fno-asm -Wall -Wextra -std=c++17 -lmpdclient
files = mpd-autoupdate-queue

install : 
	$(CC) $(FLAGS) main.cpp -o mpd-autoupdate-queue

clear :
	rm -f $(files)
