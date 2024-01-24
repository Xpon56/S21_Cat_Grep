CC = gcc
CFLAGS = -Wall -Werror -Wextra

all:clean s21_grep

s21_grep: 
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test: 
	sh tests.sh

clean:
	rm -f s21_grep
