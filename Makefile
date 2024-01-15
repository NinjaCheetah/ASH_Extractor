all:
	gcc source/main.c -fsanitize=address -g -m32 -o ASH