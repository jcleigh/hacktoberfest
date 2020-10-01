.DEFAULT_GOAL := build

install: build
	mv remember /usr/local/bin
build:
	gcc remember.c -o remember
clean:
	rm ./remember
