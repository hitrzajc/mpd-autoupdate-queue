CC = g++
FLAGS = -fno-asm -Wall -Wextra -std=c++17 -lmpdclient
files = main.out

install : 
	$(CC) $(FLAGS) main.cpp -o main.out
	# $(CC) $(FLAGS) brute.cpp -o brute.out
	# $(CC) $(FLAGS) gen.cpp -o gen.out
	

clear :
	rm -f $(files)
