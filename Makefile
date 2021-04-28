CC = g++
FLAGS = -fno-asm -Wall -Wextra -std=c++17 -lmpdclient
files = main.out

install : 
	$(CC) $(FLAGS) main.cpp -o main.out

clear :
	rm -f $(files)
