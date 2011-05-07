all:
		gcc -Wall -o swap -O3 swap.c

install: swap
		install -m 0755 swap /usr/bin
